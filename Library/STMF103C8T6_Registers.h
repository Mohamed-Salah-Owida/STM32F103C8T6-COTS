/*
 * STmF103C8T6_Registers.h
 *
 *  Created on: Jul 31, 2025
 *      Author: Mohamed Salah
 */

#ifndef STMF103C8T6_REGISTERS_H_
#define STMF103C8T6_REGISTERS_H_




/* ----------------------------- ----------------------------------------------------------  *
 *                         Various Memories Base Addresses                                     *
 * ----------------------------- ----------------------------------------------------------  */
#define FLASH_BASE_ADDRESS	0x08000000ul
#define SRAM_BASE_ADDRESS	0x20000000ul



/* ----------------------------- ----------------------------------------------------------  *
 *                          AHB Peripherals Base Addresses                                      *
 * ----------------------------- ----------------------------------------------------------  */
#define RCC_BASE_ADDRESS		0x40021000U



/* ----------------------------- ----------------------------------------------------------  *
 *                         APB2 Peripheral Base Addresses                                     *
 * ----------------------------- ----------------------------------------------------------  */



/* ----------------------------- ----------------------------------------------------------  *
 *                          APB2 Peripheral Base Addresses                                     *
 * ----------------------------- ----------------------------------------------------------  */
#define GPIOA_BASE_ADDRESS     0x40010800
#define GPIOB_BASE_ADDRESS	 0x40010C00
#define GPIOC_BASE_ADDRESS	 0x40011000
#define GPIOD_BASE_ADDRESS	 0x40011400
#define GPIOE_BASE_ADDRESS	 0x40011800
#define GPIOF_BASE_ADDRESS	 0x40011C00
#define GPIOG_BASE_ADDRESS	 0x40012000






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




/******************* GPIO Registers Definition Structure *******************
 * This structure represents the layout of the GPIO registers block.
 * Each field corresponds to a 32-bit register in the GPIO module.
 * 'volatile' is used because the register values can change unexpectedly (e.g., due to hardware or interrupts).
 **************************************************************************/
typedef struct
{
	volatile uint32_t CR[2];          /* Port configuration registers: CRL (pins 0–7), CRH (pins 8–15) */
	volatile uint32_t IDR;            /* Input data register: reads logic level of input pins */
	volatile uint32_t ODR;            /* Output data register: controls and reads pin outputs */
	volatile uint32_t BSRR;           /* Bit set/reset register: set pins (low half) or reset pins (high half) */
	volatile uint32_t BRR;            /* Bit reset register: resets selected pins */
	volatile uint32_t LCKR;           /* Lock register: locks GPIO configuration until reset */
	volatile uint32_t EVCR;           /* Event control register: configures event output pin and signal */
	volatile uint32_t AFIO_MAPR;      /* AF remap register: remaps peripheral and debug pins */
	volatile uint32_t AFIO_EXTICR[4]; /* EXTI configuration registers: select GPIO pin for EXTI0–15 */
	volatile uint32_t AFIO_MAPR2;     /* Additional AF remap register: extra remapping options */
} GPIO_Register_t;


/******************* GPIO Peripheral Definition Macros *******************
 * GPIO is now a pointer to the GPIO register structure.
 * This allows you to access GPIO registers like: GPIOx->CR, GPIOx->CFGR, etc.
 ************************************************************************/
#define GPIOA		((GPIO_Register_t *) GPIOA_BASE_ADDRESS)
#define GPIOB		((GPIO_Register_t *) GPIOB_BASE_ADDRESS)
#define GPIOC		((GPIO_Register_t *) GPIOC_BASE_ADDRESS)
#define GPIOD		((GPIO_Register_t *) GPIOD_BASE_ADDRESS)
#define GPIOE		((GPIO_Register_t *) GPIOE_BASE_ADDRESS)
#define GPIOF		((GPIO_Register_t *) GPIOF_BASE_ADDRESS)
#define GPIOG		((GPIO_Register_t *) GPIOG_BASE_ADDRESS)






#endif /* STMF103C8T6_REGISTERS_H_ */
