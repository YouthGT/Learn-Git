/***********������***********/
	   ORG  0000H    ;�������
       MOV  A,#0FFH  ;ȫ����һ
      ;SETB  C      ;��CY��һ
	   CLR   C       ;��CY����
LIGHT: RLC  A        ;A�е�������λѭ������
	   MOV  P2,A     ;��A�е�������Px��
       CALL DELAY    ;������ʱ����
       AJMP LIGHT    ;������ת�Ƶ�LIGHT
/**********��ʱ����**********/
DELAY: MOV  R2,#199  ;
LOOPS: MOV  B,#250   ;T=1us
LOOPR: DJNZ B,LOOPR  ;2T=2us
       DJNZ R2,LOOPS ;2T=2us
	   RET
	   END



