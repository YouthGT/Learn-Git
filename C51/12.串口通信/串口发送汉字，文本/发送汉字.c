#include <reg52.h>
#include <stdio.h>

#define uint unsigned int
#define uchar unsigned char
	
void UARTInit();
void delay(uint z);
	
void main()
{
	UARTInit();//���ڳ�ʼ��
	while(1)
	{
		TI = 1;
		puts("����ʹ�ã�����ʹ��2021.01.23");
		while (!TI);
		TI = 0;
		delay(1000);
	}
}
//���ڳ�ʼ��
void UARTInit()
{
	SM0 = 0; SM1 = 1; //���ڹ�����ʽ1��8λUART�����ʿɱ�
	TR1 = 1;//������ʱ��1
	TMOD |=0x20;//��ʱ��1������ģʽ2 8λ�Զ���װ
	TH1 = 0xfd;
	TL1 = 0xfd;//���ò�����9600
	
}
//��ʱ����
void delay(uint z)
{
	uint x,y;
	for(x = z;x > 0;x--)
		for(y = 114; y > 0; y--);
}
/*************************************
��ע��
ʹ��printf()puts()ǰ��Ӧ�����λTI = 1��
printf()puts()  ʹ��putchar�������� �ֽڣ�һ�����������ֽڣ�

void putchar(uchar sbyte )
{
    while(��TI);   //�ȴ�������

    SBUF=sbyte;

}

���Ե�һ�ε���putcharǰûTI=1 ��Զ�ȴ�
*************************************/
