/*
 * RCC_Program.c
 *
 *  Created on: Jul 31, 2025
 *      Author: Mohamed Salah
 */

#include <stdint.h>
#include "RCC_Interface.h"
#include "RCC_Prv.h"
#include "RCC_Cfg.h"
#include "STMF103C8T6_Registers.h"


/**
 * @brief Enable or disable a specific clock (HSI, HSE, or PLL)
 * @param CLKType: Type of clock
 * @param CLKStatus: ON or OFF
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCC_SetCLKStatus (RCC_CLKTypes_t CLKType,RCC_CLKStatus_t CLKStatus)
{

	RCC_ErrorState_t ErrorState =OK;
	uint32_t TimeOutCounter =0 ;

	switch(CLKType)
	{
	case HSI:
		if (CLKStatus == ON) {
			/*set HSI_ON bit */
			RCC -> CR |= (uint32_t)(1<<HSI_ON);
			/*waiting for the HSI Ready flag*/
			while((TimeOutCounter < TIME_OUT)&& !(RCC -> CR >> HSI_RDY)){TimeOutCounter++;}}

		else if (CLKStatus == OFF){

			if ((RCC->CFGR & CFGR_SW_BITS_MASK) == HSI || ((RCC->CFGR >> 2) & CFGR_SW_BITS_MASK) == HSI){
				// HSE is selected or currently used → cannot switch it off
				ErrorState = SWITCHING_OFF_SELECTED_CLK;
			}
			else{
				RCC->CR &= ~(1 << HSI_ON);
			}
		}
		else{
			ErrorState = INVALID_INPUT ;
		}break;



	case HSE:
		if (CLKStatus == ON) {
			/*set HSI_ON bit */
			RCC -> CR |= (uint32_t)(1<<HSE_ON);
			/*waiting for the HSE Ready flag*/
			while((TimeOutCounter < TIME_OUT)&& !(RCC -> CR >> HSE_RDY)){TimeOutCounter++;}}

		else if (CLKStatus == OFF){

			if ((RCC->CFGR & CFGR_SW_BITS_MASK) == HSE || ((RCC->CFGR >> 2) & CFGR_SW_BITS_MASK) == HSE){
				// HSE is selected or currently used → cannot switch it off
				ErrorState = SWITCHING_OFF_SELECTED_CLK;
			}
			else{
				RCC->CR &= ~(1 << HSE_ON);
			}
		}
		else{
			ErrorState = INVALID_INPUT ;
		}break;
	case PLL:
		if (CLKStatus == ON) {
			/*set HSI_ON bit */
			RCC -> CR |= (uint32_t)(1<<PLL_ON);
			/*waiting for the PLL Ready flag*/
			while((TimeOutCounter < TIME_OUT)&& !(RCC -> CR >> PLL_RDY)){TimeOutCounter++;}}

		else if (CLKStatus == OFF){

			if ((RCC->CFGR & CFGR_SW_BITS_MASK) == PLL || ((RCC->CFGR >> 2) & CFGR_SW_BITS_MASK) == PLL){
				// PLL is selected or currently used → cannot switch it off
				ErrorState = SWITCHING_OFF_SELECTED_CLK;
			}
			else{
				RCC->CR &= ~(1 << PLL_ON); // PLLON = 0

			}
		}
		else{
			ErrorState = INVALID_INPUT ;
		}break;

	default: ErrorState = WRONG_CLK_SRC_INPUT;
	}

	if (TimeOutCounter == TIME_OUT)
	{
		ErrorState = TIMEOUT ;
	}
	return ErrorState;
}


/**
 * @brief Set the system clock source (after enabling it)
 * @param CLKType: HSI, HSE, or PLL
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCC_SetSystemCLK(RCC_CLKTypes_t CLKType)
{
	RCC_ErrorState_t ErrorState =OK;

	if(CLKType != HSI && CLKType != HSE  && CLKType != PLL)
	{
		ErrorState = WRONG_CLK_SRC_INPUT;
	}
	else
	{
		RCC -> CFGR &= ~(CFGR_SW_BITS_MASK);
		RCC -> CFGR |= CLKType ;
	}

	return ErrorState;
}



/**
 * @brief Configure HSE type: crystal or bypass
 * @param HSEMode: HSE_CRYSTAL or HSE_BYPASS
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCC_HSEConfig(HSE_Mode_t HSEMode)
{
	RCC_ErrorState_t ErrorState =OK ;

	if(HSEMode == HSE_CRYSTAL)
	{
		RCC -> CR &= (uint32_t) (~(HSE_CRYSTAL <<HSE_BYP));
	}
	else if (HSEMode == HSE_BYPASS)
	{
		RCC -> CR |= (uint32_t) (HSE_BYPASS << HSE_BYP);
	}
	else
	{
		ErrorState = NOK;
	}

	return ErrorState;
}


/**
 * @brief Configure PLL source and multiplication factor
 * @param PLLSource: HSI/2, HSE, or HSE/2
 * @param PLLMulFactor: x2 to x16
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCC_PLLConfig(PLL_Source_t PLLSource,PLL_MUL_t PLLMulFactor )
{
	RCC_ErrorState_t ErrorState = OK ;

	/*switching OFF the PLL First */
	if ((RCC->CFGR & CFGR_SW_BITS_MASK) == PLL || ((RCC->CFGR >> 2) & CFGR_SW_BITS_MASK) == PLL){
		ErrorState = CONFIGING_PLL_WHILE_ON;
	}
	else{
		RCC->CR &= ~(1 << PLL_ON); // PLLON = 0
	}


	// 2. Clear old PLL source and multiplier bits
	RCC->CFGR &= ~((1 << PLL_SRC) | (1 << PLL_XTPRE));      // Clear PLLSRC and PLLXTPRE
	RCC->CFGR &= ~(CFGR_PLLMUL_BITS_MASK << PLL_MUL0);      // Clear PLLMUL[21:18]


	switch(PLLSource)
	{
	case PLL_HSI_DIV_2 :
		RCC -> CR &= ~(1 << PLL_SRC);
		break;
	case PLL_HSE :
		RCC->CFGR |= (1 << PLL_SRC);   // PLLSRC = 1
		RCC->CFGR &= ~(1 << PLL_XTPRE);  // PLLXTPRE = 0 (no divide)
		break;

	case PLL_HSE_DIV_2:
		RCC->CFGR |= (1 << PLL_SRC);   // PLLSRC = 1
		RCC->CFGR |= (1 << PLL_XTPRE);   // PLLXTPRE = 1 (divide by 2)
		break;
	default:
		ErrorState = NOK;
	}



	//Set PLL multiplier factor
	if (PLLMulFactor <= PLL_MUL_x16)
	{
		RCC->CFGR |= (PLLMulFactor << PLL_MUL0); // Set PLLMUL bits [21:18]
	}
	else
	{
		ErrorState = NOK;
	}

	return ErrorState;
}





/**
 * @brief Enable clock for AHB peripheral
 * @param Peripheral: Peripheral enum (bit position)
 */
void RCC_AHBEnableCLK(AHB_Peripheral_t Peripheral)
{
	if(~(RCC -> AHBENR & (1 << Peripheral)))
	{
		RCC -> AHBENR |= (1 << Peripheral);
	}
}


/**
 * @brief Disable clock for AHB peripheral
 * @param Peripheral: Peripheral enum (bit position)
 */
void RCC_AHBDisableCLK(AHB_Peripheral_t Peripheral)
{
	if(RCC -> AHBENR & (1 << Peripheral))
	{
		RCC -> AHBENR &= ~(1 << Peripheral);
	}
}


/**
 * @brief Enable clock for APB1 peripheral
 * @param Peripheral: Peripheral enum (bit position)
 */
void RCC_APB1EnableCLK(APB1_Peripheral_t Peripheral)
{
	if(~(RCC -> APB1ENR & (1 << Peripheral)))
	{
		RCC -> APB1ENR |= (1 << Peripheral);
	}
}


/**
/**
 * @brief Disable clock for APB1 peripheral
 * @param Peripheral: Peripheral enum (bit position)
 */
void RCC_APB1DisableCLK(APB1_Peripheral_t Peripheral)
{
	if(RCC -> APB1ENR & (1 << Peripheral))
	{
		RCC -> APB1ENR &= ~(1 << Peripheral);
	}
}

/**
 * @brief Enable clock for APB2 peripheral
 * @param Peripheral: Peripheral enum (bit position)
 */
void RCC_APB2EnableCLK(APB2_Peripheral_t Peripheral)
{
	if(~(RCC -> APB2ENR & (1 << Peripheral)))
	{
		RCC -> APB2ENR |= (1 << Peripheral);
	}
}

/**
 * @brief Disable clock for APB2 peripheral
 * @param Peripheral: Peripheral enum (bit position)
 */
void RCC_APB2DisableCLK(APB2_Peripheral_t Peripheral)
{
	if(RCC -> APB2ENR & (1 << Peripheral))
	{
		RCC -> APB2ENR &= ~(1 << Peripheral);
	}
}



/**
 * @brief General function to enable clock using bus type
 * @param Bus: AHB, APB1, APB2
 * @param Peripheral: bit number of the peripheral
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCCEnableCLK(BusType_t Bustype,uint8_t Peripheral )
{
	RCC_ErrorState_t ErrorState =OK ;

	switch(Bustype)
	{
	case AHB:
		if(~(RCC -> AHBENR & (1 << Peripheral)))
		{
			RCC -> AHBENR |= (1 << Peripheral);
		}
		break;
	case APB1:
		if(~(RCC -> APB1ENR & (1 << Peripheral)))
		{
			RCC -> APB1ENR |= (1 << Peripheral);
		}
		break;
	case APB2:
		if(~(RCC -> APB2ENR & (1 << Peripheral)))
		{
			RCC -> APB2ENR |= (1 << Peripheral);
		}
		break;
	default: ErrorState = NOK ;
	break;
	}
	return ErrorState ;
}




/**
 * @brief General function to disable clock using bus type
 * @param Bus: AHB, APB1, APB2
 * @param Peripheral: bit number of the peripheral
 * @return RCC_ErrorState_t
 */
RCC_ErrorState_t RCCDisableCLK(BusType_t Bustype,uint8_t Peripheral )
{
	RCC_ErrorState_t ErrorState =OK ;

	switch(Bustype)
	{
	case AHB:
		if(RCC -> AHBENR & (1 << Peripheral))
		{
			RCC -> AHBENR &= ~(1 << Peripheral);
		}
		break;
	case APB1:
		if(RCC -> APB1ENR & (1 << Peripheral))
		{
			RCC -> APB1ENR &= ~(1 << Peripheral);
		}
		break;
	case APB2:
		if(RCC -> APB2ENR & (1 << Peripheral))
		{
			RCC -> APB2ENR &= ~(1 << Peripheral);
		}
		break;
	default: ErrorState = NOK ;
	break;
	}
	return ErrorState ;
}



/**
 * @brief Get the current system clock source
 * @return RCC_CLKTypes_t: HSI, HSE, or PLL
 */
RCC_CLKTypes_t RCC_GetCurrentClock(void)
{
    // Extract SWS bits from RCC->CFGR register
    uint8_t SWS = (RCC->CFGR >> SWS0) & CFGR_SW_BITS_MASK;

    switch(SWS)
    {
        case 0: return HSI;   // 00: HSI used as system clock
        case 1: return HSE;   // 01: HSE used as system clock
        case 2: return PLL;   // 10: PLL used as system clock
        default: return HSI;  // If undefined, default to HSI (safe fallback)
    }
}



