/*
 * STmF103C8T6_Registers.h
 *
 *  Created on: Jul 31, 2025
 *      Author: Mohamed Salah
 */

#ifndef STMF103C8T6_REGISTERS_H_
#define STMF103C8T6_REGISTERS_H_



// -----------------------------
// Base Address of RCC Peripheral
// -----------------------------
#define RCC_BASE_ADDRESS		0x40021000U
// RCC (Reset and Clock Control) base address in STM32F103C8T6 memory map




/******************* RCC Registers Definition Structure *******************
 * This structure represents the layout of the RCC register block.
 * Each field corresponds to a 32-bit register in the RCC module.
 * 'volatile' is used because the register values can change unexpectedly (e.g., due to hardware or interrupts).
 **************************************************************************/
typedef struct
{
	volatile uint32_t CR;                   // Clock Control Register (enables/disables HSI, HSE, PLL)
	volatile uint32_t CFGR;                 // Clock Configuration Register (selects system clock, prescalers, PLL settings)
	volatile uint32_t CIR;                  // Clock Interrupt Register (manages interrupts from clock sources)
	volatile uint32_t APB2RSTR;             // APB2 Peripheral Reset Register
	volatile uint32_t APB1RSTR;             // APB1 Peripheral Reset Register
	volatile uint32_t AHBENR;               // AHB Peripheral Clock Enable Register
	volatile uint32_t APB2ENR;              // APB2 Peripheral Clock Enable Register
	volatile uint32_t APB1ENR;              // APB1 Peripheral Clock Enable Register
	volatile uint32_t BDCR;                 // Backup Domain Control Register
	volatile uint32_t CSR;                  // Control/Status Register

}RCC_Register_t;




/******************* RCC Peripheral Definition Macro *******************
 * RCC is now a pointer to the RCC register structure.
 * This allows you to access RCC registers like: RCC->CR, RCC->CFGR, etc.
 ************************************************************************/
#define RCC		((RCC_Register_t *) RCC_BASE_ADDRESS)





#endif /* STMF103C8T6_REGISTERS_H_ */
