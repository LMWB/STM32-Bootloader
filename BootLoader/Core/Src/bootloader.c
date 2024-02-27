/*
 * bootloader.c
 *
 *  Created on: Feb 14, 2024
 *      Author: lukas
 *
 *
 *      Demo and how to write Bootloader
 *
 *      Pin PC0 (Nucleo A5) and Pin PC1 (Nucleo A4) are configured as GPIO Input with Pull Down
 *      Use a Jumper Wire to simulate switches for these two pins. The bootloader will loop until
 *      one presses the blue button (Nucleo B1). According to state of switches the bootloader
 *      decides where to jump to.
 *
 *      TIM6 is not used it is initialized just for demo to make sure it is working on Application
 *      after bootloader.
 *
 *      On application Project, the Interrupt Vector Table has to be configured in system_stm32f4xx.c at line 94 and 108.
 *      Vector Table Offset must match Linker file!
 *
 *
 */
#include <string.h>
#include <stdio.h>
#include "bootloader.h"
#include "usart.h"
#include "tim.h"

static uint8_t partition = 0;
volatile uint8_t bootSelection = 0;

void bl_deinitEverything() {
	//-- reset peripherals to guarantee flawless start of user application
	HAL_GPIO_DeInit(LD2_GPIO_Port, LD2_Pin);
	HAL_GPIO_DeInit(B1_GPIO_Port, B1_Pin);

	HAL_UART_MspDeInit(&huart2);
	HAL_TIM_Base_MspDeInit(&htim6);

	__HAL_RCC_GPIOC_CLK_DISABLE();
	__HAL_RCC_GPIOD_CLK_DISABLE();
	__HAL_RCC_GPIOB_CLK_DISABLE();
	__HAL_RCC_GPIOA_CLK_DISABLE();

	HAL_RCC_DeInit();

	HAL_DeInit();

	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;
}


void bl_jumpToApplication(const uint32_t address)
{
	const JumpStruct* vector_p = (JumpStruct*)address;

	/* let's do The Jump! */
    /* Jump, used asm to avoid stack optimization */
    asm("msr msp, %0; bx %1;" : : "r"(vector_p->stack_addr), "r"(vector_p->func_p));
}


void bl_main(void)
{
	char msg[128] = {};
	uint16_t msgSize = 0;
	msgSize = sprintf(msg, "Booting ...");
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, msgSize, -1);

	msgSize = sprintf(msg, "Enter Bootloader\nMake Selection on Boot Partition then press Blue Button...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, msgSize, -1);

	while( !bootSelection ){
		partition = HAL_GPIO_ReadPin(BootSelect0_GPIO_Port, BootSelect0_Pin);
		partition |= (HAL_GPIO_ReadPin(BootSelect1_GPIO_Port, BootSelect1_Pin) << 1);
		HAL_Delay(10);
	}

	msgSize = sprintf(msg, "Jump to Application %d...\n", partition);
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, msgSize, -1);

	bl_deinitEverything();
	switch (partition) {
		case 0:
			bl_jumpToApplication(APP1_START);
			break;
		case 1:
			bl_jumpToApplication(APP1_START);
			break;
		case 2:
			bl_jumpToApplication(APP2_START);
		break;
		case 3:
			bl_jumpToApplication(APP2_START);
			break;
		default:
			bl_jumpToApplication(APP1_START);
			break;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if( GPIO_Pin == B1_Pin ){
		bootSelection = 1;
	}
}
