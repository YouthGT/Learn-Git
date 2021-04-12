#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define PCF8591ADDR 0X90   //PCF8591Ӳ����ַ
#define	IICRead 1		   //IIC������λ
#define	IICWrite 0		   //IICд����λ

sbit SCL = P2^1;//I2Cʱ������
sbit SDA = P2^0;//I2C��������
bit AckFlag;//Ӧ���־λ

//��ʱ����
void delay5us()
{
	_nop_();
}
/*====================================
����	��IICStart()
����	����
����ֵ	����
����	��IIC������ʼ�ź�
====================================*/
void IICStart()
{
	SCL = 1;
	SDA = 1;
	delay5us();
	SDA = 0;
	delay5us();
} 
/*====================================
����	��IICStop()
����	����
����ֵ	����
����	��IIC����ֹͣ�ź�
====================================*/
void IICStop()
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	delay5us();//״̬����5us
	SDA = 1;
	delay5us();//״̬����5us	
}
/*====================================
����	��ReadACK()
����	����
����ֵ	��1��Ӧ��0Ӧ��
����	��IIC���߶��ӻ�Ӧ���ź�
====================================*/
bit ReadACK()
{
	SCL = 0;//����ʱ�����ߣ�����ӻ�����SDA
	SCL = 1;//���߶�SDA
	delay5us();
	if(SDA)//SDAΪ�ߵ�ƽ
	{
		SCL = 0;
		return(1);
	}
	else
	{
		SCL = 0;
		return(0);
	}
}
/*====================================
����	��SendACK(bit i)
����	��1�������ͷ�Ӧ��0����Ӧ��
����ֵ	����
����	����������Ӧ���ź�
====================================*/
void SendACK(bit i)
{
	SCL = 0;
	if(i)
		SDA = 1;
	else
		SDA = 0;
	SCL = 1;
	delay5us();
	SCL = 0;
	SDA = 1;//�ͷ���������
}
/*====================================
����	��IICSendByte(uchar DAT)
����	��DAT��Ҫ���͵�����
����ֵ	����
����	��IIC����һ���ֽ�����
====================================*/
void IICSendByte(uchar DAT)
{
	uchar i;
	for (i =0;i<8;i++)//���������������������
	{
		SCL = 0;
		if(DAT & 0x80)
			SDA = 1;
		else
			SDA = 0;
		SCL = 1;
		DAT <<= 1; 
	}
	SCL= 0;
	SDA = 1;//�ͷ�����
}
/*====================================
����	��PCF8591Write(uchar ADDR, DAT)
����	��ADDR ��Ԫ��ַ0-255��DAT ��Ҫ���������0-255
����ֵ	����
����	��PCF8591ָ����Ԫд��һ���ֽ�����
====================================*/
//void PCF8591Write(uchar ADDR,DAT)
//{
//	IICStart();//IIC��ʼ�ź�
//	IICSendByte(PCF8591ADDR + IICWrite);
//	if (ReadACK())//���ӻ�Ӧ��
//		AckFlag = 1;//NoAck
//	else
//		AckFlag = 0;//Ack
//	IICSendByte(ADDR);//���ʹ��浥Ԫ��ַ�ֽ�
//	if(ReadACK())//���ӻ�Ӧ��
//		AckFlag = 1;//NoAck
//	else
//		AckFlag = 0;//ACk
//	IICSendByte(DAT);
//	if(ReadACK())
//		AckFlag = 1;
//	else 
//		AckFlag = 0;
//	IICStop();//IICֹͣ�ź�	
//}
/*====================================
����	��IICReadByte()
����	����
����ֵ	�����ض�����һ�ֽ�����
����	��IIC���߶�һ�ֽ�����
====================================*/
uchar IICReadByte()
{
	uchar i,DAT;
	for(i = 0;i < 8;i++)//�ֱ���˴Σ�ÿ�ζ�һλ
	{
		DAT <<= 1;//��������׼��������һλ
		SCL = 0;//����ʱ�����ߣ�����ӻ�����SDA�仯
		SCL = 1;//����ʱ�����ߣ���ȡSDA�ϵ�����
		if(SDA)
			DAT |=0x01;
	}
	return (DAT);//�������ص�����
}
/*====================================
����	��PCF8591Read(uchar ADDR)
����	��ADDR ��Ԫ��ַ	0-255
����ֵ	������ָ����Ԫ������
����	����PCF8591ָ����Ԫ������
====================================*/
uchar PCF8591Read(uchar Ctrl)
{
	uchar DAT;
	IICStart();//IIC��ʼ�ź�
	IICSendByte(PCF8591ADDR + IICWrite);//����������ַ�Ӷ�д����λ
	if(ReadACK())//���ӻ�Ӧ��
		AckFlag = 1;	//NOACK
	else
		AckFlag = 0;	//ACK
	IICSendByte(Ctrl);//IIC����һ���ֽ�
	ReadACK();//���ӻ�Ӧ��
	IICStart();//�ٴβ���IIC��ʼ�ź�
	IICSendByte(PCF8591ADDR + IICRead);//����������ַ�Ӷ�д����λ ��
	if(ReadACK())//���ӻ�Ӧ��
		AckFlag = 1;	//NOACK
	else
		AckFlag = 0;	//ACK
	DAT = IICReadByte();//��һ�ֽ�
	SendACK(1);//�������ͷ�Ӧ��
	IICStop(); //IICֹͣ�ź�
	return(DAT);//���ض�������
}

