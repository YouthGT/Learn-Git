#include <reg52.h>//����51ͷ�ļ�

sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit LED5 = P1^4;

int main()//������
{
	LED1 = 0;
	LED2 = 0;
	LED5 = 0;
	
	return 0; 
}