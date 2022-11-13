#define STM32F411RE
//#define FAIL_SAFE_MODE

#include "stdint.h"
#include "inputOutputPin.hh"
//#include "ioPin.hh"
//#include "ExtInterrupt.hh"
//#include "UART.hh"

inputOutputPin a;
inputOutputPin d{gpioPort::A, gpioMode::output, gpioState::low, gpioPin::_5, gpioAlternateFunction::_0, gpioDebug::enable, gpioOutputSpeed::fast, gpioOutputType::pushPull};

//ExtInterrupt b{gpioExtTrigger::rising, gpioPort::B, gpioPin::_4, gpioPUPD::pullUp};
//UART com1;
//UART com2{USART1};

int main(void)
{
    //tempn = a.callback(&nuf, false, 5, 6);
    //bool ctrl = a.isReady();
    
    //while(ctrl)
    //{
    //    if(!a.read())
    //    {
    //        if(!a.write(gpioState::high))
    //        {
    //            ctrl = false;
    //            break;
    //        }
    //        for(uint32_t i = 0; i < 1000000; i++);

    //    }
    //    else
    //    {
    //        if(!a.write(gpioState::low))
    //        {
    //            ctrl = false;
    //            break;
    //        }
    //        for(uint32_t i = 0; i < 1000000; i++);
    //    }
    //}

    while (1)
    {


    }
    return 0;
}

void fpuInit(void)
{
	/*this is needed in order to use the FPU*/
	//SCB->CPACR = ((3UL << 10*2) | (3UL << 11*2)); 
}


void EXTI4_Callback()
{
    //a.toggle();
}