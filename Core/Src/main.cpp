#define STM32F411RE

#include "stdint.h"
#include "aaaa.hh"

//ioPin a({.port = gpioPort::A, .pin = gpioPin::_5, .mode = gpioMode::input});
//ioPin b(gpioMode::output, gpioPin::_5, pinState::high, gpioPUPD::disabled, GPIOA);
//ioPin c(GPIOA, gpioPin::_5, gpioMode::output, pinState::high);
//ioPin d(gpioMode::output, gpioPin::_5, pinState::high, gpioPort::A);
//ioPin e( ioPinParams{.port = gpioPort::A, gpioPin::_5, .mode = gpioMode::output, .state = pinState::high });

typedef gpioPort uint32_t;
uint32_t as = gpioPort::A;
gpioPort e = 3;


int main(void)
{

    while (1)
    {
        /* code */
    }
    return 0;
}


