     ORG 0000H    ;������ľ�����ת���ŵ���ַ0100H
	 AJMP MAIN    ;������ת��������
	 ORG 0100H    ;����������ŵ���ַ0100H
MAIN:SETB TR0     ;�򿪶�ʱ��0
     MOV R7,#42   ;����ѭ����������֤��ʱʱ��
LOOP:MOV P1,A     ;��A�е�������P1��
     MOV TMOD,#01H;���ö�ʱ��������ʽΪ��ʽ1
	 MOV TH0,#00H ;���ø߰�λ
	 MOV TL0,#00H ;���õͰ�λ
	 JNB TF0,$    ;��û�������ȴ�
     CLR TF0	  ;��������־λ
     DJNZ R7,LOOP ;��R7Ϊ����ת��LOOP
     CPL A        ;��Aȡ��
	 SJMP MAIN    ;������ת��MAIN
	 END          ;�������