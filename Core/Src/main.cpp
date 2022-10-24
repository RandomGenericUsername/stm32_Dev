#define STM32F411RE
//#define FAIL_SAFE_MODE

#include "stdint.h"
#include "ioPin.hh"
#include "ExtInterrupt.hh"

ioPin a{gpioPort::A, gpioMode::output, gpioState::high, gpioPin::_5};
ExtInterrupt b{gpioExtTrigger::rising, gpioPort::B, gpioPin::_4, gpioPUPD::pullUp};

int main(void)
{
    //tempn = a.callback(&nuf, false, 5, 6);

    while (1)
    {

    }
    return 0;
}

void fpuInit(void)
{
	/*this is needed in order to use the FPU*/
	SCB->CPACR = ((3UL << 10*2) | (3UL << 11*2)); 
}


void EXTI4_Callback()
{
    a.toggle();
}