	   ORG  0000H     ;������ľ�����ת���ŵ���ַ0100H
	   AJMP MAIN      ;������ת��������
	   ORG  0003H     ;������ľ�����ת���ŵ���ַ0003H
	   AJMP INT	      ;������ת��INT
	   ORG  0100H     ;����������ŵ���ַ0100H
MAIN:  SETB EX0       ;�����ⲿ�ж�0�½��ش���
       SETB EA        ;�����ж�
	   SJMP $         ;�ȴ��ж�
	   ORG  0200H	  ;����������ŵ���ַ0200H	   
INT:   MOV  R0,#08H   ;ѭ���˴�
       MOV  A,#01H    ;��01H������� 0000 0001���λ�ĵ���
LIGHT: MOV  P1,A      ;��A�е�������P1��
       MOV  R2,#199   ;����ѭ����ʱ
LOOPS: MOV  B,#250    ;T=1us
LOOPR: DJNZ B,LOOPR   ;2T=2us
       DJNZ R2,LOOPS  ;2T=2us
	   RL   A         ;ѭ������
       DJNZ R0,LIGHT  ;������ת�Ƶ�LIGHT
	   RETI           ;�жϷ���
	   END            ;�������
