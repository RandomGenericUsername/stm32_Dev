#ifndef _AF_PIN_H
#define _AF_PIN_H


#include "ioPin.hh"
#include "alternateFunctionBuilder.hh"

class afPin : private ioPin
{
private:
    /* data */
    gpioAlternateFunction _alternateFunction{gpioAlternateFunction::_0};
    alternateFunctionBuilder *_builder;




public:

    explicit afPin();
    explicit afPin(const gpioAlternateFunction &af);
    explicit afPin(const gpioAlternateFunction &af, const GPIO_TypeDef *port, const gpioPin &pin);
    explicit afPin(const gpioAlternateFunction &af, const gpioPort *port, const gpioPin &pin);
    ~afPin( );

    void setAlternateFunction(const gpioAlternateFunction &af);
    void setPort(const gpioPort &port);
    void setPort(const GPIO_TypeDef *port);
    void setPin(const gpioPin &pin);
};



#endif /* B4CDA144_7F30_4D04_AE9E_E111C50DC250 */
