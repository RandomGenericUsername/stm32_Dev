#include "afPin.hh"

afPin::afPin(/* args */):ioPin()
{
    
}

afPin::afPin(const gpioAlternateFunction &af)
{

}
afPin::afPin(const gpioAlternateFunction &af, const GPIO_TypeDef *port, const gpioPin &pin)
{

}
afPin::afPin(const gpioAlternateFunction &af, const gpioPort *port, const gpioPin &pin)
{

}
afPin::~afPin()
{

}

void afPin::setAlternateFunction(const gpioAlternateFunction &af)
{
    _alternateFunction = af;
}
void afPin::setPort(const gpioPort &port)
{
    ::ioPin::setPort(port);
}
void afPin::setPort(const GPIO_TypeDef *port)
{
    ::ioPin::setPort(port);
}
void afPin::setPin(const gpioPin &pin)
{
    ::ioPin::setPin(pin);
}