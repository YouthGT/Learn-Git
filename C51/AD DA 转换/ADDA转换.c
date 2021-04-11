#include <reg52.h>
#include <intrins.h>
#include <IIC.h>

#define uchar unsigned char
#define uint unsigned int
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3


sbit DU = P2^6;//����ܶ�ѡ
sbit WE = P2^7;//����ܶ�ѡ
sbit key_s2 = P3^0;//��������S2
sbit key_s3 = P3^1;//��������S3
extern bit AckFlag;//Ӧ���־λ
uint num;//�������ʾ��ֵ


//��������ܶ�ѡ��0-9
uchar code SMGduan[]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//�����λѡ��
uchar code SMGwei[] = {0xfe, 0xfd, 0xfb};

void delay(uint z);
void timer0Init();
void display(uint i);

void main()
{
	timer0Init();//��ʱ��0��ʼ��
	while (1)
	{
		EA = 0;//�����ж�
		num = PCF8591Read(CH0);
		EA = 1;//���ж�
		delay(5);	
	}
	
}


void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 
//��ʱ��0��ʼ������
void timer0Init()
{
	EA = 1;//�����ж�
	ET0 = 1;//�򿪶�ʱ��0�ж�
	TR0 = 1;//������ʱ��0
	TMOD = 0x01;//��ʱ������ģʽ16λ��ʱģʽ
	TH0 = 0xed;
	TL0 = 0xff;//��ʱ5ms
}
//��ʱ��0�жϺ���
void timer0() interrupt 1
{
    TH0 = 0xed;
	TL0 = 0xff;//��ʱ5ms
	display(num);//�������ʾ
}
//�������ʾ����
void display(uint i)
{
	static uchar wei;//��̬�ֲ�����
	P0 = 0xff;
	WE = 1;
	P0 = SMGwei[wei];
	WE = 0;
	switch(wei)
	{
		case 0:
			DU = 1;
			P0 = SMGduan[i / 100];
			DU = 0;
			break;
		case 1:
			DU = 1;
			P0 = SMGduan[i % 100 / 10];
			DU = 0;
			break;
		case 2:
			DU = 1;
			P0 = SMGduan[i % 10];
			DU = 0;
			break;
	}
	wei++;
	if(wei == 3)
		wei = 0;
}
