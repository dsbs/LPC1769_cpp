/**************************************************************************//**
 * @file     system_LPC17xx.h
 * @brief    CMSIS Cortex-M3 Device Peripheral Access Layer Header File
 *           for the NXP LPC17xx Device Series
 * @version  V1.02
 * @date     08. September 2009
 *
 * @note
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

/*
 * Updated for LPC1769:
 * - Added __RAM_MODE__ definition which is used in system_LPC17xx.h file
 * - GetSystemCoreClock used instead SystemCoreClockUpdate
 *
 * Dawid Bazan <dawidbazan@gmail.com>
 * Dariusz Synowiec <devemouse@gmail.com>
 *
 * Last update on June 2011
 */


#ifndef __SYSTEM_LPC17xx_H
#define __SYSTEM_LPC17xx_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @addtogroup LPC17xx_System
 * @{
 */

/*--------------------- PCONP MASKS and values ----------------------*/

#define PCONP_PCTIM0_MASK  (1 << 1 ) /* Timer/Counter 0 power/clock control bit.                       */
#define PCONP_PCTIM1_MASK  (1 << 2 ) /* Timer/Counter 1 power/clock control bit.                       */
#define PCONP_PCUART0_MASK (1 << 3 ) /* UART0 power/clock control bit.                                 */
#define PCONP_PCUART1_MASK (1 << 4 ) /* UART1 power/clock control bit.                                 */
#define PCONP_PCPWM1_MASK  (1 << 6 ) /* PWM1 power/clock control bit.                                  */
#define PCONP_PCI2C0_MASK  (1 << 7 ) /* The I2C0 interface power/clock control bit.                    */
#define PCONP_PCSPI_MASK   (1 << 8 ) /* The SPI interface power/clock control bit.                     */
#define PCONP_PCRTC_MASK   (1 << 9 ) /* The RTC power/clock control bit.                               */
#define PCONP_PCSSP1_MASK  (1 << 10) /* The SSP 1 interface power/clock control bit.                   */
#define PCONP_PCADC_MASK   (1 << 12) /* A/D converter (ADC) power/clock control bit.                   */
#define PCONP_PCCAN1_MASK  (1 << 13) /* CAN Controller 1 power/clock control bit.                      */
#define PCONP_PCCAN2_MASK  (1 << 14) /* CAN Controller 2 power/clock control bit.                      */
#define PCONP_PCGPIO_MASK  (1 << 15) /* Power/clock control bit for IOCON, GPIO, and GPIO interrupts.  */
#define PCONP_PCRIT_MASK   (1 << 16) /* Repetitive Interrupt Timer power/clock control bit.            */
#define PCONP_PCMCPWM_MASK (1 << 17) /* Motor Control PWM                                              */
#define PCONP_PCQEI_MASK   (1 << 18) /* Quadrature Encoder Interface power/clock control bit.          */
#define PCONP_PCI2C1_MASK  (1 << 19) /* The I2C1 interface power/clock control bit.                    */
#define PCONP_PCSSP0_MASK  (1 << 21) /* The SSP0 interface power/clock control bit.                    */
#define PCONP_PCTIM2_MASK  (1 << 22) /* Timer 2 power/clock control bit.                               */
#define PCONP_PCTIM3_MASK  (1 << 23) /* Timer 3 power/clock control bit.                               */
#define PCONP_PCUART2_MASK (1 << 24) /* UART 2 power/clock control bit.                                */
#define PCONP_PCUART3_MASK (1 << 25) /* UART 3 power/clock control bit.                                */
#define PCONP_PCI2C2_MASK  (1 << 26) /* I2C interface 2 power/clock control bit.                       */
#define PCONP_PCI2S_MASK   (1 << 27) /* I2S interface power/clock control bit.                         */
#define PCONP_PCGPDMA_MASK (1 << 29) /* GPDMA function power/clock control bit.                        */
#define PCONP_PCENET_MASK  (1 << 30) /* Ethernet block power/clock control bit.                        */
#define PCONP_PCUSB_MASK   (1 << 31) /* USB interface power/clock control bit.                         */

#define PCONP_PCTIM0_DEFAULT  (1 << 1 ) /* Timer/Counter 0 power/clock control bit.                       */
#define PCONP_PCTIM1_DEFAULT  (1 << 2 ) /* Timer/Counter 1 power/clock control bit.                       */
#define PCONP_PCUART0_DEFAULT (1 << 3 ) /* UART0 power/clock control bit.                                 */
#define PCONP_PCUART1_DEFAULT (1 << 4 ) /* UART1 power/clock control bit.                                 */
#define PCONP_PCPWM1_DEFAULT  (1 << 6 ) /* PWM1 power/clock control bit.                                  */
#define PCONP_PCI2C0_DEFAULT  (1 << 7 ) /* The I2C0 interface power/clock control bit.                    */
#define PCONP_PCSPI_DEFAULT   (1 << 8 ) /* The SPI interface power/clock control bit.                     */
#define PCONP_PCRTC_DEFAULT   (1 << 9 ) /* The RTC power/clock control bit.                               */
#define PCONP_PCSSP1_DEFAULT  (1 << 10) /* The SSP 1 interface power/clock control bit.                   */
#define PCONP_PCADC_DEFAULT   (0 << 12) /* A/D converter (ADC) power/clock control bit.                   */
#define PCONP_PCCAN1_DEFAULT  (0 << 13) /* CAN Controller 1 power/clock control bit.                      */
#define PCONP_PCCAN2_DEFAULT  (0 << 14) /* CAN Controller 2 power/clock control bit.                      */
#define PCONP_PCGPIO_DEFAULT  (1 << 15) /* Power/clock control bit for IOCON, GPIO, and GPIO interrupts.  */
#define PCONP_PCRIT_DEFAULT   (0 << 16) /* Repetitive Interrupt Timer power/clock control bit.            */
#define PCONP_PCMCPWM_DEFAULT (0 << 17) /* Motor Control PWM                                              */
#define PCONP_PCQEI_DEFAULT   (0 << 18) /* Quadrature Encoder Interface power/clock control bit.          */
#define PCONP_PCI2C1_DEFAULT  (1 << 19) /* The I2C1 interface power/clock control bit.                    */
#define PCONP_PCSSP0_DEFAULT  (1 << 21) /* The SSP0 interface power/clock control bit.                    */
#define PCONP_PCTIM2_DEFAULT  (0 << 22) /* Timer 2 power/clock control bit.                               */
#define PCONP_PCTIM3_DEFAULT  (0 << 23) /* Timer 3 power/clock control bit.                               */
#define PCONP_PCUART2_DEFAULT (0 << 24) /* UART 2 power/clock control bit.                                */
#define PCONP_PCUART3_DEFAULT (0 << 25) /* UART 3 power/clock control bit.                                */
#define PCONP_PCI2C2_DEFAULT  (1 << 26) /* I2C interface 2 power/clock control bit.                       */
#define PCONP_PCI2S_DEFAULT   (0 << 27) /* I2S interface power/clock control bit.                         */
#define PCONP_PCGPDMA_DEFAULT (0 << 29) /* GPDMA function power/clock control bit.                        */
#define PCONP_PCENET_DEFAULT  (0 << 30) /* Ethernet block power/clock control bit.                        */
#define PCONP_PCUSB_DEFAULT   (0 << 31) /* USB interface power/clock control bit.                         */


/*
 * 0 - Code is loaded and run from ROM
 * 1 - Code is loaded and run from RAM
 */
#define __RAM_MODE__ 0

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * Get SystemCoreClock variable
 *
 * @param  none
 * @return current system clock
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers and returns its value.
 */
extern uint32_t GetSystemCoreClock (void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __SYSTEM_LPC17xx_H */
