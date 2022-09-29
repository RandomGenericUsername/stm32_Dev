#ifndef _GPIO_TYPES_H
#define _GPIO_TYPES_H

#include <stdint.h>

/* */
#define NUMBER_OF_PORTS 7U
/* number of pins available in each port. This is used as a reference variable in the pin init functions. */
#define NUMBER_OF_PINS 16U
#define NUMBER_OF_AVAILABLE_EXT_INTERRUPT 16


typedef uint32_t isParamSet_t;
typedef uint32_t settings_t;

const uint8_t numberOfBasicPinParams = 7;

namespace paramIndex { enum paramIndex {port = 0, pin = 1, mode = 2, pupd = 3, oType = 4, oSpeed = 5, state = 6}; }
namespace gpioPort { enum  gpioPort{A = 0x0UL, B = 0x01UL, C = 0x02UL, D = 0x03UL, E = 0x04UL, H = 0x07UL, null = -1}; }

namespace gpioPin { enum  gpioPin{_0 = 0UL, _1 = 1UL, _2 = 2UL, _3 = 3UL, _4 = 4UL, _5 = 5UL, _6 = 6UL, _7 = 7UL, _8 = 8UL, _9 = 9UL, _10 = 10UL, _11 = 11UL, _12 = 12UL, _13 = 13UL, _14 = 14UL, _15 = 15UL, null = -1}; }

namespace ExtInterruptAllocated {enum  ExtInterruptAllocated{A, B, C, D, E, H, free }; }
namespace gpioStatus{ enum gpioStatus{reset = 0, ready = 1, busy = 2, error = 4}; }
namespace gpioState { enum gpioState{low = 0, high = 1 }; }
namespace gpioMode { enum gpioMode { input = 0x0U, output = 0x1U, alternateFunction = 0x2U, analogInput = 0x3U }; }
namespace gpioOutputType { enum gpioOutputType { pushPull = 0x0U, openDrain	= 0x1U }; }
namespace gpioOutputSpeed { enum gpioOutputSpeed { low  = 0x0UL, medium = 0x1UL, fast = 0x2UL, high	= 0x3UL }; }
namespace gpioPUPD { enum gpioPUPD { disabled = 0x00U, pullUp = 0x01U, pullDown = 0x02U }; }
namespace gpioAlternateFunction { enum gpioAlternateFunction
{ 
    _0 = 0x0U, 
    _1 = 0x1U, 
    _2 = 0x2U, 
    _3 = 0x3U, 
    _4 = 0x4U, 
    _5 = 0x5U, 
    _6 = 0x6U, 
    _7 = 0x7U, 
    _8 = 0x8U, 
    _9 = 0x9U, 
    _10 = 0xAU, 
    _11 = 0xBU, 
    _12 = 0xCU, 
    _13 = 0xDU, 
    _14 = 0xEU, 
    _15 = 0xFU, 
}; }

namespace gpioExtTrigger { enum gpioExtTrigger{ disabled = 0x00, rising = 0x01, falling = 0x02, both = 0x03 }; }
namespace gpioExtInterrupt { enum gpioExtInterrupt { enable = true, disable = false }; }
namespace gpioExtEvent { enum gpioExtEvent { enable = true, disable = false }; }

static uint16_t initializedPins[NUMBER_OF_PORTS]{0}; 
static ExtInterruptAllocated::ExtInterruptAllocated initializedInterrupt[NUMBER_OF_AVAILABLE_EXT_INTERRUPT]{ExtInterruptAllocated::free}; 

#endif //guard header