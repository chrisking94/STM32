#pragma once
#include "Common.h"
#include "GPIOPin.h"
/**
  ******************************************************************************
  * @file    EXTI.h
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 12:54
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

struct __reserved_SEXTI//�ܹ�ֻ��16���ⲿ�ж�ģ�飬���Զ���GPIO������Ϊ�ж�ʱ�����źŲ�����ͬ
{
public:
	typedef enum 
	{
		_Rising=1,//�����ش���
		_Falling,//�½��ش���
		_RisiFall//�������½��ش���
	}EXTITrigMode;
public:
		void	enableInterrupt(u8	linex);/*linex[0~19]*/
		void	disableInterrupt(u8	linex);/*linex[0~19]*/
		void	enableEventRequest(u8	linex);/*linex[0~19]*/
		void	disableEventRequest(u8	linex);/*linex[0~19]*/
		void	enableRisingTrig(u8	linex);/*linex[0~19]�����������ش���*/
		void	disableRisingTrig(u8	linex);/*linex[0~19]����ֹ�����ش���*/
		void	enableFallingTrig(u8	linex);/*linex[0~19]�������½��ش���*/
		void	disableFallingTrig(u8	linex);/*linex[0~19]����ֹ�½��ش���*/
		void	trigInterrupt(u8	linex);/*linex[0~19]��ͨ���ú������Դ����ж�*/
		void	clearPendingBit(u8	linex);/*linex[0~19]���������λ���жϺ�������Ҫ����*/
		u32		isPended(u8	linex);/*linex[0~19]���Ƿ����*/
private:
	__IO uint32_t IMR;
	__IO uint32_t EMR;
	__IO uint32_t RTSR;
	__IO uint32_t FTSR;
	__IO uint32_t SWIER;
	__IO uint32_t PR;
};

#define exti	(*(__reserved_SEXTI*)EXTI)




inline void __reserved_SEXTI::enableInterrupt(u8 linex)
{
	BSETB_REG(IMR,linex);
}

inline void __reserved_SEXTI::disableInterrupt(u8 linex)
{
	BCLR_REG(IMR,linex);
}

inline void __reserved_SEXTI::enableEventRequest(u8 linex)
{
	BSETB_REG(EMR,linex);
}

inline void __reserved_SEXTI::disableEventRequest(u8 linex)
{
	BCLR_REG(EMR,linex);
}

inline void __reserved_SEXTI::enableRisingTrig(u8 linex)
{
	BSETB_REG(RTSR,linex);
}

inline void __reserved_SEXTI::disableRisingTrig(u8 linex)
{
	BCLR_REG(RTSR,linex);
}

inline void __reserved_SEXTI::enableFallingTrig(u8 linex)
{
	BSETB_REG(FTSR,linex);
}

inline void __reserved_SEXTI::disableFallingTrig(u8 linex)
{
	BCLR_REG(FTSR,linex);
}

inline void __reserved_SEXTI::trigInterrupt(u8 linex)
{
	BSETB_REG(SWIER,linex);
}

inline void __reserved_SEXTI::clearPendingBit(u8 linex)
{
	BSETB_REG(PR,linex);
}

inline u32 __reserved_SEXTI::isPended(u8 linex)
{
	return BGET_REG(PR,linex);
}
