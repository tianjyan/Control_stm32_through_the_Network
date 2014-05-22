/*****************************************************************
������:���ݰ��������
����:��С��
�������:2013��10��16��10:01:12
����˵��:v1.0
*****************************************************************/

#ifndef __HELPER_H
#define __HELPER_H	
#include "stm32f10x.h"

int CheckData(u8 DataBuf[200]);
int CheckPwd(u8 DataBuf[200],int DataLength);
int GetOperation(u8 DataBuf[200]);
void Clear(u8 DataBuf[200]);
void MergeIR(void);
void Merge(int OperationNum, char* message);
void MergeDHT1(void);
int GetDigitalNum(u8 DataBuf[200]);
int GetDigitalLevel(u8 DataBuf[200]);
char ToHex(int i);
void GetAngolags(u8 ch,int chNum);
void MergeDigitalAndAnalog(void);
int GetPWMData(u8 DataBuf[200]);
int GetPinNum(u8 DataBuf[200]);
#endif
