#ifndef GPIO_PRV_H_
#define GPIO_PRV_H_



/******************* Private Macros for GPIO Driver *******************/

/*bit mask */
#define GPIO_2BIT_MASK   0b11u
#define GPIO_4BIT_MASK   0b1111u

/* Each pin configuration in CR register takes 4 bits */
#define GPIO_4BIT_SHIFTINTG  4u


/* Half of BSRR register (upper 16 bits used for reset) */
#define BSR_REG_HALF_VAL   16u

/* Total number of GPIO ports available (A–G) */
#define GPIO_NUM_OF_PORTS     7u

/* Pins per CR register (CRL for pins 0–7, CRH for pins 8–15) */
#define PINS_PER_CR_REG         8u




#endif /* GPIO_PRV_H_ */
