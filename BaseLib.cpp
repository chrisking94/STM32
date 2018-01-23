#include "BaseLib.h"
#include "CommuDev.h"
#include "stdarg.h"
#include "GPIOPin.h"
#include "RCC.h"
#include "AFIO.h"
#include "SysTick.h"
#include "NVIC.h"
#include "SCB.h"

#define obeep	PA14


void BaseLib_init(void)
{
	//++++++++++++++++++++RCCʱ������
    //!�õ�Remapʱ�����ȴ�AFIOʱ��
	rcc.enableClock(__reserved_SRCC::_AFIO);
	rcc.enableClock(__reserved_SRCC::_TIM1);
	rcc.enableClock(__reserved_SRCC::_TIM2);
	rcc.enableClock(__reserved_SRCC::_TIM3);
	rcc.enableClock(__reserved_SRCC::_TIM4);
	rcc.enableClock(__reserved_SRCC::_USART1);
	rcc.enableClock(__reserved_SRCC::_USART2);
	rcc.enableClock(__reserved_SRCC::_I2C1);
	rcc.enableClock(__reserved_SRCC::_SPI1);
	rcc.enableClock(__reserved_SRCC::_GPIOA);
	rcc.enableClock(__reserved_SRCC::_GPIOB);
	rcc.enableClock(__reserved_SRCC::_GPIOC);
	rcc.enableClock(__reserved_SRCC::_ADC1);
	rcc.enableClock(__reserved_SRCC::_SPI1);
	rcc.enableClock(__reserved_SRCC::_DMA1);
	
	rcc.resetPeriph(__reserved_SRCC::_SPI1);
	rcc.resetPeriph(__reserved_SRCC::_SPI2);
	
	afio.configJTAG(__reserved_SAFIO::_NSWJ);

	//NVIC
	scb.setNVICPriorityGroup(__reserved_SSCB::_4Preemption_4Sub);
	scb.setNVICVetorTable(__reserved_SSCB::_Flash);
	nvic.configPriority(TIM3_IRQn,1,1);
	nvic.enable(TIM3_IRQn);
	nvic.configPriority(DMA1_Channel3_IRQn,0,0);
	nvic.enable(DMA1_Channel3_IRQn);
	nvic.configPriority(TIM1_UP_IRQn,1,3);
	nvic.enable(TIM1_UP_IRQn);
	nvic.configPriority(TIM4_IRQn,2,3);
	nvic.enable(TIM4_IRQn);
	nvic.configPriority(EXTI15_10_IRQn,2,3);
	nvic.enable(EXTI15_10_IRQn);

	led1.pinMod(_OGOD);
	led2.pinMod(_OGOD);
	obeep.pinMod(_OGOD);
    led1=1;	
	led2=1;
}

void delays(u32 s)
{
	while (s--)
	{
		delayms(1000);
	}
}

void delayms(u32 ms)
{
	if(ms==0) return;
	SysTick->VAL =0;//��ռ�����
	SysTick->CTRL |=  5;//����������
	while (ms--)
	{
		SysTick->LOAD=36000;//ʱ����أ�������0ʱ��������װ�ص�ֵ(24bit)���ڲ�ʱ��36MHz��36000/36MHz=1ms
		while (!(SysTick->CTRL&(1<<16)))//�ȴ�������0��CountFlag������0ʱ��λΪ1
		{
			//HighPriorityInterrupt();//��ʱʱ�䳤(ms��)ʱ��ִ�и����ȼ�������MasterControl��ʵ��
		}

	}
	SysTick->CTRL &= ~1;       //�رռ�����
}

void delayus(u32 us)
{
	if(us==0) return;

	SysTick->LOAD=(u32)us*36;//ʱ����أ�������0ʱ��������װ�ص�ֵ(24bit)
	SysTick->VAL =0;           //��ռ�����
	SysTick->CTRL |=  5;          //(bit0��en)��ʼ������(bit2)�ڲ�36MHzʱ��Ƶ��
	while (!(SysTick->CTRL&(1<<16)));//�ȴ�������0��CountFlag������0ʱ��λΪ1
	SysTick->CTRL &= ~1;       //�رռ�����
}

void waitWhile(bool condition)
{
	while(condition)
	{
		//HighPriorityInterrupt();//��ִ�и����ȼ�����
	}
}

void beep(u16 time ,u16 interval)
{
	interval+=200;
	for (;time>0;time--)
	{
		obeep=!obeep;
		delayus(interval);
	}
	obeep=1;
}

void startTiming(void)
{
	systick.setReloadVal(0x00FFFFFF);//ʱ����أ�������0ʱ��������װ�ص�ֵ(24bit)
	systick.reset();
	systick.start();
}

u32 readTimingms(void)
{
	u32 ms;
	systick.stop();
	ms=(SysTick->LOAD-SysTick->VAL)/72000;
	return ms;
}

u32 div_u32(u32 n1,u32 n2)
{

}

u8 bcd2dec(u8 bcd)
{

}

u8 dec2bcd(u8 dec)
{

}

/*********************************
ע������������ŵ�ƽʱҪд�����·�ʽ
printf("%d",(u32)PA15);
��д��
printf("%d",PA15);
�������PA15��ָ��
*********************************/
u32 printf(const char *format,...)
{
	va_list args;
	u32 ret;

	va_start(args,format);
	ret=printf(format,args);
	va_end(args);
	return ret;//������Ŀ�����޸�
}

u32 printf(const char *format,va_list &args)
{
#define put(x) CCommuDev::pDev->sendChar(x)//CCommuDev::pDev->sendChar(x)

	u8 i=0,j,k;
	char n;
	int num;
	char *s,buf[10];

	while(*format)
	{
		if(*format=='%')
		{
			format++;
			n=0;
			while(*format>='0'&&*format<='9')
			{
				n*=10;
				n+=*format++-0x30;
			}
			switch(*format)
			{
			case 'o'://offset
				while(n--) put(' ');
				break;
			case 'c':
				put((char)va_arg(args,int));
				break;
			case 's':
				s=va_arg(args,char*);
				while(*s) put(*s++);
				break;
			case 'd':
				num=((int)va_arg(args,int));
				k=0;
				if (num < 0)
				{
					num = ~num;
					num += 1;
					put('-');
					j++;
				}
				do
				{
					buf[k++] = num % 10 + 0x30;
				}
				while (num /= 10);
				//������0�digits
				j = k;
				while (j < n)
				{
					put('0');
					j++;
				}
				while (k)
				{
					put(buf[--k]);
				}
				break;
			case '%':
				put('%');
				break;
			}
		}
		else
		{
			put(*format);
		}
		format++;
	}
	put(*format);

	return 1;//������Ŀ�����޸�
#undef put
}

u32 scanf(const char *format,...)
{

}
