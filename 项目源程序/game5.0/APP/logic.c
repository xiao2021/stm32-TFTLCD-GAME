#include "logic.h"
#include <stdlib.h>
#include "system.h"
#include "SysTick.h"
#include "tftlcd.h"
#include <string.h>

#define BEEP_PORT GPIOB
#define BEEP_PIN GPIO_PIN_8
#define BEEP_PORT_RCC_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE()
#define BEEP PBout(8)

//#include <time.h>
int LOGIC_TABLE[4][4] = 
	  {{0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
    };
int score = 0;
int random_num[37]={0,5,9,2,0,3,2,1,0,1,35,1,5,3,7,4,3,5,67,4,1,2,3,5,6,4,8,2,3,4,5,64,8,1,8,61,6};
int i_num=0;
int status_game = 1;
void Draw_border()
{
	LCD_Fill(0,0,5,480,GRAY);
	LCD_Fill(0,0,320,5,GRAY);
	LCD_Fill(0,475,320,480,GRAY);
	LCD_Fill(315,0,320,480,GRAY);
	LCD_Fill(81,0,82,480,GRAY);
	LCD_Fill(159,0,160,480,GRAY);
	LCD_Fill(236,0,237,480,GRAY);
	LCD_Fill(0,123,320,124,GRAY);
	LCD_Fill(0,242,320,243,GRAY);
	LCD_Fill(0,361,320,362,GRAY);
}	
void LOGIC_FLOW()
{

	if(LOGIC_TABLE[3][0]==1||LOGIC_TABLE[3][1]==1||LOGIC_TABLE[3][2]==1||LOGIC_TABLE[3][3] == 1)
		
	{ NVIC_DisableIRQ(TIM3_IRQn);
		status_game = 0;
		LCD_Fill(0,0,320,480,WHITE);
		LCD_ShowString(30,120,tftlcd_data.width,tftlcd_data.height,24,"GAME OVER");
   int num = score;
   char str[10];
   int i = 0;

    while (num != 0)
		{
    int digit = num % 10;  // 取出num的最低位数字
    str[i++] = digit + '0';  // 将数字转换为字符，并存入str数组
    num /= 10;  // 将num的最低位数字去掉
    }

    str[i] = '\0';  // 字符串以'\0'结尾

   int len = strlen(str);
    char reversed_str[10];
     for (int j = 0; j < len; j++)
		 { 
      reversed_str[j] = str[len - j - 1];
      }
    reversed_str[len] = '\0';
    LCD_ShowString(10, 300, tftlcd_data.width, tftlcd_data.height, 24, "ultimate score is:");
    LCD_ShowString(245, 300, tftlcd_data.width, tftlcd_data.height, 24, reversed_str);
	  
			GPIO_InitTypeDef GPIO_InitStructure;
      BEEP_PORT_RCC_ENABLE;
      GPIO_InitStructure.Pin=BEEP_PIN;
      GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP; //推挽输出
      GPIO_InitStructure.Pull=GPIO_PULLUP; //上拉
      GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH; //高速
      HAL_GPIO_Init(BEEP_PORT,&GPIO_InitStructure);
      HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_SET);
			delay_ms(1000);
			HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_RESET);
			
	}
	int i;
	for (i = 0; i < 4; i++) {
		LOGIC_TABLE[3][i] = LOGIC_TABLE[2][i];
		LOGIC_TABLE[2][i] = LOGIC_TABLE[1][i];
		LOGIC_TABLE[1][i] = LOGIC_TABLE[0][i];
		LOGIC_TABLE[0][i] = 0;
	}
	LOGIC_TABLE[0][random_num[i_num]%4] = 1;
	
	i_num++;
}
void LOGIC_FLOW2()
{		
    NVIC_DisableIRQ(TIM3_IRQn);
		status_game = 0;
		LCD_Fill(0,0,320,480,WHITE);
		LCD_ShowString(30,120,tftlcd_data.width,tftlcd_data.height,24,"GAME OVER");
   int num = score;
   char str[10];
   int k = 0;

    while (num != 0)
		{
    int digit = num % 10;  // 取出num的最低位数字
    str[k++] = digit + '0';  // 将数字转换为字符，并存入str数组
    num /= 10;  // 将num的最低位数字去掉
    }

    str[k] = '\0';  // 字符串以'\0'结尾

   int len = strlen(str);
    char reversed_str[10];
     for (int j = 0; j < len; j++)
		 { 
      reversed_str[j] = str[len - j - 1];
      }
    reversed_str[len] = '\0';
    LCD_ShowString(10, 300, tftlcd_data.width, tftlcd_data.height, 24, "ultimate score is:");
    LCD_ShowString(245, 300, tftlcd_data.width, tftlcd_data.height, 24, reversed_str);
}

void func1() { LCD_Fill(6,6,80,122,BLACK); }
void func2() { LCD_Fill(83,6,158,122,BLACK); }
void func3() { LCD_Fill(161,6,235,122,BLACK); }
void func4() { LCD_Fill(238,6,315,122,BLACK); }
void func5() { LCD_Fill(6,125,80,241,BLACK); }
void func6() {LCD_Fill(83,125,158,241,BLACK);  }
void func7() {LCD_Fill(161,125,235,241,BLACK);  }
void func8() {LCD_Fill(238,125,315,241,BLACK);  }
void func9() { LCD_Fill(6,244,80,360,BLACK); }
void func10() { LCD_Fill(83,244,158,360,BLACK); }
void func11() { LCD_Fill(161,244,235,360,BLACK); }
void func12() { LCD_Fill(238,244,315,360,BLACK); }
void func13() { LCD_Fill(6,363,80,475,BLACK); }
void func14() { LCD_Fill(83,363,158,475,BLACK); }
void func15() { LCD_Fill(161,363,235,475,BLACK); }
void func16() { LCD_Fill(238,363,315,475,BLACK); }

void func1w() { LCD_Fill(6,6,80,122,WHITE); }
void func2w() { LCD_Fill(83,6,158,122,WHITE); }
void func3w() { LCD_Fill(161,6,235,122,WHITE); }
void func4w() { LCD_Fill(238,6,315,122,WHITE); }
void func5w() { LCD_Fill(6,125,80,241,WHITE); }
void func6w() {LCD_Fill(83,125,158,241,WHITE);  }
void func7w() {LCD_Fill(161,125,235,241,WHITE);  }
void func8w() {LCD_Fill(238,125,315,241,WHITE);  }
void func9w() { LCD_Fill(6,244,80,360,WHITE); }
void func10w() { LCD_Fill(83,244,158,360,WHITE); }
void func11w() { LCD_Fill(161,244,235,360,WHITE); }
void func12w() { LCD_Fill(238,244,315,360,WHITE); }
void func13w() { LCD_Fill(6,363,80,475,WHITE); }
void func14w() { LCD_Fill(83,363,158,475,WHITE); }
void func15w() { LCD_Fill(161,363,235,475,WHITE); }
void func16w() { LCD_Fill(238,363,315,475,WHITE); }


void SQUARE_FLOW_SELECT()
{
		if(status_game == 1)
		{
			SQUARE_FLOW();
			}
}
void SQUARE_FLOW()  //画方块
{
		void (*func_ptr[4][4])() = {{func1, func2, func3, func4},
                                 {func5, func6, func7, func8},
                                 {func9, func10, func11, func12},
                                 {func13, func14, func15, func16}};
		
		void (*func_ptrw[4][4])() = {{func1w, func2w, func3w, func4w},
                                 {func5w, func6w, func7w, func8w},
                                 {func9w, func10w, func11w, func12w},
                                 {func13w, func14w, func15w, func16w}};
		


																 
    // 定义输入的 01 列表
    
    // 遍历列表，对于每个为 1 的位置，执行相应的函数
																 
																 
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (LOGIC_TABLE[i][j] == 1) {
                func_ptr[i][j]();  // 执行函数
            }
						if (LOGIC_TABLE[i][j] == 0)
						{	func_ptrw[i][j](); }
        }
    }
}





