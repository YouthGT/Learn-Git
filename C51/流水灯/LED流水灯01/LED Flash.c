#include <reg52.h>//����ͷ�ļ�
	//λ����
unsigned int i ;//0~65535


int mian()//main���������ѭ��
	
{
	while (1)
	{
		P1 = 0xaa;//P1���������
		i = 65535;
		while(i--);//����ʱ�䳤һ��
		P1 = 0xff;//1111 1111 �˸��ߵ�ƽ Ϩ��˸�LED��
		i = 65535;
		while(i--);//���ʱ�䳤һ��
	}

	
	return 0;
}