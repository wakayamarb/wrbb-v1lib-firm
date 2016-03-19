﻿/*
 * wrbb.h
 *
 * Copyright (c) 2016 Wakayama.rb Ruby Board developers
 *
 * This software is released under the MIT License.
 * https://github.com/wakayamarb/wrbb-v1lib-firm/blob/master/MITL
 *
 */
#ifndef _WRBB_H_
#define _WRBB_H_  1

#define RUBY_CODE_SIZE (1024 * 4)		//4kBまで実行可能とする

//バイトコードバージョンを定義します
#define BYTE_CODE2	2
#define BYTE_CODE3	3

//ファームウェアのバージョンを定義します
#define MASTER		1000
#define JAM			1001
#define SDBT		1002
#define SDWF		1003

//基板の設計バージョンを定義します
#define BOARD_GR	0
#define BOARD_P01	1
#define BOARD_P02	2
#define BOARD_P03	3
#define BOARD_P04	4
#define BOARD_P05	5

//RX600シリーズの型番を定義します
#define CPU_RX63N	128		//メモリ128KB
#define CPU_RX631	256		//メモリ256KB

//License表示
#define LICENSE_MRUBY		"mruby is released under the MIT License."
#define LICENSE_MRUBYURL	"https://github.com/mruby/mruby/blob/master/MITL"
#define LICENSE_WRBB		"Wakayama-mruby-board is released under the MIT License."
#define LICENSE_WRBBURL		"https://github.com/wakayamarb/wrbb-v1lib-firm/blob/master/MITL"

//バージョンと日付
#define WRBB_VERSION	"-1.54(2016/3/19)"

//バイトコードフォーマットの設定
//#define BYTECODE	BYTE_CODE2
#define BYTECODE	BYTE_CODE3
#if BYTECODE == BYTE_CODE2
#	define BYTECODE_TEXT	"f2"
#else
#	define BYTECODE_TEXT	"f3"
#endif

//基板のタイプ設定
#define BOARD	BOARD_GR
//#define BOARD	BOARD_P01
//#define BOARD	BOARD_P02
//#define BOARD	BOARD_P03
//#define BOARD	BOARD_P04
//#define BOARD	BOARD_P05
#if BOARD == BOARD_GR || BOARD == BOARD_P01
#	define BOARDNUM	"1"
#elif BOARD == BOARD_P02
#	define BOARDNUM	"2"
#elif BOARD == BOARD_P03
#	define BOARDNUM	"3"
#elif BOARD == BOARD_P04
#	define BOARDNUM	"4"
#elif BOARD == BOARD_P05
#	define BOARDNUM	"5"
#endif

//ファームウェア設定
#define FIRMWARE	MASTER
//#define FIRMWARE	JAM
//#define FIRMWARE	SDBT
//#define FIRMWARE	SDWF
#if BOARD == BOARD_GR
#	if FIRMWARE == MASTER
#		define FIRMWARE_TEXT	"SAKURA"
#	elif FIRMWARE == JAM
#		define FIRMWARE_TEXT	"SakuraJam"
#	endif
#else
#	if FIRMWARE == MASTER
#		define FIRMWARE_TEXT	"ARIDA"
#	elif FIRMWARE == JAM
#		define FIRMWARE_TEXT	"UmeJam"
#	elif FIRMWARE == SDBT
#		define FIRMWARE_TEXT	"SDBT"
#	elif FIRMWARE == SDWF
#		define FIRMWARE_TEXT	"SDWF"
#	endif
#endif


//RX600シリーズの設定
//#define CPU		CPU_RX631
#define CPU		CPU_RX63N
#if CPU == CPU_RX63N
#	define CPURAM	"(128KB)"		//メモリ128KB
#else
#	define CPURAM	"(256KB)"		//メモリ256KB
#endif


//#define	DEBUG		// Define if you want to debug

#ifdef DEBUG
#  define DEBUG_PRINT(m,v)    { Serial.print("** "); Serial.print((m)); Serial.print(":"); Serial.println((v)); }
#else
#  define DEBUG_PRINT(m,v)    // do nothing
#endif

#define	FILE_LOAD	PORT3.PIDR.BIT.B5		//PORT 3-5

#define XML_FILENAME  "wrbb.xml"
#define RUBY_FILENAME  "main.mrb"
#define RUBY_FILENAME_SIZE 32

#if BOARD == BOARD_GR || BOARD == BOARD_P02 || BOARD == BOARD_P03 || BOARD == BOARD_P04 || BOARD == BOARD_P05
	#define REALTIMECLOCK	1
#endif

#if BOARD == BOARD_GR
	#define RB_PIN0		0
	#define RB_PIN1		1
	#define RB_PIN18	18
	#define RB_PIN19	19
	#define RB_PIN2		2
	#define RB_PIN3		3
	#define RB_PIN4		4
	#define RB_PIN5		5
	#define RB_PIN6		6
	#define RB_PIN7		7
	#define RB_PIN8		8
	#define RB_PIN9		9
	#define RB_PIN10	10
	#define RB_PIN11	11
	#define RB_PIN12	12
	#define RB_PIN13	13
	#define RB_PIN14	14
	#define RB_PIN15	15
	#define RB_PIN16	16
	#define RB_PIN17	17

	#define RB_PIN20	20
	#define RB_PIN21	21
	#define RB_PIN22	22
	#define RB_PIN23	23
	#define RB_PIN24	24
	#define RB_PIN25	25
	#define RB_PIN26	26
	#define RB_PIN27	27

	#define RB_PIN30	30
	#define RB_PIN31	31

#elif BOARD == BOARD_P01
	#define RB_PIN0		1
	#define RB_PIN1		0
	#define RB_PIN18	22
	#define RB_PIN19	23
	#define RB_PIN2		8
	#define RB_PIN3		30
	#define RB_PIN4		31
	#define RB_PIN5		24
	#define RB_PIN6		26
	#define RB_PIN7		6
	#define RB_PIN8		7
	#define RB_PIN9		53
	#define RB_PIN10	10
	#define RB_PIN11	11
	#define RB_PIN12	12
	#define RB_PIN13	13
	#define RB_PIN14	14
	#define RB_PIN15	15
	#define RB_PIN16	16
	#define RB_PIN17	17

	#define RB_PIN20	33
	#define RB_PIN21	29
	#define RB_PIN22	5
	#define RB_PIN23	45
	#define RB_PIN24	54
	#define RB_PIN25	100

#elif BOARD == BOARD_P02
	#define RB_PIN0		1
	#define RB_PIN1		0
	#define RB_PIN18	30
	#define RB_PIN19	31
	#define RB_PIN2		22
	#define RB_PIN3		23
	#define RB_PIN4		8
	#define RB_PIN5		24
	#define RB_PIN6		26
	#define RB_PIN7		6
	#define RB_PIN8		7
	#define RB_PIN9		53
	#define RB_PIN10	10
	#define RB_PIN11	11
	#define RB_PIN12	12
	#define RB_PIN13	13
	#define RB_PIN14	14
	#define RB_PIN15	15
	#define RB_PIN16	16
	#define RB_PIN17	17

	#define RB_PIN20	33
	#define RB_PIN21	29
	#define RB_PIN22	5
	#define RB_PIN23	45
	#define RB_PIN24	54
	#define RB_PIN25	100

#elif BOARD == BOARD_P03 || BOARD == BOARD_P04 || BOARD == BOARD_P05
	#define RB_PIN0		1
	#define RB_PIN1		0
	#define RB_PIN18	30
	#define RB_PIN19	31
	#define RB_PIN2		22
	#define RB_PIN3		23
	#define RB_PIN4		8
	#define RB_PIN5		24
	#define RB_PIN6		26
	#define RB_PIN7		6
	#define RB_PIN8		7
	#define RB_PIN9		53
	#define RB_PIN10	10
	#define RB_PIN11	11
	#define RB_PIN12	12
	#define RB_PIN13	13
	#define RB_PIN14	14
	#define RB_PIN15	15
	#define RB_PIN16	16
	#define RB_PIN17	17

	#define RB_PIN20	33
	#define RB_PIN21	59
	#define RB_PIN22	60
	#define RB_PIN23	5
	#define RB_PIN24	57
	#define RB_PIN25	29
	#define RB_PIN26	58
	#define RB_PIN27	56
//	#define RB_PIN28	PB3
//	#define RB_PIN29	PB5
	#define RB_PIN30	45
	#define RB_PIN31	54
//	#define RB_PIN32	EMLE
	#define RB_PIN33	100

#endif

#define RB_LED	PIN_LED0


#endif // _WRBB_H_

