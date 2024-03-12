/*
 * bootloader.h
 *
 *  Created on: Feb 14, 2024
 *      Author: lukas
 */

#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_

#include "main.h"
#include "bootloader.h"

#define APP1_START (0x08008000)			//Origin + Bootloader size (32kB)
#define APP2_START (0x08010000)			//Origin + Bootloader size (32kB) + App1 Bank (32kB)

typedef void (application_t)(void);

typedef struct
{
    uint32_t		stack_addr;     // Stack Pointer
    application_t*	func_p;        // Program Counter
} JumpStruct;


void bl_deinitEverything(void);

void bl_jumpToApplication(const uint32_t address);

void bl_main(void);


#endif /* INC_BOOTLOADER_H_ */
