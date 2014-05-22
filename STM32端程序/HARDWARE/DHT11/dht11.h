/*****************************************************************
������:DHT11�����������
����:��С��
�������:2013��10��16��10:01:12
����˵��:v1.0
*****************************************************************/
#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
 
//IO��������
#define DHT11_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
#define DHT11_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO��������											   
#define	DHT11_DQ_OUT PGout(11) //���ݶ˿�	PA0 
#define	DHT11_DQ_IN  PGin(11)  //���ݶ˿�	PA0 


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(void);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif















