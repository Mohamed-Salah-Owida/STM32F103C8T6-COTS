/*
 * RCC_Interface.h
 *
 *  Created on: Jul 31, 2025
 *      Author: Mohamed Salah
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_



/*
 ============================================================================
              ENUMERATIONS FOR RCC DRIVER STATUS AND CONFIGURATION
 ============================================================================
 */

/*
 * Return types for functions to describe result or error
 */
typedef enum {
	OK,
	NOK,
	TIMEOUT,
	INVALID_INPUT,
	SWITCHING_OFF_SELECTED_CLK,
	WRONG_CLK_SRC_INPUT,
	CONFIGING_PLL_WHILE_ON

}RCC_ErrorState_t;

/*
 * Types of available system clocks
 */
typedef enum {
	HSI,
	HSE,
	PLL
}RCC_CLKTypes_t;

/*
 * Status for clock enable/disable
 */
typedef enum {
	ON,
	OFF
}RCC_CLKStatus_t;

/*
 * Modes for using the external clock (HSE)
 */
typedef enum {
	HSE_CRYSTAL = 0,   // Use crystal oscillator (default)
	HSE_BYPASS         // Use external clock in bypass mode
} HSE_Mode_t;

/*
 * PLL multiplication factors
 * PLL output frequency = Input * Factor
 */
typedef enum
{
	PLL_MUL_x2,
	PLL_MUL_x3,
	PLL_MUL_x4,
	PLL_MUL_x5,
	PLL_MUL_x6,
	PLL_MUL_x7,
	PLL_MUL_x8,
	PLL_MUL_x9,
	PLL_MUL_x10,
	PLL_MUL_x11,
	PLL_MUL_x12,
	PLL_MUL_x13,
	PLL_MUL_x14,
	PLL_MUL_x15,
	PLL_MUL_x16,

}PLL_MUL_t;


/*
 * PLL source options
 */
typedef enum {
	PLL_HSI_DIV_2 = 0,    // 00: HSI/2
	PLL_HSE,              // 01: HSE
	PLL_HSE_DIV_2         // 10: HSE divided by 2 (PLLXTPRE = 1)
} PLL_Source_t;


/*
 ============================================================================
                  PERIPHERAL ENUMS FOR ENABLING/DISABLING CLOCKS
 ============================================================================
 */

/*
 * AHB peripherals
 */
typedef enum
{
	AHB_DMA1,
	AHB_DMA2,
	AHB_SRAM,
	AHB_FLITF = 4,
	AHB_CRC = 6,
	AHB_FSMC = 8,
	AHB_SDIO = 10,

}AHB_Peripheral_t;

/*
 * APB1 peripherals
 */
typedef enum
{
	APB1_TIMER2,
	APB1_TIMER3,
	APB1_TIMER4,
	APB1_TIMER5,
	APB1_TIMER6,
	APB1_TIMER7,
	APB1_TIMER12,
	APB1_TIMER13,
	APB1_TIMER14,
	APB1_WWDG = 11,
	APB1_SPI2 = 14,
	APB1_SPI3,
	APB1_USART2 = 17,
	APB1_USART3,
	APB1_UART4,
	APB1_UART5,
	APB1_I2C1,
	APB1_I2C2,
	APB1_CAN = 25,
	APB1_BKP = 27,
	APB1_PWR,
	APB1_DAC,
}APB1_Peripheral_t;

/*
 * APB2 peripherals
 */
typedef enum
{
	APB2_AFIORST,
	APB2_GPIOA = 2,
	APB2_GPIOB,
	APB2_GPIOC,
	APB2_GPIOD,
	APB2_GPIOE,
	APB2_GPIOF,
	APB2_GPIOG,
	APB2_ADC1,
	APB2_ADC2,
	APB2_TIMER1,
	APB2_SPI1,
	APB2_TIMER8,
	APB2_USART1,
	APB2_ADC3,
	APB2_TIMER9 = 19,
	APB2_TIMER10,
	APB2_TIMER11,
}APB2_Peripheral_t;


/*
 * Bus type (used for general enable/disable functions)
 */
typedef enum{
	AHB,
	APB1,
	APB2
}BusType_t;


/*
 ============================================================================
                      FUNCTION PROTOTYPES FOR RCC DRIVER
 ============================================================================
*/

/**
 * @brief Enable or disable a specific clock (HSI, HSE, PLL)
 * @param CLKType: Clock type to configure
 * @param CLKStatus: ON or OFF
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCC_SetCLKStatus (RCC_CLKTypes_t CLKType,RCC_CLKStatus_t CLKStatus);

/**
 * @brief Set system clock source (after enabling it)
 * @param CLKType: Clock to set as system clock
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCC_SetSystemCLK(RCC_CLKTypes_t CLKType);

/**
 * @brief Configure HSE mode (crystal or bypass)
 * @param HSEMode: HSE_CRYSTAL or HSE_BYPASS
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCC_HSEConfig(HSE_Mode_t HSEMode);

/**
 * @brief Configure PLL source and multiplication factor
 * @param PLLSource: Source for PLL (HSI/2, HSE, HSE/2)
 * @param PLLMulFactor: PLL multiplier (x2 to x16)
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCC_PLLConfig(PLL_Source_t PLLSource,PLL_MUL_t PLLMulFactor );



/*
 * =================Accessing The Buses Individually  =====================
 */
/* Enable/Disable clocks for AHB peripherals */
void RCC_AHBEnableCLK(AHB_Peripheral_t Peripheral);
void RCC_AHBDisableCLK(AHB_Peripheral_t Peripheral);


/* Enable/Disable clocks for APB1 peripherals */
void RCC_APB1EnableCLK(APB1_Peripheral_t Peripheral);
void RCC_APB1DisableCLK(APB1_Peripheral_t Peripheral);

/* Enable/Disable clocks for APB2 peripherals */
void RCC_APB2EnableCLK(APB2_Peripheral_t Peripheral);
void RCC_APB2DisableCLK(APB2_Peripheral_t Peripheral);




/**
 * @brief General function to enable clock on any bus
 * @param Bustype: AHB, APB1, or APB2
 * @param Peripheral: Peripheral number (bit position)
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCCEnableCLK(BusType_t Bustype,uint8_t Peripheral );

/**
 * @brief General function to disable clock on any bus
 * @param Bustype: AHB, APB1, or APB2
 * @param Peripheral: Peripheral number (bit position)
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCCDisableCLK(BusType_t Bustype,uint8_t Peripheral );





/**
 * @brief Get the current system clock source
 * @return RCC_CLKTypes_t: HSI, HSE, or PLL
 */
RCC_CLKTypes_t RCC_GetCurrentClock(void);

#endif /* RCC_INTERFACE_H_ */
