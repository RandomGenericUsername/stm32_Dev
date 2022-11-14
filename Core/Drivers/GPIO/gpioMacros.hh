#ifndef _GPIO_MACROS_H_
#define _GPIO_MACROS_H_

#include "cassert"
#include "GPIO_Types.hh"
#include "stm32f411xe.h"
#include "type_traits"

namespace
{
    #define ASSERT_PIN_PARAMS(arg)(std::is_same_v<const gpioPort&, decltype(arg)>         || \
                                   std::is_same_v<const gpioPin&, decltype(arg)>          || \
                                   std::is_same_v<const gpioMode&, decltype(arg)>         || \
                                   std::is_same_v<const gpioPUPD&, decltype(arg)>         || \
                                   std::is_same_v<const gpioOutputSpeed&, decltype(arg)>  || \
                                   std::is_same_v<const gpioOutputType&, decltype(arg)>   || \
                                   std::is_same_v<const gpioState&, decltype(arg)>        || \
                                   std::is_same_v<const gpioHardException&, decltype(arg)>     || \
                                   std::is_same_v<const gpioDebug&, decltype(arg)>)
    
    #ifndef NDEBUG
        #define m_assert(expr, msg) static_assert(( (void)(msg), (expr) ))
    #else
        #define m_assert(expr, msg);
    #endif

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
        if(errorCode == gpiostatusCode::alreadyAllocatedPinError) while(1);
    }

}



#endif