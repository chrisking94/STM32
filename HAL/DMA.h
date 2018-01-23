#pragma once
#include "Common.h"
#include "DMA_Channel.h"
/**
  ******************************************************************************
  * @file    DMA.h
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
struct __reserved_SDMA
{
public:
	u32		isError(u32 chx);/*ͨ��x�Ƿ������*/
	u32		isHalfTransferComplete(u32 chx);/*��������*/
	u32		isTransferComplete(u32 chx);/*�������*/
	void	clearErrorFlag(u32 chx);/*��������־*/
	void	clearHalfTransferCompleteFlag(u32 chx);/*����������ɱ�־*/
	void	clearTransferCompleteFlag(u32 chx);/*��������־*/
	void	clearGlobalFlag(u32 chx);/*���CHxȫ�ֱ�־*/
private:
	__IO uint32_t ISR;
	__IO uint32_t IFCR;
public:
	//DMA Channel
	//*ע��DMA1��7��Channel����DMA2����5��Channel*/
	__reserved_SDMA_Channel	ch1;
	__reserved_SDMA_Channel	ch2;
	__reserved_SDMA_Channel	ch3;
	__reserved_SDMA_Channel	ch4;
	__reserved_SDMA_Channel	ch5;
	__reserved_SDMA_Channel	ch6;
	__reserved_SDMA_Channel	ch7;
};

#define dma1	(*(__reserved_SDMA*)DMA1)
#define dma2	(*(__reserved_SDMA*)DMA2)




inline u32 __reserved_SDMA::isError(u32 chx)
{
	return BGET_REG(ISR,(3+((chx-1)<<2)));
}

inline u32 __reserved_SDMA::isHalfTransferComplete(u32 chx)
{
	return BGET_REG(ISR,(2+((chx-1)<<2)));
}

inline u32 __reserved_SDMA::isTransferComplete(u32 chx)
{
	return BGET_REG(ISR,1+((chx-1)<<2));
}

inline void __reserved_SDMA::clearErrorFlag(u32 chx)
{
	BSETB_REG(IFCR,3+((chx-1)<<2));
}

inline void __reserved_SDMA::clearHalfTransferCompleteFlag(u32 chx)
{
	BSETB_REG(IFCR,2+((chx-1)<<2));
}

inline void __reserved_SDMA::clearTransferCompleteFlag(u32 chx)
{
	BSETB_REG(IFCR,1+((chx-1)<<2));
}

inline void __reserved_SDMA::clearGlobalFlag(u32 chx)
{
	BSETB_REG(IFCR,0+((chx-1)<<2));
}
