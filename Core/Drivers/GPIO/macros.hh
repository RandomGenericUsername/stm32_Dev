#ifndef _GPIO_MACROS_H_
#define _GPIO_MACROS_H_

#include "GPIOTypes.hh"
#include "stm32f411xe.h"

namespace
{
    auto getGPIOIndex = [](const GPIO_TypeDef *gpio) -> const gpioPort::gpioPort
    { 
    if(gpio == GPIOA) return gpioPort::A; 
    else if(gpio == GPIOB) return gpioPort::B;
    else if(gpio == GPIOC) return gpioPort::C;
    else if(gpio == GPIOD) return gpioPort::D;
    else if(gpio == GPIOE) return gpioPort::E;
    else if(gpio == GPIOH) return gpioPort::H;
    };

    auto getGPIO = [](gpioPort::gpioPort port) -> GPIO_TypeDef*
    {
        if(port == gpioPort::A) return GPIOA;
        else if(port == gpioPort::B) return GPIOB;
        else if(port == gpioPort::C) return GPIOC;
        else if(port == gpioPort::D) return GPIOD;
        else if(port == gpioPort::E) return GPIOE;
        else if(port == gpioPort::H) return GPIOH;
    };
}



#endif