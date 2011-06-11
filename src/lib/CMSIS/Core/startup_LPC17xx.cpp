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
 * - file ported from c to cpp
 *
 * Dawid Bazan <dawidbazan@gmail.com>
 * Dariusz Synowiec <devemouse@gmail.com>
 *
 * Last update on June 2011
 */


#include "system_LPC17xx.h"


/* weak means "do not complain if there is no definition" */
#define WEAK __attribute__((weak))

/* use isr specific assembly instructions */
#define ISR __attribute__((__interrupt__))

/* make this function a reset handler (place at start of text) */
#define RESET __attribute__((section(".reset_handler")))

/******************************************************************************
 *
 * Forward declaration of the default interrupt handlers.
 *
 ******************************************************************************/
void WEAK           Default_Handler(void);               /* User cat implement his own Default_Handler*/

/* System exception vector handler */
void WEAK ISR RESET Reset_Handler(void);                 /* Reset Handler */
void WEAK ISR       NMI_Handler(void);                   /* NMI Handler */
void WEAK ISR       HardFault_Handler(void);             /* Hard Fault Handler */
void WEAK ISR       MemManage_Handler(void);             /* MPU Fault Handler */
void WEAK ISR       BusFault_Handler(void);              /* Bus Fault Handler */
void WEAK ISR       UsageFault_Handler(void);            /* Usage Fault Handler */
void WEAK ISR       SVC_Handler(void);                   /* SVCall Handler */
void WEAK ISR       DebugMon_Handler(void);              /* Debug Monitor Handler */
void WEAK ISR       PendSV_Handler(void);                /* PendSV Handler */
void WEAK ISR       SysTick_Handler(void);               /* SysTick Handler */


/* External interrupt vector handler */
void WEAK ISR WDT_IRQHandler(void);                      /* Watchdog Timer */
void WEAK ISR TIMER0_IRQHandler(void);                   /* Timer0 */
void WEAK ISR TIMER1_IRQHandler(void);                   /* Timer1 */
void WEAK ISR TIMER2_IRQHandler(void);                   /* Timer2 */
void WEAK ISR TIMER3_IRQHandler(void);                   /* Timer3 */
void WEAK ISR UART0_IRQHandler(void);                    /* UART0 */
void WEAK ISR UART1_IRQHandler(void);                    /* UART1 */
void WEAK ISR UART2_IRQHandler(void);                    /* UART2 */
void WEAK ISR UART3_IRQHandler(void);                    /* UART3 */
void WEAK ISR PWM1_IRQHandler(void);                     /* PWM1 */
void WEAK ISR I2C0_IRQHandler(void);                     /* I2C0 */
void WEAK ISR I2C1_IRQHandler(void);                     /* I2C1 */
void WEAK ISR I2C2_IRQHandler(void);                     /* I2C2 */
void WEAK ISR SPI_IRQHandler(void);                      /* SPI */
void WEAK ISR SSP0_IRQHandler(void);                     /* SSP0 */
void WEAK ISR SSP1_IRQHandler(void);                     /* SSP1 */
void WEAK ISR PLL0_IRQHandler(void);                     /* PLL0 (Main PLL) */
void WEAK ISR RTC_IRQHandler(void);                      /* Real Time Clock */
void WEAK ISR EINT0_IRQHandler(void);                    /* External Interrupt 0 */
void WEAK ISR EINT1_IRQHandler(void);                    /* External Interrupt 1 */
void WEAK ISR EINT2_IRQHandler(void);                    /* External Interrupt 2 */
void WEAK ISR EINT3_IRQHandler(void);                    /* External Interrupt 3 */
void WEAK ISR ADC_IRQHandler(void);                      /* A/D Converter */
void WEAK ISR BOD_IRQHandler(void);                      /* Brown Out Detect */
void WEAK ISR USB_IRQHandler(void);                      /* USB */
void WEAK ISR CAN_IRQHandler(void);                      /* CAN */
void WEAK ISR DMA_IRQHandler(void);                      /* GP DMA */
void WEAK ISR I2S_IRQHandler(void);                      /* I2S */
void WEAK ISR ENET_IRQHandler(void);                     /* Ethernet */
void WEAK ISR RIT_IRQHandler(void);                      /* Repetitive Interrupt Timer */
void WEAK ISR MCPWM_IRQHandler(void);                    /* Motor Control PWM */
void WEAK ISR QEI_IRQHandler(void);                      /* Quadrature Encoder Interface */
void WEAK ISR PLL1_IRQHandler(void);                     /* PLL1 (USB PLL) */
void WEAK ISR USBActivity_IRQHandler(void);              /* USB Activity */
void WEAK ISR CANActivity_IRQHandler(void);              /* CAN Activity */


/* Exported types --------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern unsigned long _etext;     /* end address for the .text section. defined in linker script */
extern unsigned long _sidata;    /* start address for the initialization values of the .data section. defined in linker script */
extern unsigned long _sdata;     /* start address for the .data section. defined in linker script */
extern unsigned long _edata;     /* end address for the .data section. defined in linker script */

extern unsigned long _sbss;      /* start address for the .bss section. defined in linker script */
extern unsigned long _ebss;      /* end address for the .bss section. defined in linker script */

extern unsigned long _estack;    /* init address for the stack pointer. defined in linker script */

extern unsigned long _sifastcode; /* start address for the rom code instructions copied to .fastcode section. defined in linker script */
extern unsigned long _sfastcode; /* start address for the .fastcode section. defined in linker script */
extern unsigned long _efastcode; /* end address for the .fastcode section. defined in linker script */

extern unsigned long _sdatar2;   /* start address for the .datar2(ram2) section. defined in linker script */
extern unsigned long _edatar2;   /* end address for the .datar2(ram2) section. defined in linker script */

extern unsigned long _sdatar3;   /* start address for the .datar3(ram3) section. defined in linker script */
extern unsigned long _edatar3;   /* end address for the .datar3(ram3) section. defined in linker script */


/* function prototypes ------------------------------------------------------*/
extern int main(void);


/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/

#define STACK_SIZE 0x00000200

__attribute__((section(".stack")))
unsigned long pulStack[STACK_SIZE];

/*
 * The Cortex-M3 interrupt controller (NVIC) will need stack address before
 * it can jump to the handler. Hence, it's put as the first thing on the interrupt table
 */
__attribute__((section(".stack_address")))
const unsigned long *stack_end_addr = (pulStack + sizeof(pulStack));

//#define USR_U2SCUM  ( &stack_end_addr + &Reset_Handler )
#define USR_U2SCUM  ( &stack_end_addr)
//static const unsigned long *u2cs = *USR_U2SCUM;

/*
 * Interrupt function addresses sorted by Exception number
 */
__attribute__((section(".isr_vector")))
const unsigned long *isr_vector_table[] =
{
   (unsigned long *)&Reset_Handler,                  /* 1  - Reset Handler */
   (unsigned long *)&NMI_Handler,                    /* 2  - NMI Handler */
   (unsigned long *)&HardFault_Handler,              /* 3  - Hard Fault Handler */
   (unsigned long *)&MemManage_Handler,              /* 4  - MPU Fault Handler */
   (unsigned long *)&BusFault_Handler,               /* 5  - Bus Fault Handler */
   (unsigned long *)&UsageFault_Handler,             /* 6  - Usage Fault Handler */
   (unsigned long *)USR_U2SCUM,                      /* 7  - User Code Checksum */
   (unsigned long *)0,                               /* 8  - Reserved */
   (unsigned long *)0,                               /* 9  - Reserved */
   (unsigned long *)0,                               /* 10 - Reserved */
   (unsigned long *)&SVC_Handler,                    /* 11 - SVCall Handler */
   (unsigned long *)&DebugMon_Handler,               /* 12 - Debug Monitor Handler */
   (unsigned long *)0,                               /* 13 - Reserved */
   (unsigned long *)&PendSV_Handler,                 /* 14 - PendSV Handler */
   (unsigned long *)&SysTick_Handler,                /* 15 - SysTick Handler */

   /* External Interrupts */
   (unsigned long *)&WDT_IRQHandler,                 /* 16 - Watchdog Timer */
   (unsigned long *)&TIMER0_IRQHandler,              /* 17 - Timer0 */
   (unsigned long *)&TIMER1_IRQHandler,              /* 18 - Timer1 */
   (unsigned long *)&TIMER2_IRQHandler,              /* 19 - Timer2 */
   (unsigned long *)&TIMER3_IRQHandler,              /* 20 - Timer3 */
   (unsigned long *)&UART0_IRQHandler,               /* 21 - UART0 */
   (unsigned long *)&UART1_IRQHandler,               /* 22 - UART1 */
   (unsigned long *)&UART2_IRQHandler,               /* 23 - UART2 */
   (unsigned long *)&UART3_IRQHandler,               /* 24 - UART3 */
   (unsigned long *)&PWM1_IRQHandler,                /* 25 - PWM1 */
   (unsigned long *)&I2C0_IRQHandler,                /* 26 - I2C0 */
   (unsigned long *)&I2C1_IRQHandler,                /* 27 - I2C1 */
   (unsigned long *)&I2C2_IRQHandler,                /* 28 - I2C2 */
   (unsigned long *)&SPI_IRQHandler,                 /* 29 - SPI */
   (unsigned long *)&SSP0_IRQHandler,                /* 30 - SSP0 */
   (unsigned long *)&SSP1_IRQHandler,                /* 31 - SSP1 */
   (unsigned long *)&PLL0_IRQHandler,                /* 32 - PLL0 (Main PLL) */
   (unsigned long *)&RTC_IRQHandler,                 /* 33 - Real Time Clock */
   (unsigned long *)&EINT0_IRQHandler,               /* 34 - External Interrupt 0 */
   (unsigned long *)&EINT1_IRQHandler,               /* 35 - External Interrupt 1 */
   (unsigned long *)&EINT2_IRQHandler,               /* 36 - External Interrupt 2 */
   (unsigned long *)&EINT3_IRQHandler,               /* 37 - External Interrupt 3 */
   (unsigned long *)&ADC_IRQHandler,                 /* 38 - A/D Converter */
   (unsigned long *)&BOD_IRQHandler,                 /* 39 - Brown Out Detect */
   (unsigned long *)&USB_IRQHandler,                 /* 40 - USB */
   (unsigned long *)&CAN_IRQHandler,                 /* 41 - CAN */
   (unsigned long *)&DMA_IRQHandler,                 /* 42 - GP DMA */
   (unsigned long *)&I2S_IRQHandler,                 /* 43 - I2S */
   (unsigned long *)&ENET_IRQHandler,                /* 44 - Ethernet */
   (unsigned long *)&RIT_IRQHandler,                 /* 45 - Repetitive Interrupt Timer */
   (unsigned long *)&MCPWM_IRQHandler,               /* 46 - Motor Control PWM */
   (unsigned long *)&QEI_IRQHandler,                 /* 47 - Quadrature Encoder Interface */
   (unsigned long *)&PLL1_IRQHandler,                /* 48 - PLL1 (USB PLL) */
   (unsigned long *)&USBActivity_IRQHandler,         /* 49 - USB Activity */
   (unsigned long *)&CANActivity_IRQHandler          /* 50 - CAN Activity */
};


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
   for (pulDest = &_sdata; pulDest < &_edata;)
   {
      *(pulDest++) = *(pulSrc++);
   }

   /* Zero fill the bss segment */
   for (pulDest = &_sbss; pulDest < &_ebss;)
   {
      *(pulDest++) = 0;
   }

   /* Copy the fastcode which shall be executed from ROM to SRAM */
   pulSrc = &_sifastcode;
   for (pulDest = &_sfastcode; pulDest < &_efastcode;)
   {
      *(pulDest++) = *(pulSrc++);
   }

   /* Call the application's entry point */
   main();

   while (1)
   {
      /* The application entry point shall not be left, in case it did ten go into an infinite loop */
   }
} /* Reset_Handler */

/*******************************************************************************
 *
 * This is the code that gets called when the processor receives an unexpected
 * interrupt.  This simply enters an infinite loop, preserving the system state
 * for examination by a debugger.
 *
 *******************************************************************************/
void Default_Handler(void)
{
   /* Go into an infinite loop */
   while (1)
   {}
}

/*
 * Dummy implementations of all handlers;
 */

void NMI_Handler(void)            { Default_Handler(); }
void HardFault_Handler(void)      { Default_Handler(); }
void MemManage_Handler(void)      { Default_Handler(); }
void BusFault_Handler(void)       { Default_Handler(); }
void UsageFault_Handler(void)     { Default_Handler(); }
void SVC_Handler(void)            { Default_Handler(); }
void DebugMon_Handler(void)       { Default_Handler(); }
void PendSV_Handler(void)         { Default_Handler(); }
void SysTick_Handler(void)        { Default_Handler(); }
void WDT_IRQHandler(void)         { Default_Handler(); }
void TIMER0_IRQHandler(void)      { Default_Handler(); }
void TIMER1_IRQHandler(void)      { Default_Handler(); }
void TIMER2_IRQHandler(void)      { Default_Handler(); }
void TIMER3_IRQHandler(void)      { Default_Handler(); }
void UART0_IRQHandler(void)       { Default_Handler(); }
void UART1_IRQHandler(void)       { Default_Handler(); }
void UART2_IRQHandler(void)       { Default_Handler(); }
void UART3_IRQHandler(void)       { Default_Handler(); }
void PWM1_IRQHandler(void)        { Default_Handler(); }
void I2C0_IRQHandler(void)        { Default_Handler(); }
void I2C1_IRQHandler(void)        { Default_Handler(); }
void I2C2_IRQHandler(void)        { Default_Handler(); }
void SPI_IRQHandler(void)         { Default_Handler(); }
void SSP0_IRQHandler(void)        { Default_Handler(); }
void SSP1_IRQHandler(void)        { Default_Handler(); }
void PLL0_IRQHandler(void)        { Default_Handler(); }
void RTC_IRQHandler(void)         { Default_Handler(); }
void EINT0_IRQHandler(void)       { Default_Handler(); }
void EINT1_IRQHandler(void)       { Default_Handler(); }
void EINT2_IRQHandler(void)       { Default_Handler(); }
void EINT3_IRQHandler(void)       { Default_Handler(); }
void ADC_IRQHandler(void)         { Default_Handler(); }
void BOD_IRQHandler(void)         { Default_Handler(); }
void USB_IRQHandler(void)         { Default_Handler(); }
void CAN_IRQHandler(void)         { Default_Handler(); }
void DMA_IRQHandler(void)         { Default_Handler(); }
void I2S_IRQHandler(void)         { Default_Handler(); }
void ENET_IRQHandler(void)        { Default_Handler(); }
void RIT_IRQHandler(void)         { Default_Handler(); }
void MCPWM_IRQHandler(void)       { Default_Handler(); }
void QEI_IRQHandler(void)         { Default_Handler(); }
void PLL1_IRQHandler(void)        { Default_Handler(); }
void USBActivity_IRQHandler(void) { Default_Handler(); }
void CANActivity_IRQHandler(void) { Default_Handler(); }


