/*****************************************************************
������:��ҵ���������
����:��С��
�������:2013��10��16��10:01:12
����˵��:v1.0
*****************************************************************/
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "rtc.h" 
#include "adc.h"
#include "enc28j60.h"
#include "uip.h"
#include "uip_arp.h"
#include "tapdev.h"
#include "timer.h"
#include "timerx.h"
#include <math.h> 	
#include <string.h> 
#include "helper.h"
#include "dht11.h"
#include "IRRmote.h"

void uip_polling(void);
int OperationNum; 
u8 PacketBuf[200];
int k;
int IsDht1Init = 0;
u8 temperature;
u8 humidity;
u8 AddressCode=0;
u8 DataCode=0;
u8 LastDateCode=0;
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

///�ϲ����ݲ����Ϊ����
void MergeAndSend(int OperationNum,char* Message)
{
	Merge(OperationNum,Message);
	for(k=0;k<PacketBuf[0];k++)
	{
		tcp_server_databuf[k] = PacketBuf[k];
	}
	tcp_server_sta|=1<<5;//�����������Ҫ����
}

 int main(void)
 {
	
	u8 tcp_server_tsta=0X00;
 	uip_ipaddr_t ipaddr;

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	DHT11_Init();				//Dht11��ʼ��
	RTC_Init();				//��ʼ��RTC
	Adc_Init();				//��ʼ��ADC	  
	TIM1_PWM_Init(899,0);
	IRRemote_Init();			//������ճ�ʼ��		 	

 	while(tapdev_init())	//��ʼ��ENC28J60����
	{								   
		delay_ms(200);
	};		
	uip_init();				//uIP��ʼ��	  
 	uip_ipaddr(ipaddr, 192,168,1,16);	//���ñ�������IP��ַ
	uip_sethostaddr(ipaddr);					    
	uip_ipaddr(ipaddr, 192,168,1,1); 	//��������IP��ַ
	uip_setdraddr(ipaddr);						 
	uip_ipaddr(ipaddr, 255,255,255,0);	//������������
	uip_setnetmask(ipaddr);

	uip_listen(HTONS(1200));			//����1200�˿�,����TCP Server

	while (1)
	{
		uip_polling();	//����uip�¼���������뵽�û������ѭ������  
		
		if(tcp_server_tsta!=tcp_server_sta)//TCP Server״̬�ı�
		{															 

 			if(tcp_server_sta&(1<<6))	//�յ�������
			{
				if(CheckData(tcp_server_databuf))
				{
					OperationNum = GetOperation(tcp_server_databuf);
					tcp_server_sta&=~(1<<6);		//��������Ѿ�������
					//Clear(tcp_server_databuf);					
					switch(OperationNum)
					{
							//��ʪ�Ȼ�ȡ
							case 0:
									if(tcp_server_sta&(1<<7))	//���ӻ�����
									{
										if(DHT11_Read_Data()==1)
										{
											MergeAndSend(0,"dht1Wrong");
										}
										else
										{
											MergeDHT1();
											for(k=0;k<PacketBuf[0];k++)
											{
												tcp_server_databuf[k] = PacketBuf[k];
											}
											tcp_server_sta|=1<<5;//�����������Ҫ����
										}								
										}										
								break;
								//IO�����
							case 1:
									if(tcp_server_sta&(1<<7))	//���ӻ�����
									{
										switch(GetDigitalNum(tcp_server_databuf))
										{
											case 1:
												LED1=GetDigitalLevel(tcp_server_databuf);
												MergeAndSend(1,"SetOK");
												break;
											case 2:
												LED2=GetDigitalLevel(tcp_server_databuf);
												MergeAndSend(1,"SetOK");
												break;
											case 3:
												LED3=GetDigitalLevel(tcp_server_databuf);
												MergeAndSend(1,"SetOK");
												break;
											case 4:
												LED4=GetDigitalLevel(tcp_server_databuf);
												MergeAndSend(1,"SetOK");
												break;
											case 5:
												LED5=GetDigitalLevel(tcp_server_databuf);
												MergeAndSend(1,"SetOK");
												break;
											case 6:
												LED6=GetDigitalLevel(tcp_server_databuf);
												MergeAndSend(1,"SetOK");
												break;
											case 7:
												LED5=GetDigitalLevel(tcp_server_databuf);
												MergeAndSend(1,"SetOK");
												break;
											case 8:
												LED6=GetDigitalLevel(tcp_server_databuf);
												MergeAndSend(1,"SetOK");
												break;
											default:
												break;
										}
									}
								break;
								//��ȡģ��˿ں����ֶ˿�״̬
							case 2:
									if(tcp_server_sta&(1<<7))
									{
										MergeDigitalAndAnalog();
										for(k=0;k<PacketBuf[0];k++)
										{
											tcp_server_databuf[k] = PacketBuf[k];
										}
										tcp_server_sta|=1<<5;//�����������Ҫ����
									}
									break;
									//������
							case 3:
									if(tcp_server_sta&(1<<7))
									{
										switch(GetPinNum(tcp_server_databuf))
										{
											case 1:												
													TIM_SetCompare1(TIM1,GetPWMData(tcp_server_databuf));											
													delay_ms(10);																							
												break;
											case 2:
													TIM_SetCompare2(TIM1,GetPWMData(tcp_server_databuf));
													delay_ms(10);
												break;
											case 3:
													TIM_SetCompare3(TIM1,GetPWMData(tcp_server_databuf));
													delay_ms(10);
												break;
											case 4:
													TIM_SetCompare4(TIM1,GetPWMData(tcp_server_databuf));
													delay_ms(10);
												break;
											default:
												break;											
										}
									}
									break;
									//�������
							case 4:
									if(tcp_server_sta&(1<<7))
									{
											DataCode=0;
											k=1000;
											while(k--)
											{
												IRRemote_Scan();
												if(DataCode)
												{
													LastDateCode=DataCode;
													MergeIR();
													for(k=0;k<PacketBuf[0];k++)
													{
														tcp_server_databuf[k] = PacketBuf[k];
													}
													tcp_server_sta|=1<<5;//�����������Ҫ����
													break;
												}
												delay_ms(10);
											}
											if(DataCode==0)
											{
												MergeAndSend(4,"Failed");
											}
											delay_ms(10);
									}
									break;
									//���ⷢ��
							case 5:
									if(tcp_server_sta&(1<<7))
									{
											if(LastDateCode)
											{
												IRRmote_Send(AddressCode,LastDateCode);
												MergeAndSend(5,"Sent");
											}
											else
											{
												MergeAndSend(5,"Failed");
											}
											delay_ms(10);
									}
									break;
							default:
								break;
						}
				}
				else
				{
					MergeAndSend(0,"Miss");					
				}
			}							
			tcp_server_tsta=tcp_server_sta;
		}
		delay_ms(1);
	}  
} 
 
//uip�¼�������
//���뽫�ú��������û���ѭ��,ѭ������.
void uip_polling(void)
{
	u8 i;
	static struct timer periodic_timer, arp_timer;
	static u8 timer_ok=0;	 
	if(timer_ok==0)//����ʼ��һ��
	{
		timer_ok = 1;
		timer_set(&periodic_timer,CLOCK_SECOND/2);  //����1��0.5��Ķ�ʱ�� 
		timer_set(&arp_timer,CLOCK_SECOND*10);	   	//����1��10��Ķ�ʱ�� 
	}				 
	uip_len=tapdev_read();	//�������豸��ȡһ��IP��,�õ����ݳ���.uip_len��uip.c�ж���
	if(uip_len>0) 			//������
	{   
		//����IP���ݰ�(ֻ��У��ͨ����IP���Żᱻ����) 
		if(BUF->type == htons(UIP_ETHTYPE_IP))//�Ƿ���IP��? 
		{
			uip_arp_ipin();	//ȥ����̫��ͷ�ṹ������ARP��
			uip_input();   	//IP������
			//������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ��� uip_len > 0
			//��Ҫ���͵�������uip_buf, ������uip_len  (����2��ȫ�ֱ���)		    
			if(uip_len>0)//��Ҫ��Ӧ����
			{
				uip_arp_out();//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
				tapdev_send();//�������ݵ���̫��
			}
		}else if (BUF->type==htons(UIP_ETHTYPE_ARP))//����arp����,�Ƿ���ARP�����?
		{
			uip_arp_arpin();
 			//������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ���uip_len>0
			//��Ҫ���͵�������uip_buf, ������uip_len(����2��ȫ�ֱ���)
 			if(uip_len>0)tapdev_send();//��Ҫ��������,��ͨ��tapdev_send����	 
		}
	}else if(timer_expired(&periodic_timer))	//0.5�붨ʱ����ʱ
	{
		timer_reset(&periodic_timer);		//��λ0.5�붨ʱ�� 
		//��������ÿ��TCP����, UIP_CONNSȱʡ��40��  
		for(i=0;i<UIP_CONNS;i++)
		{
			uip_periodic(i);	//����TCPͨ���¼�  
	 		//������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ���uip_len>0
			//��Ҫ���͵�������uip_buf, ������uip_len (����2��ȫ�ֱ���)
	 		if(uip_len>0)
			{
				uip_arp_out();//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
				tapdev_send();//�������ݵ���̫��
			}
		}
#if UIP_UDP	//UIP_UDP 
		//��������ÿ��UDP����, UIP_UDP_CONNSȱʡ��10��
		for(i=0;i<UIP_UDP_CONNS;i++)
		{
			uip_udp_periodic(i);	//����UDPͨ���¼�
	 		//������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ���uip_len>0
			//��Ҫ���͵�������uip_buf, ������uip_len (����2��ȫ�ֱ���)
			if(uip_len > 0)
			{
				uip_arp_out();//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
				tapdev_send();//�������ݵ���̫��
			}
		}
#endif 
		//ÿ��10�����1��ARP��ʱ������ ���ڶ���ARP����,ARP��10�����һ�Σ��ɵ���Ŀ�ᱻ����
		if(timer_expired(&arp_timer))
		{
			timer_reset(&arp_timer);
			uip_arp_timer();
		}
	}
}
