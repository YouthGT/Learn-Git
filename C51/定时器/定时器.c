#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char 
	
sbit WE = P2^7;
sbit DU = P2^6;

//��ǰ�����Զ��庯��
void timer0Init();
void display(uint i);
void delay (uint z);

//����������ܶ�ѡ����0-9
uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//�����鴢����ROM��

void main()
{
	uchar mSec, Sec;
	timer0Init();
	while(1)
	{
		 if(TF0 == 1)//
		 {
			 TF0 = 0;
			 TH0 = 0X4b;
			 TL0 = 0Xfd;
			 mSec++;//
			 if(mSec == 20)
			 {
				mSec = 0;
				 Sec++;
			 }
		 }
		 display(Sec);
	 }	
}
//��ʱ��0��ʼ��
void timer0Init()
{
	TR0 = 1;//������ʱ��0
	TMOD = 0x01;//��ʱ������ģʽ
	TH0 = 75;
	TL0 = 253;
	
}
//��ʱ����
void delay (uint z)
{
	uint x,y;
	for (x = z; x > 0; x--)
		for(y = 114; y > 0; y--);
}
void display(uint i)
{
	uint bai,shi,ge;
	bai = i / 100;
	shi = i %100 / 10;
	ge = i % 10;

	//
	P0 = 0xff;//
	WE = 1;
	P0 = 0xfe;//1111 1110
	WE = 0;
	
	DU = 1;
	P0 = table[bai];
	DU = 0;
	delay(5);
	
	//
	P0 = 0xff;//
	WE = 1;
	P0 = 0xfd;//1111 1101
	WE = 0;
	
	DU = 1;
	P0 = table[shi];
	DU = 0;
	delay(5);
	
	//
	P0 = 0xff;//
	WE = 1;
	P0 = 0xfb;//1111 1011
	WE = 0;
	
	DU = 1;
	P0 = table[ge];
	DU = 0;
	delay(5);	

}
