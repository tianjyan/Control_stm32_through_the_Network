/*****************************************************************
������:���������������
����:��С��
�������:2013��10��16��10:01:12
����˵��:v1.0
*****************************************************************/
#ifndef __IRRMOTE_H
#define __IRRMOTE_H
#include "sys.h"

#define RDATA PBin(9)	 //�������������

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
#define REMOTE_ID 0      		   

extern u8 RmtCnt;	//�������µĴ���
extern u8 AddressCode;
extern u8 DataCode;
void IRRemote_Init(void);    //���⴫��������ͷ���ų�ʼ��
void IRRemote_Scan(void);	
void IRRmote_Send(u8 addressCode,u8 dataCode);
void IRRmote_Send_Byte(u8 getdata);
#endif
