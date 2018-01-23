#pragma once
#include "stm32f10x.h"
#include "stdint-gcc.h"

typedef uint8_t		BYTE;
typedef uint8_t		uchar;
typedef uint16_t	WORD;
typedef	uint32_t	DWORD;
typedef uint64_t	QWORD;
typedef enum
{
	FALSE,
	TRUE
}BOOL;
#define NULL 0

#define CLR_REG(reg,offset,mask)	((reg)&=~((mask)<<(offset)))//��offset�����mask^(1/2)��λ
#define SET_REG(reg,offset,val)		((reg)|=(val)<<(offset))//��offset������val
#define RST_REG(reg,offset,mask,val) CLR_REG(reg,offset,mask);SET_REG(reg,offset,val)//��offset������mask^(1/2)��λ
#define GET_REG(reg,offset,mask)	(((reg)>>(offset))&(mask))
#define BCLR_REG(reg,ibit) CLR_REG(reg,ibit,1)//���λ
#define BSETB_REG(reg,ibit) SET_REG(reg,ibit,1)//��λ
#define BRST_REG(reg,ibit,val) RST_REG(reg,ibit,1,val)//����λ
#define BGET_REG(reg,ibit)	(((reg)>>(ibit))&0x01)

#define __API	extern "C"	//C�ӿ�
#define __INTR	__API void	//�ж�
#define _72MHz	((u32)72000000)
#define	_36MHz	((u32)36000000)



