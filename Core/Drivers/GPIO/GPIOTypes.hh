#ifndef _GPIO_TYPES_H
#define _GPIO_TYPES_H

#include <stdint.h>

/* */
#define NUMBER_OF_PORTS 7U
/* number of pins available in each port. This is used as a reference variable in the pin init functions. */
#define NUMBER_OF_PINS 16U
#define NUMBER_OF_AVAILABLE_EXT_INTERRUPT 16

typedef int32_t paramType;
typedef uint32_t paramIndex;
const uint8_t numberOfPinParams = 7;
const uint8_t numberOfAFPArams = 1;

enum class gpioParameters {port = 0, pin = 1, mode = 2, pupd = 3, oType = 4, oSpeed = 5, state = 6, failSafe = 15, debug = 16 };
enum class gpioPort{A = 0x0, B = 0x01, C = 0x02, D = 0x03, E = 0x04, H = 0x07, null = -1};
enum class gpioPin{_0 = 0UL, _1 = 1UL, _2 = 2UL, _3 = 3UL, _4 = 4UL, _5 = 5UL, _6 = 6UL, _7 = 7UL, _8 = 8UL, _9 = 9UL, _10 = 10UL, _11 = 11UL, _12 = 12UL, _13 = 13UL, _14 = 14UL, _15 = 15UL, null = -1};
enum class gpioExtITAllocated{A, B, C, D, E, H, free };
enum class gpiostatusCode { reset = 0, ready = 1, busy = 2, timeout = 3, undefinedError = 4, alreadyAllocatedPinError = 5, initQueuedSettingsFailed = 6, wrongParamPassed = 7, readingDeallocatedPin = 8, modeNotAllowed = 9, alreadyAllocatedInterruptError = 10};
/* GPIO possible states definition */ /* GPIO reset state */ /* GPIO set state */
enum class gpioState{ low = 0, high = 1, undefined = -1 };

enum class gpioFailSafe { disable = 0 ,enable = 1 };
enum class gpioDebug { disable = 0 ,enable = 1 };


/* GPIO mode selection definition */
enum class gpioMode
{
    input = (unsigned int)0x0U,                 /* GPIO input selection mode */
    output = (unsigned int)0x1U,                /* GPIO output selection mode */
    alternateFunction = (unsigned int)0x2U,    /* GPIO alternate function selection mode */
    analogInput = (unsigned int)0x3U,          /* GPIO analog input mode */
};

/* GPIO output mode type selection */
enum class gpioOutputType
{
    pushPull = (unsigned int)0x0U,      /* GPIO push pull output mode */
    openDrain	= (unsigned int)0x1U,     /* GPIO open dragin output mode */
};

/* GPIO output speed selection */
enum class gpioOutputSpeed
{
    low  = (unsigned int)0x0UL,     /* GPIO output low speed */
    medium = (unsigned int)0x1UL,   /* GPIO output medium speed */
    fast	= (unsigned int)0x2UL,    /* GPIO output fast speed */
    high	= (unsigned int)0x3UL,    /* GPIO output high speed */
};

/* GPIO pull up-pull down selection */
enum class gpioPUPD
{
    disabled = (unsigned int)0x00U,           /* GPIO no pull up or pull down selected */
    pullUp = (unsigned int)0x01U,           /* GPIO pull up selection */ 
    pullDown = (unsigned int)0x02U,         /* GPIO pull  down selection */
};


/* GPIO alternate function selection */
enum class gpioAlternateFunction{

    _0 = (unsigned int)0x0U,                /* GPIO alternate function 0 */
    _1 = (unsigned int)0x1U,                /* GPIO alternate function 1 */
    _2 = (unsigned int)0x2U,                /* GPIO alternate function 2 */
    _3 = (unsigned int)0x3U,                /* gpio alternate function 3 */
    _4 = (unsigned int)0x4U,                /* GPIO alternate function 4 */
    _5 = (unsigned int)0x5U,                /* GPIO alternate function 5 */
    _6 = (unsigned int)0x6U,                /* GPIO alternate function 6 */
    _7 = (unsigned int)0x7U,                /* GPIO alternate function 7 */
    _8 = (unsigned int)0x8U,                /* GPIO alternate function 8 */
    _9 = (unsigned int)0x9U,                /* GPIO alternate function 9 */
    _10 = (unsigned int)0xAU,               /* GPIO alternate function 10 */
    _11 = (unsigned int)0xBU,               /* GPIO alternate function 11 */
    _12 = (unsigned int)0xCU,               /* GPIO alternate function 12 */
    _13 = (unsigned int)0xDU,               /* GPIO alternate function 13 */
    _14 = (unsigned int)0xEU,               /* GPIO alternate function 14 */
    _15 = (unsigned int)0xFU,               /* GPIO alternate function 15 */
};

/* GPIO external events and interrupts trigger selection */ 
enum class gpioExtTrigger{

    disabled = (unsigned int)0x00,                      /* GPIO external events and interrupts no trigger enabled */
    rising = (unsigned int)0x01,                  /* GPIO external events and interrupts rising trigger selection */
    falling = (unsigned int)0x02,                 /* GPIO external events and interrupts falling trigger selection */
    both = (unsigned int)0x03,      /* GPIO external events and interrupts rising and falling trigger selection */
};


enum class gpioExtInterrupt
{
    enable = true,
    disable = false,
};

enum class gpioExtEvent
{
    enable = true,
    disable = false,
};


 

#endif //guard header