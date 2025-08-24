#include <stdint.h>
#include <stddef.h>

#include "STMF103C8T6_Registers.h"
#include "ErrType.h"

#include "GPIO_Interface.h"
#include "GPIO_Prv.h"



/* Array of pointers to GPIO register structures for all available ports */
static GPIO_Register_t * GPIO_PORTS[GPIO_NUM_OF_PORTS] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG};


/*-------------------------------------------------------------
 * Function: GPIO_u8PinInit
 * Purpose : Configure a GPIO pin according to user settings
 * Input   : Pointer to GPIO_Pin_Config struct
 * Return  : Error state (OK, INVALID_PORT_NUM, NULL_PTR)
 *------------------------------------------------------------*/
uint8_t GPIO_u8PinInit(const GPIO_Pin_Config* PinConfigs)
{
	uint8_t Local_u8ErrorState =OK;
	uint8_t Local_u8ConFigs  =0 ;

	if (PinConfigs != NULL)  /* Check for null pointer */
	{
		if(PinConfigs -> Port <= PORTG && PinConfigs -> Pin  <= PIN15)
		{

			uint8_t Local_u8RegNum = (PinConfigs -> Pin) / PINS_PER_CR_REG;
			uint8_t Local_u8BitNum = (PinConfigs -> Pin) % PINS_PER_CR_REG;

			/* 1- Combine mode and type into one configuration value */
			if ((PinConfigs -> Mode) == INPUT)
			{
				Local_u8ConFigs = (((PinConfigs -> Input_type) << 2) | (PinConfigs -> Mode));
			}

			else
			{
				Local_u8ConFigs = (((PinConfigs -> Output_type) << 2) | (PinConfigs -> Mode));

			}

			/* 2- Apply configuration: clear then set 4 bits for the selected pin */
			(GPIO_PORTS[PinConfigs->Port] -> CR[Local_u8RegNum]) &=~( GPIO_4BIT_MASK    << (Local_u8BitNum*GPIO_4BIT_SHIFTINTG));
			(GPIO_PORTS[PinConfigs->Port] -> CR[Local_u8RegNum]) |= (Local_u8ConFigs << (Local_u8BitNum*GPIO_4BIT_SHIFTINTG));
		}
		else
		{
			Local_u8ErrorState = INVALID_PORT_NUM ;  /* Invalid port/pin number */
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR ;
	}


	return Local_u8ErrorState ;
}








/*-------------------------------------------------------------
 * Function: GPIO_u8SetPinValue
 * Purpose : Set a GPIO pin value (HIGH or LOW)
 * Input   : Port, Pin number, Value (HIGH/LOW)
 * Return  : Error state
 *------------------------------------------------------------*/
uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinVal_t PinVal)
{
	uint8_t Local_u8ErrorState =OK;

	if(Port <= PORTG && PinNum  <= PIN15)
	{
		if(PinVal == HIGH)
		{
			GPIO_PORTS[Port] -> BSRR |= (1<< PinNum);
		}
		else
		{
			GPIO_PORTS[Port] -> BSRR |= (1<<( PinNum +BSR_REG_HALF_VAL));
		}
	}
	else
	{
		Local_u8ErrorState = INVALID_PORT_NUM ;
	}



	return Local_u8ErrorState ;

}



/*-------------------------------------------------------------
 * Function: GPIO_u8TogglePinValue
 * Purpose : Toggle a GPIO pin value
 * Input   : Port, Pin number
 * Return  : Error state
 *------------------------------------------------------------*/
uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum)
{
	uint8_t Local_u8ErrorState =OK;

	if(Port <= PORTG && PinNum  <= PIN15)
	{

		GPIO_PORTS[Port] -> ODR ^= (1 << PinNum);   /* XOR toggle */

	}
	else
	{
		Local_u8ErrorState = INVALID_PORT_NUM ;
	}
	return Local_u8ErrorState ;

}



/*-------------------------------------------------------------
 * Function: GPIO_u8ReadPinValue
 * Purpose : Read the current logic level of a GPIO pin
 * Input   : Port, Pin number, Pointer to variable for value
 * Return  : Error state
 *------------------------------------------------------------*/
uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinVal_t* PinVal)
{
	uint8_t Local_u8ErrorState =OK;
	if(Port<= PORTG && PinNum  <= PIN15)
	{

		*PinVal = (1 & ((GPIO_PORTS[Port] -> IDR) >> PinNum));  /* Extract bit value */

	}
	else
	{
		Local_u8ErrorState = INVALID_PORT_NUM ;
	}

	return Local_u8ErrorState ;

}
