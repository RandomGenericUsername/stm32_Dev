#include "ExtInterrupt.hh"

gpioPort ExtInterrupt::_allocatdInterrupts[NUMBER_OF_PINS] = {gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null, gpioPort::null};
bool testoVar = false;


ExtInterrupt::ExtInterrupt(/* args */)
{
    initHandler();
}

ExtInterrupt::~ExtInterrupt()
{
}

bool ExtInterrupt::setInputMode()
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = ioPin::getParamIndex(gpioMode::input);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(gpioMode::input);
        return modeHandler(gpioMode::input);
    }
    else if(_status == gpiostatusCode::busy)
    {
        
    }
    else
    {

    }
    return false;
}
bool ExtInterrupt::initHandler()
{
    return setInputMode();
}

template<>
bool ExtInterrupt::initHandler<gpioPort>(const gpioPort &param)
{
    if(!ioPin::initHandler(param))return false;
    if(isReady() && _queuedSetting)
    {
        _queuedSetting = false;
        return initHandler(_trigger);
    }
    return true;
}
template<>
bool ExtInterrupt::initHandler<gpioPin>(const gpioPin &param)
{
    if(!ioPin::initHandler(param))return false;
    if(isReady() && _queuedSetting)
    {
        _queuedSetting = false;
        return initHandler(_trigger);
    }
    return true;
}
template<>
bool ExtInterrupt::initHandler<gpioPUPD>(const gpioPUPD &param)
{
    return ioPin::initHandler(param);
}
template<>
bool ExtInterrupt::initHandler<bool>(const bool &param)
{
    return ioPin::initHandler(param);
}
template<>
bool ExtInterrupt::initHandler<gpioExtTrigger>(const gpioExtTrigger &param)
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        _trigger = param;
        if(isAllocated())
        {
            _status = gpiostatusCode::alreadyAllocatedInterruptError;
            if(_failSafeMode) gpioExceptionHandler(_status);
            return false;
        }
        if(isReady())
        {
            paramType pin = _settings[static_cast<paramIndex>(gpioParameters::pin)];
            paramType port = _settings[static_cast<paramIndex>(gpioParameters::port)];
            init(param);
            _status = gpiostatusCode::ready;
            _allocatdInterrupts[pin] = static_cast<gpioPort>(port);
        }
        else
        {
            _queuedSetting = true;
            _status = gpiostatusCode::reset;
        }
        return true;

    }
    else if(_status == gpiostatusCode::busy)
    {
        
    }
    else
    {

    }
    return false;
}

bool ExtInterrupt::isAllocated(const gpioPin &pin)
{
    if(pin != gpioPin::null)
    {
        if( _allocatdInterrupts[static_cast<paramType>(pin)] != gpioPort::null )
        {
            return true;
        }
    }
    return false;
}

bool ExtInterrupt::isAllocated()
{
    gpioPin pin = (gpioPin)_settings[static_cast<paramIndex>(gpioParameters::pin)];
    return ExtInterrupt::isAllocated(pin);
}

void ExtInterrupt::init(const gpioExtTrigger &trigger)
{
    uint32_t pin = _settings[static_cast<paramType>(gpioParameters::pin)];
    uint32_t port = _settings[static_cast<paramType>(gpioParameters::port)];
    uint32_t pinMsk = 4U * (pin & 0x3U);

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[pin >> 2] &= (uint32_t) ~(SYSCFG_EXTICR1_EXTI0_Msk << pinMsk);
    SYSCFG->EXTICR[pin >> 2] |= (uint32_t) (port << pinMsk);

    if(_trigger == gpioExtTrigger::rising || _trigger == gpioExtTrigger::both)
    {
        EXTI->RTSR &= ~(EXTI_RTSR_TR0 << pin);
        EXTI->RTSR |= EXTI_RTSR_TR0 << pin;
    }
    if(_trigger == gpioExtTrigger::falling || _trigger == gpioExtTrigger::both)
    {
        EXTI->FTSR &= ~EXTI_FTSR_TR0 << pin;
        EXTI->FTSR |= EXTI_FTSR_TR0 << pin;
    }
    
    if(_priority > 15) _priority = 15;
    if(pin <= static_cast<paramType>(gpioPin::_4))
    {
        NVIC_EnableIRQ((IRQn_Type)(EXTI0_IRQn + pin));
        NVIC_SetPriority((IRQn_Type)(EXTI0_IRQn + pin), _priority );
    }
    else if(pin > static_cast<paramType>(gpioPin::_4) && pin < static_cast<paramType>(gpioPin::_10))
    {
        NVIC_EnableIRQ(EXTI9_5_IRQn);
        NVIC_SetPriority(EXTI9_5_IRQn, _priority);
    }
    else
    {
        NVIC_EnableIRQ(EXTI15_10_IRQn);
        NVIC_SetPriority(EXTI15_10_IRQn, _priority);
    }
    EXTI->IMR &= ~(EXTI_IMR_MR0_Msk << pin);
    EXTI->IMR |= EXTI_IMR_IM0 << pin;
}


/* <-----------------------------------------------------------------------------------------------------------------------------------------------------------------> */
/* <-------------------------------------------------------------------- IRQ handlers and callbacks -------------------------------------------------------------------> */
/* <-----------------------------------------------------------------------------------------------------------------------------------------------------------------> */
__attribute__((weak)) void EXTI0_Callback(){

    __NOP();

}

__attribute__((weak)) void EXTI1_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI2_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI3_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI4_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI5_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI6_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI7_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI8_Callback(){

    __NOP();

}
 __attribute__((weak)) void EXTI9_Callback(void){

     __NOP();

}
__attribute__((weak)) void EXTI10_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI11_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI12_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI13_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI14_Callback(){

    __NOP();

}
__attribute__((weak)) void EXTI15_Callback(){

    __NOP();

}

extern "C"
{
    void EXTI0_IRQHandler()
    {
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_0))) && ExtInterrupt::isAllocated(gpioPin::_0)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_0);
            EXTI0_Callback();
        }
    }


    void EXTI1_IRQHandler()
    {
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_1))) && ExtInterrupt::isAllocated(gpioPin::_1)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_1);
            EXTI1_Callback();
        }
    }
    void EXTI2_IRQHandler()
    {
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_2))) && ExtInterrupt::isAllocated(gpioPin::_2)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_2);
            EXTI2_Callback();
        }

    }
    void EXTI3_IRQHandler()
    {
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_3))) && ExtInterrupt::isAllocated(gpioPin::_3)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_3);
            EXTI3_Callback();
        }

    }
    void EXTI4_IRQHandler()
    {
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_4))) && ExtInterrupt::isAllocated(gpioPin::_4)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_4);
            EXTI4_Callback();
        }

    }
    void EXTI9_5_IRQHandler()
    {
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_5))) && ExtInterrupt::isAllocated(gpioPin::_5)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_5);
            EXTI5_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_6))) && ExtInterrupt::isAllocated(gpioPin::_6)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_6);
            EXTI6_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_7))) && ExtInterrupt::isAllocated(gpioPin::_7)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_7);
            EXTI7_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_8))) && ExtInterrupt::isAllocated(gpioPin::_8)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_8);
            EXTI8_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_9))) && ExtInterrupt::isAllocated(gpioPin::_9)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_9);
            EXTI9_Callback();
        }
        

    }
    void EXTI15_10_IRQHandler()
    {
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_10))) && ExtInterrupt::isAllocated(gpioPin::_10)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_10);
            EXTI10_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_11))) && ExtInterrupt::isAllocated(gpioPin::_11)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_11);
            EXTI11_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_12))) && ExtInterrupt::isAllocated(gpioPin::_12)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_12);
            EXTI12_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_13))) && ExtInterrupt::isAllocated(gpioPin::_13)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_13);
            EXTI13_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_14))) && ExtInterrupt::isAllocated(gpioPin::_14)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_14);
            EXTI14_Callback();
        }
        if((EXTI->PR & (0x1 << static_cast<uint32_t>(gpioPin::_15))) && ExtInterrupt::isAllocated(gpioPin::_15)) 
        {
            EXTI->PR = 0x1 << static_cast<uint32_t>(gpioPin::_15);
            EXTI15_Callback();
        }

    }
}