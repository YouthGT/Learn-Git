/*
��P3^4��P1������һ�������ӣ���������������������ʾ����
����������Ϊһ��
*/
#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char 
	
sbit WE = P2^7;
sbit DU = P2^6;

//��ǰ�����Զ��庯��
void timer0Init();
void timer1Init();
void display(uint i);
void delay (uint z);

//����������ܶ�ѡ����0-9
uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//�����鴢����ROM��

//������
void main()
{
	uchar mSec;
	timer0Init();//��ʼ��������0����������
	timer1Init();//��ʼ����ʱ��1��������ʱ
	while(1)
	{
		if(TF1 == 1)//�ж϶�ʱ��1�Ƿ����
		{
			TF1 = 0;//������������־λ
			TH1 = 0x4b;//��ʱ�Ĵ����߰�λ
			TL1 = 0xfd;//��ʱ�Ĵ����Ͱ�λ
			mSec++;//50ms��
			if(mSec == 10)//500ms��
			{
				mSec = 0;//Ϊ��һ����ʱ50ms׼��
				P1 = ~P1;//�����������԰˸�LED�������ʾ����
				
			}
		}
//		delay(500);//��Ӱ������ܶ�̬ɨ��ʵʱ��ʾ�������ö�ʱ����ʱ	
		
		display(TL0);//�������ʾ
	 }	
}
//������0��ʼ��
void timer0Init()
{
	TR0 = 1;//����������0
	TMOD |= 0x05;//������ģʽ,16λ����ģʽ
	TH0 = 0;
	TL0 = 0;
	
}
//��ʱ��1��ʼ��
void timer1Init()
{
	TR1 = 1;//������ʱ��1
	TMOD |= 0x10;//��ʱ��1����ģʽ,16λ��ʱģʽ
	TH1 = 0x4b;
	TL1 = 0xfd;//��ʱ50ms
	
}
//��ʱ����
void delay (uint z)
{
	uint x,y;
	for (x = z; x > 0; x--)
		for(y = 114; y > 0; y--);
}
//����ܶ�̬��ʾ����
void display(uint i)
{
	uint bai,shi,ge;
	bai = i / 100;
	shi = i %100 / 10;
	ge = i % 10;

	//��λ��ʾ
	P0 = 0xff;//�������
	WE = 1;
	P0 = 0xfe;//1111 1110�򿪵�һλ�����
	WE = 0;
	
	DU = 1;
	P0 = table[bai];
	DU = 0;
	delay(5);
	
	//ʮλ��ʾ
	P0 = 0xff;//�������
	WE = 1;
	P0 = 0xfd;//1111 1101�򿪵ڶ�λ�����
	WE = 0;
	
	DU = 1;
	P0 = table[shi];
	DU = 0;
	delay(5);
	
	//��λ��ʾ
	P0 = 0xff;//�������
	WE = 1;
	P0 = 0xfb;//1111 1011�򿪵���λ�����
	WE = 0;
	
	DU = 1;
	P0 = table[ge];
	DU = 0;
	delay(5);	

}
