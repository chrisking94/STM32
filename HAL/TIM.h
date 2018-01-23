#pragma once
#include "Common.h"
#include "RCC.h"

#define TIM_STOP(tim) (BCLR_REG(tim->CR1,0))
#define TIM_START(tim) (BCLR_REG(tim->CR1,0))
#define TIM_CUIF(tim) (BCLR_REG(tim->SR,0))
struct __reserved_STIM
{
public:
	typedef enum
	{
		_=0,
		_En_Counter				=0x0001,/*ʹ�ܼ�����*/
		_DE_Update				=0x0002,/*��ֹUEV*/
		_En_UpdateRequestSource	=0x0004,
		_Mode_OnePulse			=0x0008,/*������ģʽ*/
		_Direction_CountDown	=0x0010,/*���¼�������������*/
		_En_AutoReloadPreload	=0x0080,/*ARR�Ĵ�����װ�뻺����*/
	}CR1Conf;
	typedef enum
	{
		/*���ض���ģʽ�����������ݷ���λ(DIR)���ϻ����¼���*/
		_EdgeMode,
		/*�������ģʽ1����������������Ϻ����¼���������Ϊ�����ͨ��(TIMx_CCMRx�Ĵ���
		��CCxS=00)������Ƚ��жϱ�־λ��ֻ�ڼ��������¼���ʱ�����á�*/
		_CenterMode1,
		/*�������ģʽ2����������������Ϻ����¼���������Ϊ�����ͨ��(TIMx_CCMRx�Ĵ���
		��CCxS=00)������Ƚ��жϱ�־λ��ֻ�ڼ��������ϼ���ʱ�����á�*/
		_CenterMode2,
		/*�������ģʽ3����������������Ϻ����¼���������Ϊ�����ͨ��(TIMx_CCMRx�Ĵ���
		��CCxS=00)������Ƚ��жϱ�־λ���ڼ��������Ϻ����¼���ʱ�������á�*/
	}CenterAlignedMode;
	typedef enum
	{
		_1div,
		_2div,
		_4div,
	}ClockDivisionConf;
	typedef enum
	{
		_Intr_Update				=0x0001,/*�����ж�*/
		_Intr_CaptureCompare1		=0x0002,/*����Ƚ�1�ж�*/
		_Intr_CaptureCompare2		=0x0004,/*����Ƚ�2�ж�*/
		_Intr_CaptureCompare3		=0x0008,/*����Ƚ�3�ж�*/
		_Intr_CaptureCompare4		=0x0010,/*����Ƚ�4�ж�*/
		_Intr_COM					=0x0020,/*COM�ж�*/
		_Intr_Trigger				=0x0040,/*�����ж�*/
		_Intr_Break					=0x0080,/*ɲ���ж�*/
	}TimerInterrupt;
	typedef enum
	{
		_DMA_Update					=0x0100,/*����DMA*/
		_DMA_CaptureCompare1		=0x0200,/*����Ƚ�1DMA*/
		_DMA_CaptureCompare2		=0x0400,/*����Ƚ�2DMA*/
		_DMA_CaptureCompare3		=0x0800,/*����Ƚ�3DMA*/
		_DMA_CaptureCompare4		=0x1000,/*����Ƚ�4DMA*/
		_DMA_COM					=0x2000,/*COM DMA*/
		_DMA_Trigger				=0x4000,/*����DMA*/
	}TimerDMA;
	typedef enum
	{
		_Flag_UpdateInterrupt		=0x0001,/*�����жϱ��*/
		_Flag_CaptureCompare1		=0x0002,/*����Ƚ�1���*/
		_Flag_CaptureCompare2		=0x0004,/*����Ƚ�2���*/
		_Flag_CaptureCompare3		=0x0008,/*����Ƚ�3���*/
		_Flag_CaptureCompare4		=0x0010,/*����Ƚ�4���*/
		_Flag_COM					=0x0020,/*COM���*/
		_Flag_Trigger				=0x0040,/*�������*/
		_Flag_Break					=0x0080,/*ɲ�����*/
		_Flag_CCOvercapture1		=0x0020,/*����/�Ƚ�1 �ظ�������*/
		_Flag_CCOvercapture2		=0x0040,/*����/�Ƚ�2 �ظ�������*/
		_Flag_CCOvercapture3		=0x0080,/*����/�Ƚ�3 �ظ�������*/
		_Flag_CCOvercapture4		=0x0100,/*����/�Ƚ�4 �ظ�������*/
	}TimerFlag;
	typedef enum
	{
		_Event_Update				=0x0001,/*�����¼�*/
		_Event_CaptureCompare1		=0x0002,/*����Ƚ�1�¼�*/
		_Event_CaptureCompare2		=0x0004,/*����Ƚ�2�¼�*/
		_Event_CaptureCompare3		=0x0008,/*����Ƚ�3�¼�*/
		_Event_CaptureCompare4		=0x0010,/*����Ƚ�4�¼�*/
		_Event_COM					=0x0020,/*COM�¼�*/
		_Event_Trigger				=0x0040,/*�����¼�*/
		_Event_Break				=0x0080,/*ɲ���¼�*/
	}TimerEvent;
public:
	__reserved_STIM();
	~__reserved_STIM(void);
	/*��2λ�����ڶ�ʱ��ʱ��(CK_INT)Ƶ�ʡ�����ʱ����������������������˲���(ETR,TIx)����
	�Ĳ���ʱ��֮��ķ�Ƶ������*/
	void setDTSClockDivision(ClockDivisionConf conf);
	void setCenterAlignedMode(CenterAlignedMode conf);
	void set(CR1Conf conf);
	void reset(CR1Conf conf);
	void enableInterrupt(TimerInterrupt conf);
	void disableInterrupt(TimerInterrupt conf);
	void enableDMARequest(TimerDMA conf);
	void disableDMARequest(TimerDMA conf);
	void clearFlag(TimerFlag conf);
	u32	 isFlagOn(TimerFlag conf) const;/*���Ա�־�Ƿ���λ*/
	void generateEvent(TimerEvent conf);/*��������¼�*/
	void enable();
	void disable();
	void setTimeMs(uint16_t ms);
	void setTimeUs(uint16_t us);
	void setTime56Ns(uint16_t hns);//��56����Ϊ��λ
	void clearUpateInterruptFlag(){SR &= ~1;}

	//PWN
	void enablePWM(uint8_t chx);//ʹ��chx[1~4]ͨ��PWN���
	void setCCR(const u8 chx,uint16_t val);
	void setLowVoltageValid(const u8 chx);
	void setHighVoltageValid(const u8 chx);
private:
	__IO uint16_t CR1;
	uint16_t  RESERVED0;
	__IO uint16_t CR2;
	uint16_t  RESERVED1;
	__IO uint16_t SMCR;
	uint16_t  RESERVED2;
	__IO uint16_t DIER;
	uint16_t  RESERVED3;
	__IO uint16_t SR;
	uint16_t  RESERVED4;
	__IO uint16_t EGR;
	uint16_t  RESERVED5;
	__IO uint16_t CCMR1;
	uint16_t  RESERVED6;
	__IO uint16_t CCMR2;
	uint16_t  RESERVED7;
	__IO uint16_t CCER;
	uint16_t  RESERVED8;
	__IO uint16_t CNT;
	uint16_t  RESERVED9;
	__IO uint16_t PSC;
	uint16_t  RESERVED10;
	__IO uint16_t ARR;
	uint16_t  RESERVED11;
	__IO uint16_t RCR;
	uint16_t  RESERVED12;
	__IO uint16_t CCR1;
	uint16_t  RESERVED13;
	__IO uint16_t CCR2;
	uint16_t  RESERVED14;
	__IO uint16_t CCR3;
	uint16_t  RESERVED15;
	__IO uint16_t CCR4;
	uint16_t  RESERVED16;
	__IO uint16_t BDTR;
	uint16_t  RESERVED17;
	__IO uint16_t DCR;
	uint16_t  RESERVED18;
	__IO uint16_t DMAR;
	uint16_t  RESERVED19;
};

//Timer����궨��
#define tim1	(*(__reserved_STimer*)TIM1)
#define tim2	(*(__reserved_STimer*)TIM2)
#define tim3	(*(__reserved_STimer*)TIM3)
#define tim4	(*(__reserved_STimer*)TIM4)
#define tim5	(*(__reserved_STimer*)TIM5)
#define tim6	(*(__reserved_STimer*)TIM6)
#define tim7	(*(__reserved_STimer*)TIM7)
#define tim8	(*(__reserved_STimer*)TIM8)
#define tim9	(*(__reserved_STimer*)TIM9)
#define tim10	(*(__reserved_STimer*)TIM10)
#define tim11	(*(__reserved_STimer*)TIM11)
#define tim12	(*(__reserved_STimer*)TIM12)
#define tim13	(*(__reserved_STimer*)TIM13)
#define tim14	(*(__reserved_STimer*)TIM14)
#define tim15	(*(__reserved_STimer*)TIM15)
#define tim16	(*(__reserved_STimer*)TIM16)
#define tim17	(*(__reserved_STimer*)TIM17)




inline void __reserved_STIM::setDTSClockDivision(ClockDivisionConf conf)
{
	RST_REG(CR1,8,0x3,conf);
}

inline void __reserved_STIM::setCenterAlignedMode(CenterAlignedMode conf)
{
	RST_REG(CR1,5,0x3,conf);
}

inline void __reserved_STIM::set(CR1Conf conf)
{
	CR1|=conf;
}

inline void __reserved_STIM::reset(CR1Conf conf)
{
	CR1&=~conf;
}

inline void __reserved_STIM::enableInterrupt(TimerInterrupt conf)
{
	DIER|=conf;
}

inline void __reserved_STIM::disableInterrupt(TimerInterrupt conf)
{
	DIER&=~conf;
}

inline void __reserved_STIM::enableDMARequest(TimerDMA conf)
{
	DIER|=conf;
}

inline void __reserved_STIM::disableDMARequest(TimerDMA conf)
{
	DIER&=~conf;
}

inline void __reserved_STIM::clearFlag(TimerFlag conf)
{
	SR&=~conf;
}

inline u32 __reserved_STIM::isFlagOn(TimerFlag conf) const
{
	return SR&conf;
}

inline void __reserved_STIM::generateEvent(TimerEvent conf)
{
	EGR|=conf;
}

inline void __reserved_STIM::enable()
{
	CR1|=_En_Counter;
}
