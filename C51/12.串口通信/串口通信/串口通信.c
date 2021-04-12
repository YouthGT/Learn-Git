#include <reg52.h>
#include <intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;

sbit DU = P2^6;//����ܶ�ѡ
sbit WE = P2^7;//����ܶ�ѡ
uint num;//�������ʾ��ֵ

//��������ܶ�ѡ��0-9
uchar code SMGduan[]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//�����λѡ��
uchar code SMGwei[] = {0xfe, 0xfd, 0xfb};

void timer0Init();
void display(uint i);
void UARTInit();

void main()
{
	timer0Init();//��ʱ��0��ʼ��
	UARTInit();//���ڳ�ʼ��
	while(1);
}
//��ʱ��0��ʼ������
void timer0Init()
{
	EA = 1;//�����ж�
	ET0 = 1;//�򿪶�ʱ��0�ж�
	TR0 = 1;//������ʱ��0
	TMOD |= 0x01;//��ʱ������ģʽ16λ��ʱģʽ
	TH0 = 0xed;
	TL0 = 0xff;//��ʱ5ms
}
//���ڳ�ʼ��
void UARTInit()
{
	EA = 1;//�����ж�
	ES = 1;//�򿪴����ж�
	SM0 =0; SM1 = 1;//���ڹ�����ʽ1,8λ
	REN = 1;//�����������
	TR1 = 1;//������ʱ��1 
	TMOD |= 0x20;//��ʱ��1������ģʽ2 8λ�Զ���װ
	TH1 = 0xfd;
	TL1 = 0xfd;//���ò�����9600
}
//��ʱ��0�жϺ���
void timer0() interrupt 1
{
    TH0 = 0xed;
	TL0 = 0xff;//��ʱ5ms
	display(num);//�������ʾ
}
//�����жϺ���
void UART() interrupt 4
{
	uchar temp;
	if(RI)//�жϽ����Ƿ����
	{
		num = SBUF;//��SBUF
		RI = 0;//���������ձ�־λ
		temp = num;
		SBUF = ++temp;//дSBUF����Ҫ���͵����ݷ��͸�������
	}
	if(TI)//�ж��Ƿ������
		TI = 0;//���㷢����ɱ�־
}
//�������ʾ����
void display(uint i)
{
	static uchar wei;//��̬�ֲ�����
	P0 = 0xff;//�������
	WE = 1;//��λѡ������
	P0 = SMGwei[wei];
	WE = 0;//����λѡ����
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