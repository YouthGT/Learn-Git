#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char 
	
sbit WE = P2^7;
sbit DU = P2^6;
sbit key_s2 = P3^0;
sbit key_s3 = P3^1;

uchar num = 0;

void delay(uint z);

//����������ܶ�ѡ����0-9
uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//�����鴢����ROM��

void main()
{
	WE = 1;//��λѡ������
	P0 = 0xfe;//1111 1110
	WE = 0;//�ر�λѡ������
	
	
	while(1)
	{
		if(key_s2 == 0)
		{
			delay(20);//ȥ����������
			if(key_s2 == 0)
			{
				if(num != 9)
					num++;
				    DU = 1;
					P0 = table[num];//���¾ͱ仯
					DU = 0;
					while(!key_s2);//���ּ��
			}
		}

		
		if(key_s3 == 0)
		{	
			delay(20);//ȥ����������
			if(key_s3 == 0)
			{
				if(num > 0)
					num--;
					DU = 1;
					P0 = table[num];//���¾ͱ仯
					DU = 0;
					while(!key_s3);//���ּ��
			}
		}

			
			//ˢ����ʾ			
			DU = 1;
			P0 = table[num];
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