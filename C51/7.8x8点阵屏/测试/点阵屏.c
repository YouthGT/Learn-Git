#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit DIO  = P3^4;//�������ݿ�
sbit S_CLK = P3^5;//��λ�Ĵ���ʱ��
sbit R_CLK = P3^6;//����Ĵ���ʱ��
 
void main()
{
  	//ROW 0x80��COL 0xfe
	uchar i, dat;
	dat = 0xfe;//��
	for(i = 0; i < 8; i++)
	{
		
		S_CLK = 0;
		R_CLK = 0;
		if(dat & 0x01)//��λ��
			DIO = 1;
		else 
			DIO = 0;
		S_CLK = 1;
		//dat = dat>>1;
		dat >>= 1;
	}
	dat = 0x80;//��
	for(i = 0; i < 8; i++)
	{
		
		S_CLK = 0;
		R_CLK = 0;
		if(dat & 0x01)//��λ��
			DIO = 1;
		else 
			DIO = 0;
		S_CLK = 1;
		//dat = dat>>1;
		dat >>= 1;
	}
	R_CLK = 1;
	while(1);
}




