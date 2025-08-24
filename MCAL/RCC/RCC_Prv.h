/*
 * RCC_Private.h
 *
 *  Created on: Jul 31, 2025
 *      Author: Mohamed Salah
 */

#ifndef RCC_PRV_H_
#define RCC_PRV_H_


/*
 * Enum: CR_REG_t
 * This enum defines the bit positions in the RCC_CR register.
 * RCC_CR controls internal/external clock sources (HSI, HSE, PLL).
 */
typedef enum
{
	HSI_ON,                      // Bit 0: Enable the internal High-Speed oscillator (HSI)
	HSI_RDY,                     // Bit 1: HSI ready flag

	// Bits 3–7: HSI trimming bits for fine tuning
	HSI_TRIM0 = 3,
	HSI_TRIM1,
	HSI_TRIM2,
	HSI_TRIM3,
	HSI_TRIM4,

	// Bits 8–15: HSI calibration bits (read-only factory calibration)
	HSI_CAL0,
	HSI_CAL1,
	HSI_CAL2,
	HSI_CAL3,
	HSI_CAL4,
	HSI_CAL5,
	HSI_CAL6,
	HSI_CAL7,

	HSE_ON,                      // Bit 16: Enable external High-Speed oscillator (HSE)
	HSE_RDY,                     // Bit 17: HSE ready flag
	HSE_BYP,                     // Bit 18: Bypass HSE with external clock
	CSS_ON,                      // Bit 19: Clock security system enable
	PLL_ON = 24,                 // Bit 24: Enable PLL
	PLL_RDY,                     // Bit 25: PLL ready flag

}CR_REG_t;

/*
 * Enum: CFGR_REG_t
 * This enum defines the bit positions in the RCC_CFGR register.
 * This register controls system clock selection, prescalers, PLL config, etc.
 */
typedef enum
{
	SW0,                          // Bit 0: System clock switch bit 0
	SW1,                          // Bit 1: System clock switch bit 1
	SWS0,                         // Bit 2: System clock switch status bit 0
	SWS1,                         // Bit 3: System clock switch status bit 1
	HPRE0,                        // Bit 4: AHB prescaler bit 0
	HPRE1,                        // Bit 5
	HPRE2,                        // Bit 6
	HPRE3,                        // Bit 7
	PPRE1_0,                      // Bit 8: APB1 prescaler bit 0
	PPRE1_1,                      // Bit 9
	PPRE1_2,                      // Bit 10
	PPRE2_0,                      // Bit 11: APB2 prescaler bit 0
	PPRE2_1,                      // Bit 12
	PPRE2_2,                      // Bit 13
	ADCPRE0,                      // Bit 14: ADC prescaler bit 0
	ADCPRE1,                      // Bit 15
	PLL_SRC,                      // Bit 16: PLL source (HSI/2 or HSE)
	PLL_XTPRE,                    // Bit 17: HSE divider for PLL entry
	PLL_MUL0,                     // Bit 18: PLL multiplier bit 0
	PLL_MUL1,                     // Bit 19
	PLL_MUL2,                     // Bit 20
	PLL_MUL3,                     // Bit 21
	USB_PRE,                      // Bit 22: USB prescaler

	// MCO [26:24]: Microcontroller clock output
	MCO0 = 24,
	MCO1,
	MCO2,

}CFGR_REG_t;


/*
 * Enum: CIR_REG_t
 * Defines bit positions in the RCC_CIR register.
 * This register manages interrupt flags and enables for clock sources.
 */
typedef enum
{
	LSI_RDYF,                     // Bit 0: LSI ready interrupt flag
	LSE_RDYF,                     // Bit 1: LSE ready interrupt flag
	HSI_RDYF,                     // Bit 2: HSI ready interrupt flag
	HSE_RDYF,                     // Bit 3: HSE ready interrupt flag
	PLL_RDYF,                     // Bit 4: PLL ready interrupt flag

	CSSF = 7,                     // Bit 7: Clock security system interrupt flag

	LSI_RDYIE,                    // Bit 8: LSI ready interrupt enable
	LSE_RDYIE,                    // Bit 9
	HSI_RDYIE,                    // Bit 10
	HSE_RDYIE,                    // Bit 11
	PLL_RDYIE,                    // Bit 12

	LSI_RDYC,                    // Bit 16: LSI ready interrupt clear
	LSE_RDYC,                    // Bit 17
	HSI_RDYC,                    // Bit 18
	HSE_RDYC,                    // Bit 19
	PLL_RDYC,                    // Bit 20

	CSSC = 23,                   // Bit 23: Clock security system clear

}CIR_REG_t;




/*
 * These masks are used to isolate specific fields inside RCC_CFGR
 */

// Mask for SW bits [1:0] – used to select system clock source
#define CFGR_SW_BITS_MASK		3

// Mask for SWS bits [3:2] – used to check current system clock source
#define CFGR_SWS_BITS_MASK  	12

// Mask for PLLMUL bits [21:18] – used to set PLL multiplier factor
#define CFGR_PLLMUL_BITS_MASK	0b1111

#endif /* RCC_PRV_H_ */
