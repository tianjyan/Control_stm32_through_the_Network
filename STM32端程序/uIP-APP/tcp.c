/*****************************************************************
������:TCP����
����:��С��
�������:2013��10��16��10:01:12
����˵��:v1.0
*****************************************************************/
#include "sys.h"
#include "usart.h"	 		   
#include "uip.h"	    
#include "enc28j60.h"
#include "httpd.h"
#include "tcp.h"

//TCPӦ�ýӿں���(UIP_APPCALL)
//���TCP Server����
void tcp_appcall(void)
{	
  	
	switch(uip_conn->lport)
	{
		case HTONS(1200):
		    tcp_server_appcall(); 
			break;
		default:						  
		    break;
	}		    
}
//��ӡ��־��
void uip_log(char *m)
{			    
	printf("uIP log:%s\r\n",m);
}

























