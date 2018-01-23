#pragma once
#include "Common.h"
class __reserved_SI2C
{
#define DevCount 2//ʹ�õ�I2Cģ��ĸ���
#define BUFFER_SIZE 8//��������С
public:
	typedef enum
	{
		_En_I2C				=0x0001,/*����I2C*/
		_Mode_SMBus			=0x0002,/*SMBusģʽ,����I2Cģʽ*/
		_Mode_SMBBusMaster	=0x0008,/*SMBus����ģʽ������SMBus�ӻ�*/
		_En_ARP				=0x0010,/*ʹ��ARP*/
		_En_PEC				=0x0020,/*����PEC*/
		_En_GneralCall		=0x0040,/*����㲥���У���Ӧ����Ӧ��ַ00h*/
		_Da_ClockStretching	=0x0080,/*��ֹʱ���ӳ�����ģʽ��*/
		_Gen_Start			=0x0100,/*��ģʽ���ظ�������ʼ��������ģʽ�����߿���ʱ������ʼ����*/
		_Gen_Stop			=0x0200,/*��ģʽ���ڵ�ǰ�ֽڴ����ǰ��ʼ�������������ֹͣλ����ģʽ���ڵ�ǰ�ֽڴ�����ͷ�SCL��SDA��*/
		_En_Acknowledge		=0x0400,/*����Ӧ��*/
		/*1��ACKλ��������λ�Ĵ�������յ���һ���ֽڵ�(N)ACK��PECλ��������λ�Ĵ�������յ���һ���ֽ���PEC��
		  0��ACKλ���Ƶ�ǰ��λ�Ĵ��������ڽ��յ��ֽڵ�(N)ACK��PECλ������ǰ��λ�Ĵ����ڵ��ֽ���PEC*/
		_AckPECPostion		=0x0800,
		_PacketErrorChecking=0x1000,/*PEC����*/
		_SMBusAlert			=0x2000,
		_SoftwareRest		=0x8000,/*I2Cģ�鸴λ*/
	}I2CCR1Conf;
	typedef enum
	{
		/*
		�����������£����������жϣ�
		�C BERR = 1��
		�C ARLO = 1��
		�C AF = 1��
		�C OVR = 1��
		�C PECERR = 1��
		�C TIMEOUT = 1��
		�C SMBAlert = 1��
		*/
		_Intr_Error		=0x0010,
		/*
		�����������£����������жϣ�
		�C SB = 1 (��ģʽ)��
		�C ADDR = 1 (��/��ģʽ)��
		�C ADD10= 1 (��ģʽ)��
		�C STOPF = 1 (��ģʽ)��
		�C BTF = 1������û��TxE��RxNE�¼���
		�C ���ITBUFEN = 1��TxE�¼�Ϊ1��
		�C ���ITBUFEN = 1��RxNE�¼�Ϊ1��
		*/
		_Intr_Event		=0x0020,
		_Intr_Buffer	=0x0040,/*1����TxE=1��RxNE=1ʱ�������¼��ж�(����DMAEN�Ǻ���״̬)��*/
	}I2CIntrConf;
	typedef enum
	{
		_En_DMARequest	=0x0080,/*1����TxE=1��RxNE =1ʱ������DMA����*/
		_DMALastTransfer=0x0100,/*1����һ��DMA��EOT�����Ĵ��䡣ע����λ��������ģʽʹ�ã� ʹ�������һ�ν�������ʱ���Բ���һ��NACK��*/
	}I2CCR2Conf;
	typedef enum
	{
		_Flag_StartBit				=0x0001,/*��ʼ�����ѷ���*/
		_Flag_AddressSentOrMatched	=0x0002,/*��ַ�ѷ��ͻ�ƥ��*/
		_Flag_ByteTransferFinished	=0x0004,/*�ֽڷ��ͽ���*/
		_Flag_10BitHeaderSent		=0x0008,/*�����ѽ���10λ��ַ��һ���ֽڷ��ͳ�ȥ*/
		_Flag_StopDetected			=0x0010,/*��⵽ֹͣλ*/
		_Flag_RxRegNotEmpty			=0x0040,/*���ռĴ����ǿ�*/
		_Flag_TxRegNotEmpty			=0x0080,/*���ͼĴ����ǿ�*/
		_Flag_BusError				=0x0100,/*��ʼ��ֹͣ��������*/
		_Flag_ArbitrationLost		=0x0200,/*�ٲö�ʧ*/
		_Flag_AcknowledgeFailure	=0x0400,/*Ӧ��ʧ��*/
		_Flag_OverrunOrUnderrun		=0x0800,/*���ػ�Ƿ��*/
		/*0: ��PEC���󣺽��յ�PEC�����������ACK(���ACK=1)��
		  1: ��PEC���󣺽��յ�PEC�����������NACK(����ACK��ʲôֵ)��
		�C ��λ�����д��0�����������PE=0ʱ��Ӳ�������*/
		_Flag_PECErrorInReception	=0x1000,
		/*0���޳�ʱ����
		  1��SCL�� �ڵ��Ѵ� ��25ms(��ʱ)�������� �� �͵�ƽ�� �� ʱ����չ ʱ �䳬��
		10ms(Tlow:mext)������豸�͵�ƽ�ۻ�ʱ����չʱ�䳬��25ms(Tlow:sext)��
		�C ���ڴ�ģʽ�����ø�λ�����豸��λͨѶ��Ӳ���ͷ����ߡ�
		�C ������ģʽ�����ø�λ��Ӳ������ֹͣ������*/
		_Flag_TimeoutOrTlowError	=0x4000,
		_Flag_SMBusAlert			=0x8000,
	}I2CSR1Flag;
	typedef enum
	{
		_Flag_Master					=0x0001,/*��ģʽ*/
		_Flag_BusBusy					=0x0002,/*���������ڽ�������ͨѶ*/
		_Flag_Transmitter				=0x0004,/*��Ϊ���ݷ����������ܵĵ�ַ�ֽ�R/Wλ������λ*/
		_Flag_GeneralCall				=0x0010,/*�յ��㲥���еĵ�ַ*/
		/*0��δ�յ�SMBus�豸��Ĭ�ϵ�ַ��
		  1����ENARP=1ʱ���յ�SMBus�豸��Ĭ�ϵ�ַ��*/
		_Flag_SMBusDeviceDefaultAdress	=0x0020,
		/*0��δ�յ�SMBus�����ĵ�ַ��
		  1����SMBTYPE=1��ENARP=1ʱ���յ�SMBus������ַ��*/
		_Flag_SMBusHostHeader			=0x0040,
		/*0�����յ��ĵ�ַ��OAR1�ڵ�������ƥ�䣻
		  1�����յ��ĵ�ַ��OAR2�ڵ�������ƥ�䡣*/
		_Flag_DualFlag					=0x0080,
	}I2CSR2Flag;
public:
	__reserved_SI2C(I2C_TypeDef *I2C);
	~__reserved_SI2C(void);
	void setClockFrequency(const u8 freq);/*I2Cģ��ʱ��Ƶ�ʣ���Χ2~36MHz*/
	void set(const I2CCR1Conf conf);
	void reset(const I2CCR1Conf conf);
	void enableDMA();
	void disableDMA();
	void set(const I2CCR2Conf conf);
	void reset(const I2CCR2Conf conf);
	void enableInterrupt(const I2CIntrConf conf);
	void disableInterrupt(const I2CIntrConf conf);
	void setInterfaceAddress(const u8 conf);/*����������ַ����7λ��Ч*/
	u16	 isFlagOn(const I2CSR1Flag	conf) const;
	u16	 isFlagOn(const I2CSR2Flag	conf) const;
	void clearFlag(const I2CSR2Flag conf);
	void clearFlag(const I2CSR1Flag conf);

	void transfer(){start();}//��������
	void wait(void)	const{while(m_cStat==_Transffering);}
	void writeData(u8 addr,u8 dat);
	u8 readData(u8 addr);
	 void EV_IRQHandler();//���жϺ�������
	 void ER_IRQHandler();
protected:
	u16 calcCRRValue(u32 ClockSpeed);
	u16 calcTRISEValue(u32 ClockSpeed);
	 void start()			{m_cStat=_Transffering;m_I2C->CR1 |=   1<<8;}//!������ʼ����
	 void stop()		const{m_I2C->CR1 |=   1<<9;}
	 void end()		const{m_I2C->CR1 &=   ~1;}//PE��0
	 void ack()		const{m_I2C->CR1 |= 1<<10;}//����ACK
	 void nack()		const{m_I2C->CR1 &= ~(1<<10);}//��ACK
public:
	u8			I2CDevAddr;//I2C�����ϵ��豸��ַ
	u8			Buffer[BUFFER_SIZE];//���仺��
	u8			nWriteLen;//д�����ݸ���
	enum{_W,_R}	Mod;//д �� ��
	u8			nReadLen;//��ȡ���ݸ���
private:
	__IO uint16_t CR1;
	uint16_t  RESERVED0;
	__IO uint16_t CR2;
	uint16_t  RESERVED1;
	__IO uint16_t OAR1;
	uint16_t  RESERVED2;
	__IO uint16_t OAR2;
	uint16_t  RESERVED3;
	__IO uint16_t DR;
	uint16_t  RESERVED4;
	__IO uint16_t SR1;
	uint16_t  RESERVED5;
	__IO uint16_t SR2;
	uint16_t  RESERVED6;
	__IO uint16_t CCR;
	uint16_t  RESERVED7;
	__IO uint16_t TRISE;
	uint16_t  RESERVED8;
	I2C_TypeDef *m_I2C;
	enum		
	{
		_Standby,
		_Transffering,
		_Error
	}			m_cStat;
private://��̬��Ա
	static I2C_TypeDef *s_CurI2C;//��ǰ����ʹ�õ�I2C
};

extern __reserved_SI2C oI2C1;