#ifndef _PIN_H
#define _PIN_H

#include "GPIOTypes.hh"
#include "stm32f411xe.h"

class pin
{
    private:
    

    public:

        pin(){}
        pin(gpioPin pin){}
        pin(GPIO_TypeDef *GPIOx){}
        template<class...Args>
        pin(GPIO_TypeDef *GPIOx, gpioPin pin, const Args &...args){}
        ~pin(){}


        bool read();
        void set();
        void reset();

        bool release(bool force = false);
        

};





#endif
