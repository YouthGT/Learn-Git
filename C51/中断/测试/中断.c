#include <reg52.h>
#include <intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;

sbit flag = P3^7;//�ⲿ�ж��źŲ�����
sbit key_s2 = P3^0;//��������s2
sbit beep = P2^3;

void int1Inint();
void delay(uint z);

void main ()//main���������ѭ��
{
	int1Inint();//�ⲿ�ж�1��ʼ��
	while(1)
	{
		if(key_s2 == 0)//�жϰ����Ƿ���
		{
			delay(20);//��������
			if(key_s2 == 0);
			{
				
				flag = 1;
				flag = 0;//�����½���
				while(!key_s2);//�ж��Ƿ�����
			}
			
		}
	}
	
}
//�ⲿ�ж�1��ʼ��
void int1Inint()
{
	EA = 1;//�жϵ��ܿ���
	EX1 = 1;//�ⲿ�жϵ��ܿ���
	IT1 = 1;//ѡ���ⲿ�ж�Ϊ�½��ش���
}

//�ⲿ�ж�1�жϷ������  д��������֮����Ҫ����
void int1()interrupt 2
{
	beep =~beep;
}
//���뼶��ʱ����
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}