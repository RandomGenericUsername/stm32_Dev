#ifndef _GPIO_MACROS_H_
#define _GPIO_MACROS_H_

#include "GPIOTypes.hh"
#include "stm32f411xe.h"

namespace
{
    auto getGPIOIndex = [](const GPIO_TypeDef *gpio) 
    { 
        if(gpio == GPIOA) return gpioPort::A; 
        else if(gpio == GPIOB) return gpioPort::B;
        else if(gpio == GPIOC) return gpioPort::C;
        else if(gpio == GPIOD) return gpioPort::D;
        else if(gpio == GPIOE) return gpioPort::E;
        else if(gpio == GPIOH) return gpioPort::H;
    };

    auto getGPIO = [](gpioPort port) 
    {
        if(port == gpioPort::A) return GPIOA;
        else if(port == gpioPort::B) return GPIOB;
        else if(port == gpioPort::C) return GPIOC;
        else if(port == gpioPort::D) return GPIOD;
        else if(port == gpioPort::E) return GPIOE;
        else if(port == gpioPort::H) return GPIOH;
    };

    void gpioExceptionHandler(gpiostatusCode errorCode)
    {
        RCC->AHB1ENR |= 0x1 << 0;
        GPIOA->MODER |= 0x1 << 10;
        uint8_t temp = 10;
        while(temp)
        {
            GPIOA->ODR |= 0x1 << 5;
            for(uint32_t i = 0; i < 100000; i++);
            GPIOA->ODR &=  ~(0x1 << 5);
            for(uint32_t i = 0; i < 100000; i++);
            temp--;
        }
    }

}



#endif