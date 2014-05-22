/*****************************************************************
������:PWM��������
����:��С��
�������:2013��10��16��10:01:12
����˵��:v1.0
*****************************************************************/
#include "timerx.h"
#include "led.h"
#include "usart.h"
 
u32 uip_timer=0;//uip ��ʱ����ÿ10ms����1.

//��ʱ��6�жϷ������	 
void TIM6_IRQHandler(void)
{ 	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
  	uip_timer++;//uip��ʱ������1	
	} 
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
				    		  			    	    
}
 
//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM6_Int_Init(u16 arr,u16 psc)
{	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig( TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//ʹ�ܶ�ʱ��6���´����ж�
 
	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx����
 	
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 								 
}

//TIM1 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitTypeDef TIMOCInitStructure;

	 GPIO_DeInit(GPIOA);
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;//�����������
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//ʹ�ܶ˿�ʱ��A
	 GPIO_Init(GPIOA, &GPIO_InitStructure);


	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	 TIM_DeInit(TIM1);
	 TIM_InternalClockConfig(TIM1);
	 TIM_TimeBaseStructure.TIM_Period=arr;//ARR��ֵ����10K
	 TIM_TimeBaseStructure.TIM_Prescaler=psc;
	 TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	 TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	 
	 
	 TIMOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //PWMģʽ1���
	 TIMOCInitStructure.TIM_Pulse =0;//ռ�ձ�=(CCRx/ARR)*100%
	 TIMOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM����Ƚϼ��Ը�
	 TIMOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ�����״̬
	 
	 TIM_OC1Init(TIM1, &TIMOCInitStructure);
	 TIM_OC2Init(TIM1, &TIMOCInitStructure);
	 TIM_OC3Init(TIM1, &TIMOCInitStructure);
	 TIM_OC4Init(TIM1, &TIMOCInitStructure);
	 TIM_CtrlPWMOutputs(TIM1,ENABLE);
	 TIM_Cmd(TIM1, ENABLE); //����ʱ��
}
