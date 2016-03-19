/*
 * RTC関連
 *
 * Copyright (c) 2016 Wakayama.rb Ruby Board developers
 *
 * This software is released under the MIT License.
 * https://github.com/wakayamarb/wrbb-v1lib-firm/blob/master/MITL
 *
 */
#include <rxduino.h>
#include <rtc.h>

#include <mruby.h>
#include <mruby/array.h>

#include "../wrbb.h"
#include "sKernel.h"

//**************************************************
// RTCの時計を取得します: Rtc.getDateTime
//  Rtc.getTime()
//
//  戻り値は以下のとおり
//  Year, Month, Day, Hour, Minute, Second
//  Year: 年
//  Month: 月
//  Day: 日
//  Hour: 時
//  Minute: 分
//  Second: 秒
//  @note        この関数の前にbeginを呼ばなくても、内部でbeginを呼び出すので心配ない
//  @note        内蔵RTCはBCDで値を扱うが、このライブラリはBCD→intへ変換するので気にしなくてよい
//  @note        24時間制である
//  @warning     RX63Nでは西暦20xx年代を想定しているため年は2桁しか意味を持たない。内部で2000を足している。
//**************************************************
mrb_value mrb_rtc_getDateTime(mrb_state *mrb, mrb_value self)
{
int year,mon,day,hour,min,sec;
mrb_value arv[6];

	if(RXRTC::getDateTime(year, mon, day, hour, min, sec) == true)
	{
		arv[0] = mrb_fixnum_value(year);
		arv[1] = mrb_fixnum_value(mon);
		arv[2] = mrb_fixnum_value(day);
		arv[3] = mrb_fixnum_value(hour);
		arv[4] = mrb_fixnum_value(min);
		arv[5] = mrb_fixnum_value(sec);
	}
	else{
		arv[0] = mrb_fixnum_value(-1);
		arv[1] = mrb_fixnum_value(-1);
		arv[2] = mrb_fixnum_value(-1);
		arv[3] = mrb_fixnum_value(-1);
		arv[4] = mrb_fixnum_value(-1);
		arv[5] = mrb_fixnum_value(-1);
	}
	return mrb_ary_new_from_values(mrb, 6, arv);
}

//**************************************************
// RTCの時計をセットします: Rtc.setDateTime
//  Rtc.setTime( array )
//  array: 年(0000-9999),月(1-12),日(1-31),時(0-23),分(0-59),秒(0-59)の配列
//
//  戻り値は以下のとおり
//		0: 失敗
//		1: 成功
//
// @note        この関数の前にbeginを呼ばなくても、内部でbeginを呼び出すので心配ない
// @note        内蔵RTCはBCDで値を扱うが、このライブラリはint→BCDへ変換するので気にしなくてよい
// @note        24時間制である
// @warning     RX63Nでは西暦20xx年代を想定しているため、年は2桁しか意味を持たない
//**************************************************
mrb_value mrb_rtc_setDateTime(mrb_state *mrb, mrb_value self)
{
int year,month,day,hour,minuit,second;
int ret = 0;
mrb_value value;

	mrb_get_args(mrb, "A", &value);

	if ( !mrb_array_p( value ) ){
		return mrb_fixnum_value(0);
	}

    int len = RARRAY_LEN( value );
	if(len < 6){
		return mrb_fixnum_value(0);
	}

	year = mrb_fixnum(mrb_ary_ref(mrb, value, 0));
	month = mrb_fixnum(mrb_ary_ref(mrb, value, 1));
	day = mrb_fixnum(mrb_ary_ref(mrb, value, 2));
	hour = mrb_fixnum(mrb_ary_ref(mrb, value, 3));
	minuit = mrb_fixnum(mrb_ary_ref(mrb, value, 4));
	second = mrb_fixnum(mrb_ary_ref(mrb, value, 5));

	year = year % 100;

	if(RXRTC::setDateTime(year, month, day, hour, minuit, second) == true){
		ret = 1;
	}

    return mrb_fixnum_value(ret);
}


//**************************************************
// RTCを起動します: Rtc.begin
//  Rtc.begin()
//
// 戻り値は以下のとおり
//	0: 起動失敗
//	1: 起動成功
//	2: RTCは既に起動していた(成功)
//**************************************************
mrb_value mrb_rtc_begin(mrb_state *mrb, mrb_value self)
{
	return mrb_fixnum_value( RXRTC::begin() );
}

//**************************************************
// ライブラリを定義します
//**************************************************
void rtc_Init(mrb_state *mrb)
{
	struct RClass *rtcModule = mrb_define_module(mrb, "Rtc");

	mrb_define_module_function(mrb, rtcModule, "begin", mrb_rtc_begin, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, rtcModule, "init", mrb_rtc_begin, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, rtcModule, "setTime", mrb_rtc_setDateTime, MRB_ARGS_REQ(6));
	mrb_define_module_function(mrb, rtcModule, "getTime", mrb_rtc_getDateTime, MRB_ARGS_NONE());
}
