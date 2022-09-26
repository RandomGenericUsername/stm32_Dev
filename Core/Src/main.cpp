#define STM32F411RE

#include "stdint.h"
#include "ioPin.hh"

//ioPin a({.port = gpioPort::A, .pin = gpioPin::_5, .mode = gpioMode::input});
ioPin a;
//ioPin b(gpioMode::output, gpioPin::_5, pinState::high, gpioPUPD::disabled, GPIOA);
//ioPin c(GPIOA, gpioPin::_5, gpioMode::output, pinState::high);
ioPin d(gpioMode::output, gpioPin::_5, pinState::high, gpioPort::A);

int main(void)
{
    //a.setMode(gpioMode::output);
    //a.setPin(gpioPin::_5);
    //a.setPort(GPIOA);
    while (1)
    {
        /* code */
    }
    
    return 0;
}


