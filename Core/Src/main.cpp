#define STM32F411RE

#include "stdint.h"
#include "ioPin.hh"
#include "afPin.hh"

afPin e(gpioMode::output);
//afPin e(gpioState::high);
afPin a(gpioPort::A, gpioPin::_5, gpioAlternateFunction::_10, gpioPUPD::pullDown, gpioOutputSpeed::low);





int main(void)
{
    while (1)
    {
        /* code */
    }
    return 0;
}


