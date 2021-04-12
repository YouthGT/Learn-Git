#include <reg52.h>
#include <intrins.h>

#define uint unsigned int 
typedef unsigned char uchar;

sbit DIO = P3^4;//�������ݿ�
sbit S_CLK = P3^5;//��λ�Ĵ���ʱ��
sbit R_CLK = P3^6;//����Ĵ���ʱ��

uchar code table[5][8] = {
0xE0, 0xEE, 0x01, 0x6D, 0x01, 0x6D, 0x01, 0xEF, 
0xEF, 0xC7, 0x97, 0xF7, 0x00, 0xE7, 0xF9, 0x81,
0x81, 0x81, 0xE7, 0xE7, 0xE7, 0xC7, 0xC7, 0xE7,
0x81, 0x81, 0xC7, 0xF3, 0xF9, 0x99, 0x81, 0xC3,
0xC3, 0x81, 0x99, 0xF9, 0xE3, 0x99, 0x81, 0xC3		
};//����ַ���ȡģ��ά����

void Send_Byte(uint dat);//�����Զ��庯��

void main()//main������ѭ����������
{
    uint j,k,z,ROW;
	ROW = 0x80;//��ֵ��ʼ��
	while(1)	   //ʹ��ѭ����ʾ
	{
		for(k=0;k<5;k++)//�ֱ��������ַ�
		{
			for(z=0;z<100;z++)//��ʱ���ã���һ���ַ���ʾһ��ʱ��
			{
				for (j = 0;j<8; j++)//�ֱ���ʾ����
					{
					   Send_Byte(table[k][j]);//�����ź�����
					   Send_Byte(ROW);//�����ź����룬��һ�иߵ�ƽ
					   R_CLK = 1;//���������أ����䲢�����
					   R_CLK = 0;//Ϊ��һ��������׼��
					   ROW = _cror_(ROW,1);//����������������
					}
		     }
		}
    }
}

void Send_Byte(uint dat)//�����ֽں���
{
	uint i;
	for (i=0;i<8;i++)//���д�������
	{
		S_CLK = 0;//Ϊ��������׼��
		R_CLK = 0;//Ϊ��������׼��
		if(dat & 0x01)//��λ�����������Ϊ��
			DIO = 1;
		else
			DIO = 0;
		dat >>= 1;//���������
		S_CLK = 1;//���������������ֽ�
	}
}
