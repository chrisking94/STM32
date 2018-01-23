#include "TIM.h"
#include "RCC.h"

void __reserved_STIM::disable()
{
	CR1&=~_En_Counter;
}

void __reserved_STIM::setTimeMs(uint16_t ms)
{
	if(this==(void*)TIM1)
	{
		//72MHz
		PSC = 36000 - 1;
		CNT = ms*2;
	}
	else
	{
		//36MHz
		PSC = 36000 - 1;//Ԥ��Ƶ��������ʱ��Ƶ��CK_CNT=fck_psc/(PSC+1)��1ms)��16bit�Ĵ��������65536-1����16λ�Ĵ���
		CNT = ms;
	}
	
	ARR = CNT;
}

void __reserved_STIM::setTimeUs(uint16_t us)
{
	if(this==(void*)TIM1)
	{
		//72MHz
		PSC = 72 - 1;
	}
	else
	{
		//36MHz
		PSC = 36 - 1;
	}
	CNT = us;
	ARR = us;
}

void __reserved_STIM::setTime56Ns(uint16_t hns)
{
	if(this==(void*)TIM1)
	{
		//72MHz
		PSC = 4 - 1;
	}
	else
	{
		//36MHz
		PSC = 2 - 1;
	}
	CNT = hns;
	ARR = hns;
}

void __reserved_STIM::enablePWM(uint8_t chx)
{
	chx--;

	if(chx<2)
	{
		CCMR1|=0
					|6<<(4+(chx*8))//����Ƚ�chxʹ��
					//|1<<(3+(chx*8))//����chxԤװ��
						;
	}
	else
	{
		CCMR2|=0
					|6<<(4+((chx-2)*8))
					//|1<<(3+(chx*8))
					;
	}

	CCER |= 0//!(TIMx_CCER)
		|0<<(1+(chx*4))//OCx��������ߵ�ƽ��Ч
		|1<<(0+(chx*4))//OCx���ʹ��
		;
}

void __reserved_STIM::setCCR(const u8 chx,uint16_t val)
{
	(&CCR1)[(chx-1)<<1]=val;
}

void __reserved_STIM::setLowVoltageValid(const u8 chx)
{
	BSETB_REG(CCER,((chx-1)<<2)+1);
}

void __reserved_STIM::setHighVoltageValid(const u8 chx)
{
	BCLR_REG(CCER,((chx-1)<<2)+1);
}

