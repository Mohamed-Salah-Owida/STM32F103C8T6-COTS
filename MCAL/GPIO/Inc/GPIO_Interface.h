#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_


/******************* Enums for GPIO configuration *******************/


typedef enum
{
	PORTA = 0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,

}Port_t;



typedef enum
{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15

}Pin_t;




typedef enum
{
	LOW = 0,
	HIGH
}PinVal_t;


typedef enum
{
	INPUT = 0,
	OUTPUT_10MHz,
	OUTPUT_2MHz,
	OUTPUT_50MHz

}Mode_t;

typedef enum
{
	ANALOG = 0,
	FLOATING_INPUT,
	INPUT_PUPD


}Input_type_t;


typedef enum
{
	OUTPUT_PUSH_PULL = 0,
	OUTPUT_OPEN_DRAIN,
	ALT_FUNC_PUSH_PULL,
	ALT_FUNC_OPEN_DRAIN

}Output_type_t;




/******************* GPIO configuration structure *******************/

/**
 * @struct GPIO_Pin_Config
 * @brief  Structure to configure a GPIO pin
 */
typedef struct
{
	Port_t 			Port;
	Pin_t 			Pin;
	Mode_t			Mode ;
	Input_type_t 	Input_type ;
	Output_type_t  Output_type ;
}GPIO_Pin_Config;



/******************* Function Prototypes *******************/

/*-------------------------------------------------------------
 * Function: GPIO_u8PinInit
 * Purpose : Configure a GPIO pin according to user settings
 * Input   : Pointer to GPIO_Pin_Config struct
 * Return  : Error state (OK, INVALID_PORT_NUM, NULL_PTR)
 *------------------------------------------------------------*/
uint8_t GPIO_u8PinInit(const GPIO_Pin_Config* PinConfigs);


/*-------------------------------------------------------------
 * Function: GPIO_u8SetPinValue
 * Purpose : Set a GPIO pin value (HIGH or LOW)
 * Input   : Port, Pin number, Value (HIGH/LOW)
 * Return  : Error state
 *------------------------------------------------------------*/
uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinVal_t PinVal);


/*-------------------------------------------------------------
 * Function: GPIO_u8TogglePinValue
 * Purpose : Toggle a GPIO pin value
 * Input   : Port, Pin number
 * Return  : Error state
 *------------------------------------------------------------*/
uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum);


/*-------------------------------------------------------------
 * Function: GPIO_u8ReadPinValue
 * Purpose : Read the current logic level of a GPIO pin
 * Input   : Port, Pin number, Pointer to variable for value
 * Return  : Error state
 *------------------------------------------------------------*/
uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinVal_t* PinVal);






#endif /* GPIO_INTERFACE_H_ */
