#include <reg52.h>
#include <intrins.h>
//�궨��
#define uint unsigned int
#define uchar unsigned char
	
sbit beep=P2^3;//������λ����
	
uchar temp;//LED����ر���

void	delay (uint z);//���뼶�����ʱ��������

void main()
{
	temp=0xf0;//1111 0000 
	P1=temp;
	delay(100);
	while(1)
	{
		temp=_crol_(temp,1);//ѭ�����ƣ���λһ������
		P1=temp;
		beep=~beep;//ȡ����������1�ر�ȡ����Ϊ���whileѭ���ﵽ�ε�����
		delay(100);
	}
}
//��ʱ����
void delay (uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
	
}