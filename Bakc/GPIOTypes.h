#ifndef _GPIO_TYPES_H
#define _GPIO_TYPES_H

#include <stdint.h>

/* number of pins available in each port. This is used as a reference variable in the pin init functions. */
#define NUMBER_OF_PINS 16

/* GPIO pin number definition */
const uint32_t PIN_0   = 0UL;       /* GPIO pin 0 */
const uint32_t PIN_1   = 1UL;       /* GPIO pin 1 */
const uint32_t PIN_2   = 2UL;       /* GPIO pin 2 */
const uint32_t PIN_3   = 3UL;       /* GPIO pin 3 */
const uint32_t PIN_4   = 4UL;       /* GPIO pin 4 */
const uint32_t PIN_5   = 5UL;       /* GPIO pin 5 */
const uint32_t PIN_6   = 6UL;       /* GPIO pin 6 */
const uint32_t PIN_7   = 7UL;       /* GPIO pin 7 */
const uint32_t PIN_8   = 8UL;       /* GPIO pin 8 */
const uint32_t PIN_9   = 9UL;       /* GPIO pin 9 */
const uint32_t PIN_10  = 10UL;      /* GPIO pin 10 */
const uint32_t PIN_11  = 11UL;      /* GPIO pin 11 */
const uint32_t PIN_12  = 12UL;      /* GPIO pin 12 */
const uint32_t PIN_13  = 13UL;      /* GPIO pin 13*/
const uint32_t PIN_14  = 14UL;      /* GPIO pin 14*/
const uint32_t PIN_15  = 15UL;      /* GPIO pin 15*/

static const uint32_t pin[NUMBER_OF_PINS] = {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15};

typedef uint32_t GPIO_PIN;

/* GPIO possible states definition */ /* GPIO reset state */ /* GPIO set state */
enum GPIO_PIN_STATE{ PIN_RESET = 0, PIN_SET = 1 };

/* GPIO mode selection definition */
enum GPIO_MODE
{
    INPUT = (unsigned int)0x0U,                 /* GPIO input selection mode */
    OUTPUT = (unsigned int)0x1U,                /* GPIO output selection mode */
    ALTERNATE_FUNCTION = (unsigned int)0x2U,    /* GPIO alternate function selection mode */
    ANALOG_INPUT = (unsigned int)0x3U,          /* GPIO analog input mode */
};


/* GPIO output mode type selection */
enum GPIO_OTYPE
{
    PUSH_PULL = (unsigned int)0x0U,      /* GPIO push pull output mode */
    OPEN_DRAIN	= (unsigned int)0x1U,     /* GPIO open dragin output mode */
};

/* GPIO output speed selection */
enum GPIO_OSPEED
{
    LOW  = (unsigned int)0x0UL,     /* GPIO output low speed */
    MEDIUM = (unsigned int)0x1UL,   /* GPIO output medium speed */
    FAST	= (unsigned int)0x2UL,    /* GPIO output fast speed */
    HIGH	= (unsigned int)0x3UL,    /* GPIO output high speed */
};

/* GPIO pull up-pull down selection */
enum GPIO_PUPD
{
    NO_PUPD = (unsigned int)0x00U,           /* GPIO no pull up or pull down selected */
    PULL_UP = (unsigned int)0x01U,           /* GPIO pull up selection */ 
    PULL_DOWN = (unsigned int)0x02U,         /* GPIO pull  down selection */
};


/* GPIO alternate function selection */
enum GPIO_AF{

    AF_0 = (unsigned int)0x0U,                /* GPIO alternate function 0 */
    AF_1 = (unsigned int)0x1U,                /* GPIO alternate function 1 */
    AF_2 = (unsigned int)0x2U,                /* GPIO alternate function 2 */
    AF_3 = (unsigned int)0x3U,                /* gpio alternate function 3 */
    AF_4 = (unsigned int)0x4U,                /* GPIO alternate function 4 */
    AF_5 = (unsigned int)0x5U,                /* GPIO alternate function 5 */
    AF_6 = (unsigned int)0x6U,                /* GPIO alternate function 6 */
    AF_7 = (unsigned int)0x7U,                /* GPIO alternate function 7 */
    AF_8 = (unsigned int)0x8U,                /* GPIO alternate function 8 */
    AF_9 = (unsigned int)0x9U,                /* GPIO alternate function 9 */
    AF_10 = (unsigned int)0xAU,               /* GPIO alternate function 10 */
    AF_11 = (unsigned int)0xBU,               /* GPIO alternate function 11 */
    AF_12 = (unsigned int)0xCU,               /* GPIO alternate function 12 */
    AF_13 = (unsigned int)0xDU,               /* GPIO alternate function 13 */
    AF_14 = (unsigned int)0xEU,               /* GPIO alternate function 14 */
    AF_15 = (unsigned int)0xFU,               /* GPIO alternate function 15 */
};

/* GPIO external events and interrupts trigger selection */ 
enum EXT_TRIGGER_SEL{

    NO_TRIGGER = (unsigned int)0x00,                      /* GPIO external events and interrupts no trigger enabled */
    RISING_TRIGGER = (unsigned int)0x01,                  /* GPIO external events and interrupts rising trigger selection */
    FALLING_TRIGGER = (unsigned int)0x02,                 /* GPIO external events and interrupts falling trigger selection */
    RISING_AND_FALLING_TRIGGER = (unsigned int)0x03,      /* GPIO external events and interrupts rising and falling trigger selection */
};

struct GPIO_INITIALIZED_PINS 
{
    uint16_t gpioAInitializedPins;
    uint16_t gpioBInitializedPins;
    uint16_t gpioCInitializedPins;
    uint16_t gpioDInitializedPins;
    uint16_t gpioEInitializedPins;
    uint16_t reserved1;
    uint16_t reserved2;
    uint16_t gpioHInitializedPins;
};

struct GPIO_INTERRUPTS_ENABLED 
{
    uint16_t gpioAInterruptsEnabled;
    uint16_t gpioBInterruptsEnabled;
    uint16_t gpioCInterruptsEnabled;
    uint16_t gpioDInterruptsEnabled;
    uint16_t gpioEInterruptsEnabled;
    uint16_t reserved1;
    uint16_t reserved2;
    uint16_t gpioHInterruptsEnabled;
};

enum GPIO_INTERRUPT_EN
{
    IT_ENABLE = true,
    IT_DISABLE = false
};

enum GPIO_EVENT_EN
{
    EV_ENABLE = true,
    EV_DISABLE = false
};
#endif