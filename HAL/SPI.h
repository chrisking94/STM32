#pragma once
#include "Common.h"
/**
******************************************************************************
* @file    SPI.h
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
struct __reserved_SSPI
{
public:
	typedef enum
	{
		_SamplingFrom2ndClock	=0x0001,/*�ӵ�2��ʱ�ӱ�Ե��ʼ�����������1��*/
		_HighSckWhileIdle		=0x0002,/*����ʱSck�ߵ�ƽ������͵�ƽ*/
		_MasterMode				=0x0004,/*����ģʽ������ӻ�ģʽ*/
		_EnableSPI				=0x0040,/*����SPI*/
		_LSBFirst				=0x0080,/*�ȷ���LSB��������MSB*/
		_InternalSlaveSelect	=0x0100,/*�ڲ����豸ѡ��SSM=1ʱ��λ����NSS�ŵ�ƽ*/
		_SoftwareSlaveManagement=0x0200,/*����������豸����*/
		_ReceiveOnly			=0x0400,/*������*/
		_16BitDataFrame			=0x0800,/*16λ����֡������8λ��ֻ����SPEnable=0ʱ����д��λ���������*/
		_TransmitCRCNext		=0x1000,/*��һ������ΪCRCУ�飬��DR��д�����һ��ֵ��д���λ����CRCУ��*/
		_CRCEnable				=0x2000,/*����CRCУ�飬������SPE=0ʱ*/
		_EnableOutput			=0x4000,/*ʹ�������ֻ��ģʽ���������ֹ�����ֻ��ģʽ�������SingleLineʹ��*/
		_SingleLine				=0x8000,/*����˫�򣬷���˫��˫�򡣵��ߣ�����MOSI���ӻ�MISO*/
	}SPICR1Setting;
	typedef	enum
	{
		_EnRxDMA				=0x0001,/*��������DMA,RXNE=1ʱ����DMA����*/
		_EnTxDMA				=0x0002,/*���÷���DMA��TXE=1ʱ����DMA����*/
		_EnSSOutput				=0x0004,/*������ģʽ��SS���*/
		_EnErrorInterrupt		=0x0020,/*�����жϣ�CRCERR��OVR��MODF����ʱ��*/
		_EnRxBuffNotEmptyIntr	=0x0040,/*���ջ������ǿ��ж�*/
		_EnTxBuffEmptyIntr		=0x0080,/*���ͻ�������ʹ��*/
	}SPICR2Setting;
public:
	char	sendChar(char ch);/*write a char������ģʽ����˫��*/
	u16		sendWord(u16 wd);
	u16		isBusy() const;
	void	enableDMA(BOOL bEnable);
	void	set(SPICR1Setting	st);	
	void	reset(SPICR1Setting st); 
	void	set(SPICR2Setting	st);	
	void	reset(SPICR2Setting st); 
	void	enable();
	void	disable();
	void	setMasterMode(BOOL bMaster);/*1.����Ϊ����,0.����Ϊ�ӻ�*/
	void	setBaudrateDiv(u16 div);/*�����ʷ�Ƶ��BDR=fpclk/div*/
private:
	__IO uint16_t CR1;
	uint16_t  RESERVED0;
	__IO uint16_t CR2;
	uint16_t  RESERVED1;
	__IO uint16_t SR;
	uint16_t  RESERVED2;
	__IO uint16_t DR;
	uint16_t  RESERVED3;
	__IO uint16_t CRCPR;
	uint16_t  RESERVED4;
	__IO uint16_t RXCRCR;
	uint16_t  RESERVED5;
	__IO uint16_t TXCRCR;
	uint16_t  RESERVED6;
	__IO uint16_t I2SCFGR;
	uint16_t  RESERVED7;
	__IO uint16_t I2SPR;
	uint16_t  RESERVED8; 
};

#define spi1	(*(__reserved_SSPI*)SPI1)
#define spi2	(*(__reserved_SSPI*)SPI2)
#define spi3	(*(__reserved_SSPI*)SPI3)

