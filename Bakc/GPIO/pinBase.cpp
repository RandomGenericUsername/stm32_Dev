#include "pinBase.hh"


//pinBase::~pinBase()
//{
//}
// 
//void pinBase::_init(gpioPort port)
//{
//    if(_port == gpioPort::A){this->_instance = GPIOA;}
//    else if(_port == gpioPort::B){this->_instance = GPIOB;}
//    else if(_port == gpioPort::C){this->_instance = GPIOC;}
//    else if(_port == gpioPort::D){this->_instance = GPIOD;}
//    else if(_port == gpioPort::E){this->_instance = GPIOE;}
//    else if(_port == gpioPort::H){this->_instance = GPIOH;}
//    _resetValues = *_instance;
//    RCC->AHB1ENR |= 1 << static_cast<unsigned int>(_port);
//}
//void pinBase::_init(GPIO_TypeDef* GPIOx)
//{
//    if(_instance == GPIOA){this->_port = gpioPort::A;}
//    else if(_instance == GPIOB ){_port = gpioPort::B;}
//    else if(_instance == GPIOC ){_port = gpioPort::C;}
//    else if(_instance == GPIOD ){_port = gpioPort::D;}
//    else if(_instance == GPIOE ){_port = gpioPort::E;}
//    else if(_instance == GPIOH ){_port = gpioPort::H;}
//    _resetValues = *_instance;
//    RCC->AHB1ENR |= 1 << static_cast<unsigned int>(_port);
//}
//void pinBase::_init(gpioPin pin)
//{
//     _pin = pin;
//}
//void pinBase::_init(gpioMode mode)
//{
//    this->_instance->MODER &= ~(uint32_t)(GPIO_MODER_MODE0_Msk << (static_cast<int>(_pin) * 2U ));
//    this->_instance->MODER |= (uint32_t)(static_cast<unsigned int>(_mode) << (static_cast<int>(_pin) * 2U ));
//}
//void pinBase::_init(gpioOutputType outputType)
//{
//    this->_instance->OTYPER &= ~(uint32_t)(GPIO_OTYPER_OT0_Msk << (static_cast<int>(_pin)));
//    this->_instance->OTYPER |= (uint32_t)(static_cast<unsigned int>(_outputType) << (static_cast<int>(_pin)));
//}
//void pinBase::_init(gpioPUPD pupd)
//{
//    this->_instance->PUPDR &= ~(uint32_t)(GPIO_PUPDR_PUPD0_Msk << (static_cast<int>(_pin) * 2U));
//    this->_instance->PUPDR |= (uint32_t)(static_cast<unsigned int>(_pupd) << (static_cast<int>(_pin) * 2U));
//}
//void pinBase::_init(gpioOutputSpeed outputSpeed)
//{
//    this->_instance->OSPEEDR &= ~(uint32_t)(GPIO_OSPEEDR_OSPEED0_Msk << (static_cast<int>(_pin) * 2U));
//    this->_instance->OSPEEDR |= (uint32_t)(static_cast<unsigned int>(_outputSpeed) << (static_cast<int>(_pin) * 2U));
//}
//void pinBase::_init(gpioAlternateFunction alternate_function)
//{
//    uint32_t pin = static_cast<unsigned int>(_pin);
//    uint32_t afLowRegisterMask = 0x7U; /* 0x7 -> 0b111 */
//    uint32_t afHighOrLow = (4U * (pin & afLowRegisterMask));
//    uint32_t temp;
//    temp = _instance->AFR[pin >> 3];
//    temp &= ~(GPIO_AFRL_AFSEL0_Msk << afHighOrLow);
//    temp |= ((static_cast<unsigned int>(_alternateFunction)) & (GPIO_AFRL_AFSEL0_Msk << afHighOrLow));
//    _instance->AFR[pin >> 3] = (uint32_t)temp;
//
//}
//void pinBase::_init(NVIC_INTERRUPT_PRIORITY interruptPriority)
//{
//    /* enable SYSCFG clock */
//    uint8_t pin = static_cast<unsigned int>(_pin);
//    uint8_t port = static_cast<unsigned int>(_port);
//    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//    SYSCFG->EXTICR[pin >> 2] &= ~(0xF << (4U * (pin & 0x3U)));
//    SYSCFG->EXTICR[pin >> 2] |= (uint32_t)(port << (4U * (pin & 0x3U)));
//}
//void pinBase::_init(gpioExtTrigger trigger)
//{
//    uint8_t pin = static_cast<unsigned int>(_pin);
//    EXTI->EMR &= ~(EXTI_EMR_MR0_Msk << pin);
//    EXTI->EMR |= EXTI_EMR_EM0 << pin;
//}
//void pinBase::_init(gpioExtEvent extEventEnable)
//{
//
//
//}
//void pinBase::_init(gpioExtInterrupt extInterruptEnable)
//{
//
//
//}