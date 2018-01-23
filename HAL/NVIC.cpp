#include "NVIC.h"
/**
  ******************************************************************************
  * @file    NVIC.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 13:09
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

void __reserved_SNVIC::enable(IRQn_Type IRQn)
{
	ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

void __reserved_SNVIC::disable(IRQn_Type IRQn)
{
	ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

//!��������жϵ���Ӧ���ȼ�����Ӧ���ȼ�����һ���Ļ������ĸ��ж��ȷ�������ִ�С�
//!�����ȼ�����ռ���ȼ��ǿ��Դ�����ڽ��еĵ���ռ���ȼ��жϵġ�����ռ���ȼ���ͬ��
//!�жϣ������ȼ�����Ӧ���ȼ������Դ�ϵ���Ӧ���ȼ����жϡ�

void __reserved_SNVIC::configPriority(IRQn_Type IRQn,u8 PreemptionPriority,u8 SubPriority)
{
	u32 tmp,grp;

	grp=((SCB->AIRCR>>8)&0x7)-3;
	u8 IPRADDR = IRQn/4;//�õ��飨ÿ��4������ַx
	u8 IPROFFSET = IRQn%4;//�õ�����ƫ��
	IPROFFSET=IPROFFSET*8+4;//�õ�ƫ��ȷ��λ�ã�8λһ��Channel����ֻʹ�ø�4bit��
	//!���ȼ����ù���4λ����λ(��xλ)Ϊ��ռ���ȼ�����λ��yλ��Ϊ��Ӧ���ȼ���x y��SCB->AIRCR��أ��ο�ǰ��˵��
	tmp=((PreemptionPriority)<<grp)&0xf;//������ռ���ȼ�
	tmp|=SubPriority&(0x0f>>(4-grp));//������Ӧ���ȼ�
	//!IP���ж����ȼ����ƵļĴ����飨Interrupt Priority Registers��
	IP[IPRADDR]|=tmp<<IPROFFSET;//������Ӧ���ȼ����������ȼ� 
}

