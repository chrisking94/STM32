#pragma once

class CCommuDev
{
public:
	CCommuDev(void);
	~CCommuDev(void);
	
	virtual void sendChar(char ch){}//д�ַ�
	virtual char recvChar(){}//�����ַ�

	virtual void printf(const char *format,...);
	static  void selectDevice(CCommuDev &pDev_){pDev=&pDev_;}//ѡ��һ����������豸
public:
	static CCommuDev *pDev;//Ĭ��serial1
};

