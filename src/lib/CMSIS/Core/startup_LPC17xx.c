/****************************************************************************//**
 * @file :    startup_LPC17xx.c
 * @brief : CMSIS Cortex-M3 Core Device Startup File
 * @version : V1.01
 * @date :    4. Feb. 2009
 *
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-Mx
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

/*
 * Updated to LPC1769 and to adjust to new linker file:
 * - Included system_LPC17xx.h file for SystemInit() function
 * - Fixed Reset_Handler() warning
 * - End of stack address is provided by linker as well as size of the stack
 * - Added addresses for the section ram2 and ram3 (separate banks of memory)
 * - Updated Reset_Handler() function with call of SystemInit(), initialization of ram memory, jump to main()
 * - Minor fixes: comments, this header description
 * - Added missing CAN and USB interrupt vectors, updated descriptions
 * - Removed unnecessary include
 *
 * Dawid Bazan <dawidbazan@gmail.com>
 * Dariusz Synowiec <devemouse@gmail.com>
 *
 * Last update on June 2011
 */


#include "LPC17xx.h"
#include "system_LPC17xx.h"


#define WEAK __attribute__ ((weak))
//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
/* System exception vector handler */
/* Reset handler comment out because of weak attribute which do not apply to the functions used in the same c file */
/* void WEAK 		Reset_Handler(void); */             /* Reset Handler */
void WEAK 		NMI_Handler(void);               /* NMI Handler */
void WEAK 		HardFault_Handler(void);         /* Hard Fault Handler */
void WEAK 		MemManage_Handler(void);         /* MPU Fault Handler */
void WEAK 		BusFault_Handler(void);          /* Bus Fault Handler */
void WEAK 		UsageFault_Handler(void);        /* Usage Fault Handler */
void WEAK 		SVC_Handler(void);               /* SVCall Handler */
void WEAK 		DebugMon_Handler(void);          /* Debug Monitor Handler */
void WEAK 		PendSV_Handler(void);            /* PendSV Handler */
//void WEAK 		SysTick_Handler(void);           /* SysTick Handler */


/* External interrupt vector handler */
void WEAK      	WDT_IRQHandler(void);            /* Watchdog Timer */
void WEAK      	TIMER0_IRQHandler(void);         /* Timer0 */
void WEAK      	TIMER1_IRQHandler(void);         /* Timer1 */
void WEAK      	TIMER2_IRQHandler(void);         /* Timer2 */
void WEAK      	TIMER3_IRQHandler(void);         /* Timer3 */
void WEAK      	UART0_IRQHandler(void);          /* UART0 */
void WEAK      	UART1_IRQHandler(void);          /* UART1 */
void WEAK      	UART2_IRQHandler(void);          /* UART2 */
void WEAK      	UART3_IRQHandler(void);          /* UART3 */
void WEAK      	PWM1_IRQHandler(void);           /* PWM1 */
void WEAK      	I2C0_IRQHandler(void);           /* I2C0 */
void WEAK      	I2C1_IRQHandler(void);           /* I2C1 */
void WEAK      	I2C2_IRQHandler(void);           /* I2C2 */
void WEAK      	SPI_IRQHandler(void);            /* SPI */
void WEAK      	SSP0_IRQHandler(void);           /* SSP0 */
void WEAK      	SSP1_IRQHandler(void);           /* SSP1 */
void WEAK      	PLL0_IRQHandler(void);           /* PLL0 (Main PLL) */
void WEAK      	RTC_IRQHandler(void);            /* Real Time Clock */
void WEAK      	EINT0_IRQHandler(void);          /* External Interrupt 0 */
void WEAK      	EINT1_IRQHandler(void);          /* External Interrupt 1 */
void WEAK      	EINT2_IRQHandler(void);          /* External Interrupt 2 */
void WEAK      	EINT3_IRQHandler(void);          /* External Interrupt 3 */
void WEAK      	ADC_IRQHandler(void);            /* A/D Converter */
void WEAK      	BOD_IRQHandler(void);            /* Brown Out Detect */
void WEAK      	USB_IRQHandler(void);            /* USB */
void WEAK      	CAN_IRQHandler(void);            /* CAN */
void WEAK      	DMA_IRQHandler(void);            /* GP DMA */
void WEAK      	I2S_IRQHandler(void);            /* I2S */
void WEAK      	ENET_IRQHandler(void);           /* Ethernet */
void WEAK      	RIT_IRQHandler(void);            /* Repetitive Interrupt Timer */
void WEAK      	MCPWM_IRQHandler(void);          /* Motor Control PWM */
void WEAK      	QEI_IRQHandler(void);            /* Quadrature Encoder Interface */
void WEAK      	PLL1_IRQHandler(void);           /* PLL1 (USB PLL) */
void WEAK         USBActivity_IRQHandler(void);    /* USB Activity */
void WEAK         CANActivity_IRQHandler(void);    /* CAN Activity */




/* Exported types --------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern unsigned long _etext;     /* end address for the .text section. defined in linker script */
extern unsigned long _sidata;    /* start address for the initialization values of the .data section. defined in linker script */
extern unsigned long _sdata;     /* start address for the .data section. defined in linker script */
extern unsigned long _edata;     /* end address for the .data section. defined in linker script */

extern unsigned long _sbss;      /* start address for the .bss section. defined in linker script */
extern unsigned long _ebss;      /* end address for the .bss section. defined in linker script */

extern unsigned long _estack;    /* init address for the stack pointer. defined in linker script */

extern unsigned long _sifastcode;/* start address for the rom code instructions copied to .fastcode section. defined in linker script */
extern unsigned long _sfastcode; /* start address for the .fastcode section. defined in linker script */
extern unsigned long _efastcode; /* end address for the .fastcode section. defined in linker script */

extern unsigned long _sdatar2;   /* start address for the .datar2(ram2) section. defined in linker script */
extern unsigned long _edatar2;   /* end address for the .datar2(ram2) section. defined in linker script */

extern unsigned long _sdatar3;   /* start address for the .datar3(ram3) section. defined in linker script */
extern unsigned long _edatar3;   /* end address for the .datar3(ram3) section. defined in linker script */



/* Private typedef -----------------------------------------------------------*/
typedef void( *const irqfct )( void );

/* function prototypes ------------------------------------------------------*/
void Reset_Handler(void) __attribute__((__interrupt__));
void SysTick_Handler(void) __attribute__((__interrupt__));
extern int main(void);


/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/

#define STACK_SIZE                              0x00000200

__attribute__ ((section(".stack")))
unsigned long pulStack[STACK_SIZE];

__attribute__ ((section(".isr_vector")))
void (* g_pfnVectors[])(void) =
{
        /*
         * The Cortex-M3 interrupt controller (NVIC) will need stack address before
         * it can jump to the handler. Hence, it�s put as the first thing on the interrupt table
         *
         * Interrupt function addresses sorted by Exception number
         *
         */
        (void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),
        Reset_Handler,             /* 1  - Reset Handler */
        NMI_Handler,               /* 2  - NMI Handler */
        HardFault_Handler,         /* 3  - Hard Fault Handler */
        MemManage_Handler,         /* 4  - MPU Fault Handler */
        BusFault_Handler,          /* 5  - Bus Fault Handler */
        UsageFault_Handler,        /* 6  - Usage Fault Handler */
        0,                         /* 7  - Reserved */
        0,                         /* 8  - Reserved */
        0,                         /* 9  - Reserved */
        0,                         /* 10 - Reserved */
        SVC_Handler,               /* 11 - SVCall Handler */
        DebugMon_Handler,          /* 12 - Debug Monitor Handler */
        0,                         /* 13 - Reserved */
        PendSV_Handler,            /* 14 - PendSV Handler */
        SysTick_Handler,           /* 15 - SysTick Handler */

		  /* External Interrupts */
        WDT_IRQHandler,            /* 16 - Watchdog Timer */
        TIMER0_IRQHandler,         /* 17 - Timer0 */
        TIMER1_IRQHandler,         /* 18 - Timer1 */
        TIMER2_IRQHandler,         /* 19 - Timer2 */
        TIMER3_IRQHandler,         /* 20 - Timer3 */
        UART0_IRQHandler,          /* 21 - UART0 */
        UART1_IRQHandler,          /* 22 - UART1 */
        UART2_IRQHandler,          /* 23 - UART2 */
        UART3_IRQHandler,          /* 24 - UART3 */
        PWM1_IRQHandler,           /* 25 - PWM1 */
        I2C0_IRQHandler,           /* 26 - I2C0 */
        I2C1_IRQHandler,           /* 27 - I2C1 */
        I2C2_IRQHandler,           /* 28 - I2C2 */
        SPI_IRQHandler,            /* 29 - SPI */
        SSP0_IRQHandler,           /* 30 - SSP0 */
        SSP1_IRQHandler,           /* 31 - SSP1 */
        PLL0_IRQHandler,           /* 32 - PLL0 (Main PLL) */
        RTC_IRQHandler,            /* 33 - Real Time Clock */
        EINT0_IRQHandler,          /* 34 - External Interrupt 0 */
        EINT1_IRQHandler,          /* 35 - External Interrupt 1 */
        EINT2_IRQHandler,          /* 36 - External Interrupt 2 */
        EINT3_IRQHandler,          /* 37 - External Interrupt 3 */
        ADC_IRQHandler,            /* 38 - A/D Converter */
        BOD_IRQHandler,            /* 39 - Brown Out Detect */
        USB_IRQHandler,            /* 40 - USB */
        CAN_IRQHandler,            /* 41 - CAN */
        DMA_IRQHandler,            /* 42 - GP DMA */
        I2S_IRQHandler,            /* 43 - I2S */
        ENET_IRQHandler,           /* 44 - Ethernet */
        RIT_IRQHandler,            /* 45 - Repetitive Interrupt Timer */
        MCPWM_IRQHandler,          /* 46 - Motor Control PWM */
        QEI_IRQHandler,            /* 47 - Quadrature Encoder Interface */
        PLL1_IRQHandler,           /* 48 - PLL1 (USB PLL) */
        USBActivity_IRQHandler,    /* 49 - USB Activity */
        CANActivity_IRQHandler     /* 50 - CAN Activity */
};

//*****************************************************************************
//
// Provide weak aliases for each Exception handler to the Default_Handler.
// As they are weak aliases, any function with the same name will override
// this definition.
//
//*****************************************************************************
#pragma weak MemManage_Handler = Default_Handler          /* MPU Fault Handler */
#pragma weak BusFault_Handler = Default_Handler           /* Bus Fault Handler */
#pragma weak UsageFault_Handler = Default_Handler         /* Usage Fault Handler */
#pragma weak SVC_Handler = Default_Handler                /* SVCall Handler */
#pragma weak DebugMon_Handler = Default_Handler           /* Debug Monitor Handler */
#pragma weak PendSV_Handler = Default_Handler             /* PendSV Handler */
//#pragma weak SysTick_Handler = Default_Handler            /* SysTick Handler */

/* External interrupt vector handler */
#pragma weak WDT_IRQHandler = Default_Handler            /* Watchdog Timer */
#pragma weak TIMER0_IRQHandler = Default_Handler         /* Timer0 */
#pragma weak TIMER1_IRQHandler = Default_Handler         /* Timer1 */
#pragma weak TIMER2_IRQHandler = Default_Handler         /* Timer2 */
#pragma weak TIMER3_IRQHandler = Default_Handler         /* Timer3 */
#pragma weak UART0_IRQHandler = Default_Handler          /* UART0 */
#pragma weak UART1_IRQHandler = Default_Handler          /* UART1 */
#pragma weak UART2_IRQHandler = Default_Handler          /* UART2 */
#pragma weak UART3_IRQHandler = Default_Handler          /* UART3 */
#pragma weak PWM1_IRQHandler = Default_Handler           /* PWM1 */
#pragma weak I2C0_IRQHandler = Default_Handler           /* I2C0 */
#pragma weak I2C1_IRQHandler = Default_Handler           /* I2C1 */
#pragma weak I2C2_IRQHandler = Default_Handler           /* I2C2 */
#pragma weak SPI_IRQHandler = Default_Handler            /* SPI */
#pragma weak SSP0_IRQHandler = Default_Handler           /* SSP0 */
#pragma weak SSP1_IRQHandler = Default_Handler           /* SSP1 */
#pragma weak PLL0_IRQHandler = Default_Handler           /* PLL0 (Main PLL) */
#pragma weak RTC_IRQHandler = Default_Handler            /* Real Time Clock */
#pragma weak EINT0_IRQHandler = Default_Handler          /* External Interrupt 0 */
#pragma weak EINT1_IRQHandler = Default_Handler          /* External Interrupt 1 */
#pragma weak EINT2_IRQHandler = Default_Handler          /* External Interrupt 2 */
#pragma weak EINT3_IRQHandler = Default_Handler          /* External Interrupt 3 */
#pragma weak ADC_IRQHandler = Default_Handler            /* A/D Converter */
#pragma weak BOD_IRQHandler = Default_Handler            /* Brown Out Detect */
#pragma weak USB_IRQHandler = Default_Handler            /* USB */
#pragma weak CAN_IRQHandler = Default_Handler            /* CAN */
#pragma weak DMA_IRQHandler = Default_Handler            /* GP DMA */
#pragma weak I2S_IRQHandler = Default_Handler            /* I2S */
#pragma weak ENET_IRQHandler = Default_Handler           /* Ethernet */
#pragma weak RIT_IRQHandler = Default_Handler            /* Repetitive Interrupt Timer */
#pragma weak MCPWM_IRQHandler = Default_Handler          /* Motor Control PWM */
#pragma weak QEI_IRQHandler = Default_Handler            /* Quadrature Encoder Interface */
#pragma weak PLL1_IRQHandler = Default_Handler           /* PLL1 (USB PLL) */
#pragma weak USBActivity_IRQHandler = Default_Handler    /* USB Activity */
#pragma weak CANActivity_IRQHandler = Default_Handler    /* CAN Activity */


/*******************************************************************************
* Function Name  : Reset_Handler
* Description    : This is the code that gets called when the processor first starts execution
*            following a reset event.  Only the absolutely necessary set is performed,
*            after which the application supplied main() routine is called.
* Input          :
* Output         :
* Return         :
*******************************************************************************/
void Reset_Handler(void)
{
    unsigned long *pulSrc, *pulDest;


    /* Initialize the System */
    SystemInit();

    /* Copy the data segment initializers from flash to SRAM in ROM mode */
    pulSrc = &_sidata;
    for( pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    /* Zero fill the bss segment */
    for( pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    /* Copy the fastcode which shall be executed from ROM to SRAM */
    pulSrc = &_sifastcode;
    for( pulDest = &_sfastcode; pulDest < &_efastcode; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    /* Call the application's entry point */
    main();

    while(1)
    {
       /* The application entry point shall not be left, in case it did ten go into an infinite loop */
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
void Default_Handler(void)
{
   LPC_GPIO1->FIOCLR_b24 = 1;
   /* Go into an infinite loop */
   while (1)
   {

   }
}

volatile uint32_t msTicks;                            /* counts 1ms timeTicks */

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
   LPC_GPIO1->FIOCLR_b27 = 1;
  msTicks++;                        /* increment counter necessary in Delay() */
}

