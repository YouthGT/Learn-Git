#include <REG52.H>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit DU = P2^6;//����ܶ�ѡ  U9
sbit WE = P2^7;//�����λѡ  U8

void main()//
{
	WE = 1;//��λѡ������
	P0 = 0xfe;//����λѡ������1111 1110
	WE = 0;//�ر�λѡ������
	
	DU = 1;//�򿪶�ѡ������
	P0 = 0xff;//���ƶ�ѡ������ 1111 1111��ʾΪ8. 
	DU = 0;//�ر�����Ĵ���
	
	while(1)
	{
			P0 = 0x06;//��ѡ�������Ѿ��رգ���Ӱ��
	}
} 