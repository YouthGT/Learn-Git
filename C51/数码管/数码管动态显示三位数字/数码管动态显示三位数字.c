#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit WE = P2^7;
sbit DU = P2^6;

//����������ܶ�ѡ����0-9
uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//�����鴢����ROM��

void delay(uint z);//������ʱ����
void display(uint i);//������ʾ����


void main()
{
		display(111UL);//������Ҫ��ʾ��ֵ
}


//���뼶��ʱ����
void delay(uint z)
{
	uint x,y;
	for (x = z; x > 0;x--)
		for(y = 114; y>0; y--);
	
}
//�������ʾ����
void display(uint i)
{
	uint bai, shi, ge;
	bai = i / 100;         //212 / 100 = 2
	shi = i % 100 / 10;    //212 % 100 / 10 = 1
	ge  = i % 10;          //212 % 10 = 2
	
	while(1)
	{
	//��һλ�����(bai)
	    P0 = 0xff;//�������
		WE = 1;//�򿪶�ѡ������
		P0 = 0xfe;//1111 1110
		WE = 0;//����λѡ����
		
		DU = 1;//�򿪶�������
		P0 = table[bai];
		DU = 0;//�����ѡ����
		delay(5);//��ʱ5ms
	 
	//�ڶ�λ�����(shi)
	    P0 = 0xff;//�������
		WE = 1;//�򿪶�ѡ������
		P0 = 0xfd;//1111 1101
		WE = 0;//����λѡ����
		
		DU = 1;//�򿪶�������
		P0 = table[shi];
		DU = 0;//�����ѡ����
		delay(5);//��ʱ5ms
	
	//����λ�����(ge)
		P0 = 0xff;//�������
		WE = 1;//�򿪶�ѡ������
		P0 = 0xfb;//1111 1011
		WE = 0;//����λѡ����

		DU = 1;//�򿪶�������
		P0 = table[ge];
		DU = 0;//�����ѡ����
		delay(5);//��ʱ5ms
	}
}