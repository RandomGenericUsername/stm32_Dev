#ifndef _PIN_BASE_H
#define _PIN_BASE_H

#include "stm32f411xe.h"
#include "GPIOTypes.hh"
#include "stdbool.h"
#include "NVICTypes.h"
#include <utility>


class pinBase
{
    private:

        GPIO_TypeDef *_instance;
        gpioPort _port;
        gpioPin _pin;
        gpioMode _mode;
        gpioPUPD _pupd;
        gpioOutputType _outputType;
        gpioOutputSpeed _outputSpeed;
        gpioAlternateFunction _alternateFunction;
        //NVIC_INTERRUPT_PRIORITY _interruptPriority = NVIC_PRIORITY_15;
        //gpioExtTrigger _triggeringEdge = gpioExtTrigger::disabled;
        //gpioExtInterrupt _extInterrupt = ::gpioExtInterrupt::disable;
        //gpioExtEvent _extEvent = gpioExtEvent::disable;

    public:

        void begin();
        void end();

        //void setPort(GPIO_TypeDef* port) { _port = getGPIOIndex(port); _instance = port; }
        //void setPort(gpioPort port) {_port = port; _instance = getGPIO(port); }
        //void setPin(gpioPin pin) {_pin = pin; }


};


        //explicit pinBase(){init();}
        //template <class ...Args>
        //explicit pinBase(const Args& ...rest)
        //{
        //    //if constexpr(sizeof...(Args) == 0) {_init();}
        //   (..., init(rest));
        //}
        //~pinBase();


        //GPIO_TypeDef *_instance = nullptr;
        //GPIO_TypeDef _resetValues;


        //void  init();
        //template <class T>
        //void  init(T &t){_init(t);}
        //void _init(gpioPort port);
        //void _init(GPIO_TypeDef* GPIOx);
        //void _init(gpioPin pin);
        //void _init(gpioMode mode);
        //void _init(gpioOutputType outputType);
        //void _init(gpioPUPD pupd);
        //void _init(gpioOutputSpeed outputSpeed);
        //void _init(gpioAlternateFunction alternate_function);
        //void _init(NVIC_INTERRUPT_PRIORITY interruptPriority);
        //void _init(gpioExtTrigger trigger);
        //void _init(gpioExtEvent extEventEnable);
        //void _init(gpioExtInterrupt extInterruptEnable);





#endif