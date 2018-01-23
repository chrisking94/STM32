#include "SPI.h"
/**
  ******************************************************************************
  * @file    SPI.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 13:32
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
char __reserved_SSPI::sendChar(char ch)
{
	if(CR2&0x02)//DMAģʽ
	{
		
	}
	else
	{
		while(SR & (1<<7));//�ȴ�æ��־Ϊ0
		DR = (u16)ch;
		while(!(SR & (1<<0)));//�ȴ����ջ�����Ϊ�ǿ�
		return (char)DR;//��ȡ
	}
}


u16 __reserved_SSPI::sendWord(u16 wd)
{
	if(CR2&0x02)//DMAģʽ
	{
		
	}
	else
	{
		while(SR & (1<<7));//�ȴ�æ��־Ϊ0
		DR = wd;
		while(!(SR & (1<<0)));//�ȴ����ջ�����Ϊ�ǿ�
		return DR;//��ȡ
	}
}

u16 __reserved_SSPI::isBusy() const
{
	if(( SPI1->SR & 0x02 ) == 0) return TRUE;//�ȴ�TXEΪ1
	if(( SPI1->SR & 0x80 ) == 1) return TRUE;//�ȴ�æ��־Ϊ0
	return FALSE;
}

void __reserved_SSPI::enableDMA(BOOL bEnable)
{
	CR2&=~3;
	CR2|= 0//!(SPI_CR2)
			|bEnable<<0//RXDMAEN.�������ջ�����DMA
			|bEnable<<1//TXDMAEN.�������ͻ�����DMA
			;//!END
}

inline void __reserved_SSPI::set(SPICR1Setting st)
{
	CR1|=st;
}

inline void __reserved_SSPI::set(SPICR2Setting st)
{
	CR2|=st;
}

inline void __reserved_SSPI::reset(SPICR1Setting st)
{
	CR1&=~st;
}

inline void __reserved_SSPI::reset(SPICR2Setting st)
{
	CR2&=~st;
}

inline void __reserved_SSPI::enable()
{
	CR1|=_EnableSPI;
}

inline void __reserved_SSPI::disable()
{
	CR1&=~_EnableSPI;
}

inline void __reserved_SSPI::setMasterMode(BOOL bMaster)
{
	BRST_REG(CR1,2,bMaster);
}

inline void __reserved_SSPI::setBaudrateDiv(u16 div)
{
	RST_REG(CR1,3,0x7,div>>2);
}
