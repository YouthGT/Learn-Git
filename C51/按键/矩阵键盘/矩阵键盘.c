#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char 
	
sbit WE = P2^7;//λѡ
sbit DU = P2^6;//��ѡ
sbit beep = P2^3;//������

uchar num = 0;//�������ʾ��ֵ
uchar KeyValue;//����ֵ

void delay(uint z);
void KeyScan( );

//����������ܶ�ѡ��
uchar code table[] = {
//0   1     2    3    4    5   6    7     8
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
//9    A   B     C    D    E     F   H    L
0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x38,
//N    U   -    Ϩ��
0x37,0x3e,0x40,0x00};

void main()
{
	WE = 1;//��λѡ������
	P0 = 0xfe;//1111 1110
	WE = 0;//�ر�λѡ������
	
	
	while(1)
	{
//			beep = ~beep;//������

	        KeyScan();
			
			DU = 1;
			P0 = table[KeyValue];
			DU = 0;	

	}
}

//���뼶��ʱ��������
void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 
//����ɨ�躯��
void KeyScan( )
{
	P3 = 0xf0;//��ɨ��
	if(P3 != 0xf0)//�жϰ����Ƿ񱻰���
	{
		delay(10);//��ʱ10ms
		if(P3 != 0xf0)//�жϰ����Ƿ񱻰���
			{
				switch(P3)
				{
					case 0xe0:KeyValue = 0;
					break;
					case 0xd0:KeyValue = 1;
					break;
					case 0xb0:KeyValue = 2;
					break;
					case 0x70:KeyValue = 3;
					break;
				
				}
				P3 = 0x0f;//��ɨ��
				switch(P3)
				{
					case 0x0e:KeyValue = KeyValue;
					break;
					case 0x0d:KeyValue = KeyValue + 4;
					break;
					case 0x0b:KeyValue = KeyValue + 8;
					break;
					case 0x07:KeyValue = KeyValue + 12;
					break;
				}
				while(P3 != 0x0f);//���ּ��
			}
	}
	P3 = 0xff;//��������ɨ��
	if(P3 = 0xff) 
	{
		delay(10);
		if(P3 != 0xff)//�ж϶��������Ƿ���
			switch(P3)
			{
				case 0xfe: KeyValue = 16;  break;
				case 0xfd: KeyValue = 17;  break;
				case 0xfb: KeyValue = 18;  break;
				case 0xf7: KeyValue = 19;  break;

			}
			while(P3 != 0xff);//���ּ��
		
	}
}