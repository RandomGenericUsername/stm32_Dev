#define STM32F411RE

#include "stdint.h"
#include "ioPin.hh"

ioPin a;
//ioPin c(gpioMode::output, gpioState::high, gpioPin::_5, gpioPort::A);
//ioPin c(gpioMode::output, gpioState::high, gpioPort::A, gpioPin::_5);
ioPin c(gpioMode::output, gpioState::low, gpioPort::A, gpioPin::_5);



int main(void)
{
    c.write(gpioState::high);
    a.setMode(gpioMode::output);
    a.write(gpioState::high);
    a.setPort(gpioPort::A);
    //a.setPin(gpioPin::_5);
    while (1)
    {
        /* code */
    }
    return 0;
}


