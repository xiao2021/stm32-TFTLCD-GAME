#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "tftlcd.h"
#include "picture.h"
#include "key.h"
#include "touch.h"
#include "logic.h"
#include "openmv_data.h"
#include "music.h"


void LOGIC_FLOW2();

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void kai_display()  //������ʾ
{
	FRONT_COLOR=BLACK;
//	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"asdsda");
//	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"www.prechin.net");
//	  LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Welcome!!");	
	
		
    FRONT_COLOR = BLACK;  //����������ɫ
    LCD_ShowString(10, 50, tftlcd_data.width, tftlcd_data.height, 24, "Welcome!!");
	
	  delay_ms(500);
	
	  LCD_ShowString(10, 100, tftlcd_data.width, tftlcd_data.height, 24, "Select mode :");
    LCD_ShowString(10, 150, tftlcd_data.width, tftlcd_data.height, 24, "slow velocity mode");
    LCD_ShowString(10, 220, tftlcd_data.width, tftlcd_data.height, 24, "quick velocity mode");  //��������λ�ô�С
	  LCD_ShowString(10, 290, tftlcd_data.width, tftlcd_data.height, 24, "Somatosensory mode"); 
	
	  LCD_Fill(7,130,300,130,BLACK);
	  LCD_Fill(7,200,300,200,BLACK);
	  LCD_Fill(7,270,300,270,BLACK);
    LCD_Fill(7,340,300,340,BLACK);
	
	  LCD_Fill(7,130,7,340,BLACK);
//		LCD_Fill(180,130,180,270,BLACK);
		LCD_Fill(300,130,300,340,BLACK);       //��X 300-300 Y 130-270�ķ�Χ������ɫ
}

void TIM3_IRQHandler(void)            //��ʱ���жϴ�����
{
    if (TIM3->SR & TIM_SR_UIF) {
					LOGIC_FLOW();
					SQUARE_FLOW_SELECT();
					LED1=!LED1;
        // ������ִ��ÿ��2����Ҫִ�еĴ���
        TIM3->SR &= ~TIM_SR_UIF;  // ����жϱ�־λ
    }
}
int carry_num = 10000;
void TIM3_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;  // ʹ�� TIM3 ʱ��
    TIM3->PSC = 7200 - 1;  // ��Ƶϵ������ʱ��ʱ��Ϊ 72MHz / 7200 = 10KHz
    //TIM3->ARR = 20000 - 1;  // �Զ�����ֵ����ʱ���������� 0 ��ʼ�������� 20000 ʱ����������ж�
	TIM3->ARR = carry_num - 1;
		if(carry_num > 2000)                                                                           //???????????????????????????????????
	{carry_num=carry_num - 1000;}
    TIM3->DIER |= TIM_DIER_UIE;  // ʹ�ܸ����ж�
    //  // ʹ�� TIM3 �ж�
    TIM3->CR1 |= TIM_CR1_CEN;  // ʹ�ܶ�ʱ��
}

extern int rec_flag;
extern uint8_t SEND_TO_LCD;
extern int LOGIC_TABLE[4][4];
extern int score;
int main()
{ 
	
	
	u8 key;
	u8 i=0;
	u16 color=0;
	
	TIM3_Init();
	HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(RCC_PLL_MUL9); //����ʱ��,72M
	SysTick_Init(72);
	USART1_Init(115200);
	LED_Init();
	TFTLCD_Init();			//LCD��ʼ��
	KEY_Init();
	TP_Init();
	Music_GPIO_Init();//��������

	
	  kai_display();
	
    int mode_selected = 0;

    while (mode_selected == 0) 
			{
        if (TP_Scan(0)) 
					{
            if (tp_dev.x[0] > 7 && tp_dev.x[0] < 300 && tp_dev.y[0] > 130 && tp_dev.y[0] < 200) 
							{
								mode_selected = 1;
								LCD_Fill(8,131,299,199,GREEN);
								delay_ms(300);
								LCD_Fill(8,131,299,199,WHITE);
                // ����ģʽ

              } 
            if (tp_dev.x[0] > 7 && tp_dev.x[0] < 300 && tp_dev.y[0] > 200 && tp_dev.y[0] < 270) 
						  {
                // ����ģʽ
                mode_selected = 2;
								LCD_Fill(8,201,299,269,GREEN);
								delay_ms(300);
								LCD_Fill(8,201,299,269,WHITE);
              }
						if (tp_dev.x[0] > 7 && tp_dev.x[0] < 300 && tp_dev.y[0] > 270 && tp_dev.y[0] < 340) 
						  {
                mode_selected = 3;
								LCD_Fill(8,271,299,339,GREEN);
								delay_ms(300);
								LCD_Fill(8,271,299,339,WHITE);
              }
          }
      }
			delay_ms(300);
	
	 if (mode_selected == 1) 
		{
			  FRONT_COLOR = BLACK;
        LCD_ShowString(10, 100, tftlcd_data.width, tftlcd_data.height, 24, "Mode:  slow velocity");
			
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 3...");
        delay_ms(1000);
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 2...");
        delay_ms(1000);
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 1...");
        delay_ms(1000); 
			  LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Good luck with the game !");
			  delay_ms(1000); 
//			Music_GPIO_Init();//��������
			  TIM3->ARR = TIM3->ARR *1.5;
       
    } else if (mode_selected == 2)
		
		{   
			  FRONT_COLOR = BLACK;
        LCD_ShowString(10, 100, tftlcd_data.width, tftlcd_data.height, 24, "Mode:  quick velocity");
			
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 3...");
        delay_ms(1000);
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 2...");
        delay_ms(1000);
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 1...");
        delay_ms(1000);
			  LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Good luck with the game !");
			  delay_ms(1000); 
				TIM3->ARR = TIM3->ARR/2 ;  // ��ʱ���������� 0 ��ʼ�������� 10000 ����ʱ����������жϣ��������ٶ����һ��

    }
else if (mode_selected == 3)
		
		{   
			  FRONT_COLOR = BLACK;
        LCD_ShowString(10, 100, tftlcd_data.width, tftlcd_data.height, 24, "Mode:  Somatosensory mode");
			
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 3...");
        delay_ms(1000);
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 2...");
        delay_ms(1000);
        LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Starting in 1...");
        delay_ms(1000);
			  LCD_ShowString(10, 380, tftlcd_data.width, tftlcd_data.height, 24, "Good luck with the game !");
			  delay_ms(1000); 
			  TIM3->ARR = TIM3->ARR *1.2;

    }
	


//		
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); //������
//	delayms(50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); //������
Draw_border();
NVIC_EnableIRQ(TIM3_IRQn);
int status_game = 1;

if(mode_selected == 1||mode_selected == 2)
{
while(1)
	{
			if(TP_Scan(0)){
				
			if(tp_dev.x[0]<80&&tp_dev.y[0]>363&&LOGIC_TABLE[3][0]==1){
				LCD_Fill(6,363,80,475,GREEN);
				LOGIC_TABLE[3][0]=0;
				score++;
			}
				if(tp_dev.x[0]<80&&tp_dev.y[0]>363&&LOGIC_TABLE[3][1]==1){
				LCD_Fill(6,363,80,475,RED);
				delay_ms(300);
				LCD_Fill(6,363,80,475,WHITE);
			  LOGIC_FLOW2();
				}
				if(tp_dev.x[0]<80&&tp_dev.y[0]>363&&LOGIC_TABLE[3][2]==1){
				LCD_Fill(6,363,80,475,RED);
				delay_ms(300);
				LCD_Fill(6,363,80,475,WHITE);
        LOGIC_FLOW2();					
				}
				if(tp_dev.x[0]<80&&tp_dev.y[0]>363&&LOGIC_TABLE[3][3]==1){
				LCD_Fill(6,363,80,475,RED);
				delay_ms(300);
				LCD_Fill(6,363,80,475,WHITE);
        LOGIC_FLOW2();					
				}
						
				
				
			if(tp_dev.x[0]<158&&tp_dev.x[0]>83&&tp_dev.y[0]>363&&LOGIC_TABLE[3][1]==1){
				LCD_Fill(83,363,158,475,GREEN);
				LOGIC_TABLE[3][1]=0;
				score++;
				}
			if(tp_dev.x[0]<158&&tp_dev.x[0]>83&&tp_dev.y[0]>363&&LOGIC_TABLE[3][0]==1){
				LCD_Fill(83,363,158,475,RED);
				delay_ms(300);
				LCD_Fill(83,363,158,475,WHITE);
        LOGIC_FLOW2();				
				}
			if(tp_dev.x[0]<158&&tp_dev.x[0]>83&&tp_dev.y[0]>363&&LOGIC_TABLE[3][2]==1){
				LCD_Fill(83,363,158,475,RED);
				delay_ms(300);
				LCD_Fill(83,363,158,475,WHITE);
        LOGIC_FLOW2();				
			}
		 if(tp_dev.x[0]<158&&tp_dev.x[0]>83&&tp_dev.y[0]>363&&LOGIC_TABLE[3][3]==1){
				LCD_Fill(83,363,158,475,RED);
			 delay_ms(300);
			 LCD_Fill(83,363,158,475,WHITE);
        LOGIC_FLOW2();			 
			 
				}
				
				
				
			if(tp_dev.x[0]<235&&tp_dev.x[0]>161&&tp_dev.y[0]>363&&LOGIC_TABLE[3][2]==1){
				LCD_Fill(161,363,235,475,GREEN);
				LOGIC_TABLE[3][2]=0;
				score++;
				}
			if(tp_dev.x[0]<235&&tp_dev.x[0]>161&&tp_dev.y[0]>363&&LOGIC_TABLE[3][0]==1){
				LCD_Fill(161,363,235,475,RED);
				delay_ms(300);
				LCD_Fill(161,363,235,475,WHITE);
        LOGIC_FLOW2();				
			}
			if(tp_dev.x[0]<235&&tp_dev.x[0]>161&&tp_dev.y[0]>363&&LOGIC_TABLE[3][1]==1){
				LCD_Fill(161,363,235,475,RED);
				delay_ms(300);
				LCD_Fill(161,363,235,475,WHITE);
        LOGIC_FLOW2();				
			}
			if(tp_dev.x[0]<235&&tp_dev.x[0]>161&&tp_dev.y[0]>363&&LOGIC_TABLE[3][3]==1){
				LCD_Fill(161,363,235,475,RED);
				delay_ms(300);
				LCD_Fill(161,363,235,475,WHITE);
        LOGIC_FLOW2();				
			}
								
								
												
				
			if(tp_dev.x[0]<315&&tp_dev.x[0]>238&&tp_dev.y[0]>363&&LOGIC_TABLE[3][3]==1){
				LCD_Fill(238,363,315,475,GREEN);
				LOGIC_TABLE[3][3]=0;
				score++;
				}
      if(tp_dev.x[0]<315&&tp_dev.x[0]>238&&tp_dev.y[0]>363&&LOGIC_TABLE[3][0]==1){
				LCD_Fill(238,363,315,475,RED);
				delay_ms(300);
				LCD_Fill(238,363,315,475,WHITE);
        LOGIC_FLOW2();				
			 }	
			if(tp_dev.x[0]<315&&tp_dev.x[0]>238&&tp_dev.y[0]>363&&LOGIC_TABLE[3][1]==1){
				LCD_Fill(238,363,315,475,RED);
				delay_ms(300);
				LCD_Fill(238,363,315,475,WHITE);
        LOGIC_FLOW2();				
			 }	
		  if(tp_dev.x[0]<315&&tp_dev.x[0]>238&&tp_dev.y[0]>363&&LOGIC_TABLE[3][2]==1){
				LCD_Fill(238,363,315,475,RED);
				delay_ms(300);
				LCD_Fill(238,363,315,475,WHITE);
        LOGIC_FLOW2();				
			 }	

}
}
	}

else{
	Receive_GPIO_Init();
while(1)
{
	if(rec_flag){
				
				if(SEND_TO_LCD==1&&LOGIC_TABLE[3][0]==1){
					LCD_Fill(6,363,80,475,GREEN);
					LOGIC_TABLE[3][0]=0;
					SEND_TO_LCD = 0;
					score++;
					}
				if(SEND_TO_LCD==2&&LOGIC_TABLE[3][1]==1){
					LCD_Fill(83,363,158,475,GREEN);
					LOGIC_TABLE[3][1]=0;
					SEND_TO_LCD = 0;
					score++;
					}
				if(SEND_TO_LCD==3&&LOGIC_TABLE[3][2]==1){
					LCD_Fill(161,363,235,475,GREEN);
					LOGIC_TABLE[3][2]=0;
					SEND_TO_LCD = 0;
					score++;
					}
				if(SEND_TO_LCD==4&&LOGIC_TABLE[3][3]==1){
					LCD_Fill(238,363,315,475,GREEN);
					LOGIC_TABLE[3][3]=0;
					SEND_TO_LCD = 0;
					score++;
					}
				
}

}
}
}