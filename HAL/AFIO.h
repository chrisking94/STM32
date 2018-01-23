#pragma once
#include "Common.h"
/**
  ******************************************************************************
  * @file    AFIO.h
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 12:24
  * @contact 1050243371@qq.com
  * @brief   TestMCU:STM32F103C8T6 IDE:VS2010 OS:Windows7
  * @history
  *  <author> 
  *  <date>   
  *  <version>
  *  <brief>  
  ******************************************************************************     
  *
  * You can modify this file and redistribute it.Yet you shoud keep the original
  * authors' information and copyright declaration unmodified.If you are willing
  * to redistribute this file after your modification,it's very nice for you to
  * add your information to the history list.
  *
  * 				Copyright (c) XinxinWang.XiHua University,China.
  ******************************************************************************
  */
struct __reserved_SAFIO
{
public:
	typedef enum
	{
		_SWJ_JTRST=0,//��λ״̬
		_SWJ_NJTRST=1,//�޸�λ
		_SW_NJ=2,//�ر�JTAG-DP������SW-DP
		_NSWJ=4,//�ر�JTAG-DP���ر�SW-DP
	}JTAGConf;
	typedef enum
	{
		_PA,
		_PB,
		_PC,
		_PD,
		_PE,
		_PF,
		_PG,
	}EXTIxPinGroup;
public:
		void	configJTAG(JTAGConf conf);
		void	selectEXTIPinGrp(u8 extix,EXTIxPinGroup pingrp);/*exti[0~15]*/
private:
	__IO uint32_t EVCR;
	__IO uint32_t MAPR;
	__IO uint32_t EXTICR[4];
	uint32_t RESERVED0;
	__IO uint32_t MAPR2;
};

#define afio	(*(__reserved_SAFIO*)AFIO)




inline void __reserved_SAFIO::configJTAG(JTAGConf conf)
{
	RST_REG(MAPR,24,0x7,conf);
}

inline void __reserved_SAFIO::selectEXTIPinGrp(u8 extix,EXTIxPinGroup pingrp)
{
	RST_REG(EXTICR[extix/4],(extix%4)*4,0xf,pingrp);
}
