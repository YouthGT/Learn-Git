#include <reg52.h>
#include <intrins.h>

#define uint  unsigned int //�궨����uxxx�滻unsigned xxx
#define uchar unsigned char//typedef ������������ �µ��������ͣ����Ҫ�ӷֺ�	

uchar temp;//LED����ر���

int delay(uint z);//������ʱ����

int main()//�����������ѭ��
{
	temp=0xfe;
	P1=temp;//1111 1110
	delay(10);
	while (1)
	{
			temp=_crol_(temp,1);//ѭ������һλ
			P1=temp;
			delay(100);	
	}
	return 0;
}
//��ʱ����
int delay(uint z)//���뼶��ʱ����
{
	uint x,y;
	for (x=z;x>0;x--)//һ�����ʡ�Ի�����
		for (y=114;y>0;y--);
	return 0;
}