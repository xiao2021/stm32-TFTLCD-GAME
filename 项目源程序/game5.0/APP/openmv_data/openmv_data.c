#include "openmv_data.h"
#include "SysTick.h"
#include "led.h"

int BIT_flag = 1;
uint8_t STATUS_REC = 3;
uint8_t SEND_TO_LCD =0;
int rec_flag=1;

void Receive_GPIO_Init(void)
{
  // ʹ��GPIOCʱ��
  __HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
  // ����PC0Ϊ��������ģʽ
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // ����PC1Ϊ�����ش����ж�ģʽ
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // ʹ���ж�
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

// �жϴ�����
void EXTI1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

// �жϻص�����
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//LED1 =0;
  if (GPIO_Pin == GPIO_PIN_1)
  {
		if(BIT_flag == 1){
			rec_flag = 0;
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET){
    // PC1�����ش����жϴ������
		STATUS_REC = STATUS_REC & 0x02;
		}
		else {
			STATUS_REC = STATUS_REC | 0x01;
		}
		//BIT_flag++;
		}
		
		
		if(BIT_flag == 2){
			
			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET){
		STATUS_REC = STATUS_REC & 0x01;}
			else {
			STATUS_REC = STATUS_REC | 0x02;
		}
			SEND_TO_LCD = STATUS_REC+1;
		rec_flag = 1;
	}
		if(BIT_flag == 1){BIT_flag++;}
		else{BIT_flag=1;}
		
  }
}

