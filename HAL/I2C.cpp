#include "I2C.h"

#define I2C_SCL PBout(6)
#define I2C_SDA PBout(7)

#define I2C_DutyCycle2 0xBFFF//duty cycle
#define I2C_DutyCycle16_9 0x4000
#define I2C_DutyCycle I2C_DutyCycle2
#define I2C_PCLK 8000000
#define I2C_Speed 40000

__reserved_SI2C	oI2C1(I2C1);

__reserved_SI2C::__reserved_SI2C(I2C_TypeDef *I2C)
{
	/* I2C ���� */
	CR2 = 0x0700|(u16)(I2C_PCLK/1000000);//16���������λΪƵ�ʣ�2~36MHz��8MHz��I2C_CR2��
	OAR1 |= 0x00;//7bit��ַ��I2C_OAR1��
	OAR2  = 0;
	CCR = calcCRRValue(I2C_Speed);//��I2C_CCR��
	TRISE = calcTRISEValue(I2C_Speed);//��I2C_TRISE��
	CR1 = 0x0401;//bit15Ϊ1��ʹI2C���ڸ�λ״̬��I2C_CR1��
	/* ��Ա��ʼ�� */
	I2CDevAddr=0x00;
	Mod=_W;
	nReadLen=0;
	m_cStat=_Standby;
	nWriteLen=0;
}

__reserved_SI2C::~__reserved_SI2C(void)
{
}

void __reserved_SI2C::setClockFrequency(const u8 freq)
{
	RST_REG(CR2,0,0x3f,freq);
}

inline void __reserved_SI2C::set(const I2CCR1Conf conf)
{
	CR1|=conf;
}

inline void __reserved_SI2C::set(const I2CCR2Conf conf)
{
	CR2|=conf;
}

inline void __reserved_SI2C::reset(const I2CCR1Conf conf)
{
	CR1&=~conf;
}

inline void __reserved_SI2C::reset(const I2CCR2Conf conf)
{
	CR2&=~conf;
}

void __reserved_SI2C::enableDMA()
{
	CR2|=_En_DMARequest;
}

void __reserved_SI2C::disableDMA()
{
	CR2&=~_En_DMARequest;
}

inline void __reserved_SI2C::enableInterrupt(const I2CIntrConf conf)
{
	CR2|=conf;
}

inline void __reserved_SI2C::disableInterrupt(const I2CIntrConf conf)
{
	CR2&=~conf;
}

void __reserved_SI2C::setInterfaceAddress(const u8 conf)
{
	RST_REG(OAR1,1,0x7f,conf);
}

inline u16 __reserved_SI2C::isFlagOn(const I2CSR1Flag conf) const
{
	return SR1&conf;
}

inline u16 __reserved_SI2C::isFlagOn(const I2CSR2Flag conf) const
{
	return SR2&conf;
}

inline void __reserved_SI2C::clearFlag(const I2CSR2Flag conf)
{
	SR2&=~conf;
}

inline void __reserved_SI2C::clearFlag(const I2CSR1Flag conf)
{
	SR1&=~conf;
}

void __reserved_SI2C::writeData(u8 addr,u8 dat)
{
	Mod = _W;
	nWriteLen=2;
	Buffer[0]=addr;
	Buffer[1]=dat;
	transfer();
	wait();
}

u8 __reserved_SI2C::readData(u8 addr)
{
	Mod=_R;
	nReadLen=1;
	nWriteLen=1;
	Buffer[0]=addr;
	transfer();
	wait();
	return Buffer[0];
}

void __reserved_SI2C::EV_IRQHandler()
{
	static u32 x;//!ָ��
    static u16 mod=_W;
	
    if (this->SR1 & 1<<0)//!�ѷ�����ʼ����
    {
        this-> DR = this->I2CDevAddr | mod ;//!��ģʽ��д�ӻ���ַ
    }
    else if (this->SR1 & 1<<1)//!��ģʽ���ѷ��ʹӻ���ַ��
    {
        x=0;

        this->SR2;//!��SR2�����SR1 bit1��

        this->ack();//!����ack

        if (mod==_W)//!ģʽΪ����ʱ�򲻽�����һ��,����ַ���ͺ�ֱ�ӽ��ж�ȡ
        {
            if (this->nWriteLen>0)
            {
                this-> DR = this->Buffer[x++];//!���͵�һ���ֽ�
            }
        }
        else
        {
            if (this->nReadLen==1)
            {
                this->nack();//!�ر�ack
				this->stop();//!��ǰΪ��ģʽ���ڽ����꽫Ҫ������Ψһһ���ֽں����ֹͣλ
            }
        }
    }
    else if (this-> SR1 & 1<<6)//!���յ��������һ�δ����ȡ
    {
        if (this->nReadLen==1)
        {
			mod=_W;//!�ֽڶ�ȡ��ϣ��л�״̬
        }
        else
        {
            if (x==this->nReadLen-2)
            {
                //!�ڵ����ڶ����ֽ��յ������Ӧ��λ���Ա�֤���һ���ֽں�û��Ӧ��λ��NAck��
				//!���ڽ�Ҫ���������һ���ֽں����ֹͣλ
                this->nack();
				this->stop();
				nWriteLen=0;
				mod=_W;
            }
        }

        this->Buffer[x++] = this-> DR;//!������Ĵ�����ֵд�뻺������
		
		if(x==this->nReadLen)
		{
			this->m_cStat = _Standby;
		}
    }
    else if (this-> SR1 & 1<<7)//!�����ݽ������������ݼĴ���δд��������
    {
        if (x<this->nWriteLen)
        {
			if (this->Mod == _W)
			{
				/*if (!(pI2C-> SR1 & 1<<7))//!�յ�NAck
				{
					
				}*/
				if (x==this->nWriteLen-1)//!׼�������һ���ֽ�д����ֹͣ����
				{
					//I2C_nack();
					this->stop();
					nReadLen=0;
					nWriteLen=0;
				}
			}
            //!����������д����
            this-> DR = this->Buffer[x++];
        }
        else
        {
			if (this->Mod == _R)
			{
				//!��ģʽ��д��������Ѿ����
				//!��ʼReadģʽ�Ķ�����
				mod=_R;
				this->start();
			}
			else //!I2CT.imod == I2CWrite����Stop�źŲ����󣬿��ܲ���ִ�е�������ܳ�������
			{
				((__reserved_SI2C*)this)->m_cStat = _Standby;
			}
        }
    }
    else
    {
        //printStr(" SR1="   ,USART2);
       //printNum(pI2C->SR1   ,USART2);
        //printStr(" "   ,USART2);
    }
}

/******************
	�����ж�
******************/
void __reserved_SI2C::ER_IRQHandler()
{
	m_cStat=_Error;
	if (SR1 & 1<<10)         //Ӧ��ʧ��
	{
		SR1 &=~(1<<10);      //����ж�
	}
	if (SR1 & 1<<14)         //��ʱ
	{
		SR1 &=~(1<<14);      //����ж�
	}
	if (SR1 & 1<<11)         //����/Ƿ��
	{
		SR1 &=~(1<<11);      //����ж�
	}
	if (SR1 & 1<<9)          //�ٲö�ʧ
	{
		SR1 &=~(1<<9);       //����ж�
	}
	if (SR1 & 1<<8)          //���߳���
	{
		SR1 &=~(1<<8);       //����ж�
	}
}

/* Calc Maximum Rise Time for fast mode */
u16 __reserved_SI2C::calcTRISEValue(u32 ClockSpeed)
{
	u16 value;
	value=(u16)(I2C_PCLK / 1000000);
	if (ClockSpeed > 100000)
	{
		value = value*300/1000;
	}
	value++;
	return value;
}

/******************
	�ж����
******************/
void I2C1_EV_IRQHandler(void)
{
    oI2C1.EV_IRQHandler();
}

void I2C1_ER_IRQHandler(void)       //m_I2C Error Interrupt
{
	oI2C1.ER_IRQHandler();
}

u16 __reserved_SI2C::calcCRRValue(u32 ClockSpeed)
{
	u16 result=0x04;
	if (ClockSpeed <= 100000)
	{
		/* �����׼ģʽ���ٶ� */
		result = I2C_PCLK / (ClockSpeed << 1);
		/* ����Ƿ�С��0x4���������Сֵ��*/
		if (result < 0x04)
		{
			result = 0x04;
		}
		/* Maximum Rise Time for standard mode */
	}
	else /*(ClockSpeed <= 400000)*/
	{
		/* �������ģʽ���ٶ� */
		if (I2C_DutyCycle == I2C_DutyCycle2)
		{
			/* Fast mode speed calculate: Tlow/Thigh = 2 */
			result = (uint16_t)(I2C_PCLK / (ClockSpeed * 3));
		}
		else
		{
			/* Fast mode speed calculate: Tlow/Thigh = 16/9 */
			result = (uint16_t)(I2C_PCLK / (ClockSpeed * 25));
			/* Set DUTY bit */
			result |= I2C_DutyCycle16_9;
		}

		/* ���result��CCR�Ƿ�Ϊ��*/
		if ((result & 0x0FFF) == 0)
		{
			/* ������С����ֵ */
			result |= (uint16_t)0x0001;
		}
		/* ��λF/S */
		result |=0x8000;
	}
	return result;
}
