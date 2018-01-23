#include "SCB.h"
/**
  ******************************************************************************
  * @file    SCB.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 13:30
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

void __reserved_SSCB::setNVICPriorityGroup(const NVICPriorityGroup group)
{
	u32 tmp,tmp1;

	tmp1=group;//ȡ����λ
	tmp1<<=8;
	tmp=SCB->AIRCR;//��ȡ��ǰ������
	//!SCB->AIRCR��16λ�Ĵ���
	tmp&=0x0000F8FF;//�����ǰ����
	//!SCB->AIRCR ���޸���Ҫͨ���ڸ�16 λд��0X05FA �����Կ�����޸ĵ�
	tmp|=0x05FA0000;//д��Կ��
	tmp|=tmp1;
	SCB->AIRCR=tmp;
}

void __reserved_SSCB::setNVICVetorTable(NVICVectorTable tab,u32 offset/*=0*/)
{
	SCB->VTOR = tab | (offset & (uint32_t)0x1FFFFF80);
}
