/*
 * シリアル通信関連
 *
 * Copyright (c) 2016 Wakayama.rb Ruby Board developers
 *
 * This software is released under the MIT License.
 * https://github.com/wakayamarb/wrbb-v1lib-firm/blob/master/MITL
 *
 */
#include <rxduino.h>

#include <mruby.h>
#include <mruby/string.h>

#include "../wrbb.h"
#include "sSerial.h"

RB_Serial rbserial[SERIAL_MAX];

//**************************************************
// シリアル通信を初期化します: Serial.begin
//  Serial.begin(num, bps)
//  num: 通信番号(0:USB, 1:TX0/RX1, 2:TX5/RX6, 3:TX7/RX8, 4:TX/RX)
//  bps: ボーレート 
//**************************************************
mrb_value mrb_serial_begin(mrb_state *mrb, mrb_value self)
{
int num, bps;

	mrb_get_args(mrb, "ii", &num, &bps);

	if (num < 0 || num >= SERIAL_MAX){
		return mrb_nil_value();			//戻り値は無しですよ。
	}

	if(num == 0){
		//rbserial[num].enable = true;
		rbserial[num].serial = &Serial;
		//rbserial[num].sci = Serial.get_handle();
	}
	else{
		if (rbserial[num].enable){
			rbserial[num].serial->end();
			delay(50);
			delete rbserial[num].serial;
		}
		rbserial[num].serial = new CSerial();
	}

	//シリアル通信の初期化
	SCI_PORT port = SCI_USB0;
	switch(num){
	case 1:
		port = SCI_SCI0P2x;
		break;
	case 2:
		port = SCI_SCI2B;
		break;
	case 3:
		port = SCI_SCI6B;
		break;
	case 4:
		port = SCI_SCI2A;
		break;
	default:
		port = SCI_USB0;
		break;
	}

	if(port != SCI_USB0){
		rbserial[num].serial->begin(bps, port);

		sci_convert_crlf_ex(rbserial[num].serial->get_handle(), CRLF_NONE, CRLF_NONE);		//バイナリを通せるようにする
	}

	rbserial[num].enable = true;
	rbserial[num].sci = rbserial[num].serial->get_handle();

	return mrb_nil_value();			//戻り値は無しですよ。
}

//**************************************************
// シリアル通信のデフォルト出力ポートを設定します: Serial.setDefault
//  Serial.setDefault(num)
//  num: 通信番号(0:USB, 1:TX0/RX1, 2:TX5/RX6, 3:TX7/RX8)
//**************************************************
mrb_value mrb_serial_setdefault(mrb_state *mrb, mrb_value self)
{
int num;

	mrb_get_args(mrb, "i", &num);

	if (num < 0 || num >= SERIAL_MAX){
		return mrb_nil_value();
	}

	rbserial[num].serial->setDefault();
	
	return mrb_nil_value();			//戻り値は無しですよ。
}

//**************************************************
// シリアルに出力します: Serial.print|Serial.println
//**************************************************
void mrb_serial_msprint(int num, mrb_value text)
{

	if(num < 10)
	{
		rbserial[num].serial->print( RSTRING_PTR(text) );
	}
	else if(num < 20)
	{
		rbserial[num - 10].serial->println( RSTRING_PTR(text) );
	}
	else{
		rbserial[num - 20].serial->println();
	}
}

mrb_value msprintMode(mrb_state *mrb, mrb_value self, int mode)
{
int num;
mrb_value text;

	int n = mrb_get_args(mrb, "i|S", &num, &text);

	if (num < 0 || num >= SERIAL_MAX){
		return mrb_nil_value();
	}

	if(mode == 0){
		if(n >= 2){
			mrb_serial_msprint(num,  text);
		}
	}
	else{
		if(n >= 2){
			mrb_serial_msprint(num + 10,  text);
		}
		else{
			mrb_serial_msprint(num + 20,  text);
		}
	}
	return mrb_nil_value();			//戻り値は無しですよ。
}

//**************************************************
// シリアルに出力します: Serial.print
//  Serial.print(num[,str])
//  num: 通信番号(0:USB, 1:TX0/RX1, 2:TX5/RX6, 3:TX7/RX8)
//  str: 文字列
//    省略時は何も出力しません
//**************************************************
mrb_value mrb_serial_print(mrb_state *mrb, mrb_value self)
{
	return msprintMode(mrb, self, 0);
}

//**************************************************
// シリアルに\r\n付きで出力します: Serial.println
//  Serial.println(num[,str])
//  num: 通信番号(0:USB, 1:TX0/RX1, 2:TX5/RX6, 3:TX7/RX8)
//  str: 文字列
//    省略時は改行のみ
//**************************************************
mrb_value mrb_serial_println(mrb_state *mrb, mrb_value self)
{
	return msprintMode(mrb, self, 1);
}

//**************************************************
// シリアルから1バイト取得します: Serial.read
//  Serial.read(num)
//  num: 通信番号(0:USB, 1:TX0/RX1, 2:TX5/RX6, 3:TX7/RX8)
// 戻り値
//	0x00～0xFFの値、データが無いときは-1が返ります
//**************************************************
mrb_value mrb_serial_read(mrb_state *mrb, mrb_value self)
{
int num;

	mrb_get_args(mrb, "i", &num);

	if (num >= 0 && num < SERIAL_MAX){
		if(sci_rxcount_ex(rbserial[num].sci)){
			return mrb_fixnum_value( rbserial[num].serial->read() );
		}
	}
	return mrb_fixnum_value( -1 );
}

//**************************************************
// シリアルにデータを出力します: Serial.write
//  Serial.write(num, buf, len)
//  num: 通信番号(0:USB, 1:TX0/RX1, 2:TX5/RX6, 3:TX7/RX8)
//	buf: 出力データ
//	len: 出力データサイズ
// 戻り値
//	出力したバイト数
//**************************************************
mrb_value mrb_serial_write(mrb_state *mrb, mrb_value self)
{
int		num;
int		len;
mrb_value value;
char	*str;

	mrb_get_args(mrb, "iSi", &num, &value, &len);

	str = RSTRING_PTR(value);
	
	if (num < 0 || num >= SERIAL_MAX){
		return mrb_fixnum_value( 0 );
	}

	return mrb_fixnum_value( rbserial[num].serial->write( (const unsigned char *)str, len));
}

//**************************************************
// シリアルデータがあるかどうか調べます: Serial.available
//  Serial.available(num)
//  num: 通信番号(0:USB, 1:TX0/RX1, 2:TX5/RX6, 3:TX7/RX8)
//  戻り値 シリアルバッファにあるデータのバイト数。0の場合はデータなし
//**************************************************
mrb_value mrb_serial_available(mrb_state *mrb, mrb_value self)
{
int		num;
	
	mrb_get_args(mrb, "i", &num);

	if (num < 0 || num >= SERIAL_MAX){
		return mrb_fixnum_value( 0 );
	}
	return mrb_fixnum_value( sci_rxcount_ex(rbserial[num].sci) );
}

//**************************************************
// シリアルポートを閉じます: Serial.end
//  Serial.end(num)
//  num: 通信番号(0:USB, 1:TX0/RX1, 2:TX5/RX6, 3:TX7/RX8, 4:TX/RX)
//**************************************************
mrb_value mrb_serial_end(mrb_state *mrb, mrb_value self)
{
int		num;
int		ret = 0;
	
	mrb_get_args(mrb, "i", &num);

	if (num < 0 || num >= SERIAL_MAX){
		return mrb_nil_value();			//戻り値は無しですよ。
	}

	if(num != 0){	//USBは閉じない

		if (rbserial[num].enable == true){
			rbserial[num].serial->end();
			delay(50);
			delete rbserial[num].serial;
		}
	}
	rbserial[num].enable = false;

	return mrb_fixnum_value( ret );
}

//**************************************************
// シリアルにデータを出力します: Serial.write
//  Serial.write( buf )
//	buf: 出力データ
//**************************************************
/*
mrb_value mrb_system_write(mrb_state *mrb, mrb_value self)
{
int dat;

	mrb_get_args(mrb, "i", &dat);

	int ret = Serial.write( (unsigned char)dat );
	
	return mrb_fixnum_value( ret );
}
*/

//**************************************************
// ライブラリを定義します
//**************************************************
void serial_Init(mrb_state *mrb)
{
	for (int i = 0; i < SERIAL_MAX; i++){
		rbserial[i].enable = false;
		rbserial[i].serial = 0;
		rbserial[i].sci = 0;
	}

	struct RClass *serialModule = mrb_define_module(mrb, "Serial");

	mrb_define_module_function(mrb, serialModule, "begin", mrb_serial_begin, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, serialModule, "setDefault", mrb_serial_setdefault, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, serialModule, "print", mrb_serial_print, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
	mrb_define_module_function(mrb, serialModule, "println", mrb_serial_println, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));

	mrb_define_module_function(mrb, serialModule, "read", mrb_serial_read, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, serialModule, "write", mrb_serial_write, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, serialModule, "available", mrb_serial_available, MRB_ARGS_REQ(1));

	mrb_define_module_function(mrb, serialModule, "end", mrb_serial_end, MRB_ARGS_REQ(1));
}
