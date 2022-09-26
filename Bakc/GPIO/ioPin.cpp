#include "ioPin.hh"

    
void ioPin::setDefaultParams()
{
    *_settings = {
        .port = gpioPort::null,
        .pin = gpioPin::null,
        .mode = gpioMode::input,
        .pupd = gpioPUPD::disabled,
        .oType = gpioOutputType::pushPull,
        .oSpeed = gpioOutputSpeed::low,
        .state = pinState::low
    };
}


void ioPin::setParam(const GPIO_TypeDef *GPIOx)
{
    _settings->port = getGPIOIndex(GPIOx); 
    _isParamSet[portParam] = true;
    _builder->manager(GPIOx);
}
void ioPin::setParam(const gpioPort &GPIOx)
{ 
    _settings->port = GPIOx; 
    _isParamSet[portParam] = true;
    _builder->manager(GPIOx);
}
void ioPin::setParam(const gpioPin &pin) 
{ 
    _settings->pin = pin; 
    _isParamSet[pinParam] = true;
    _builder->manager(pin);
}
void ioPin::setParam(const gpioMode &mode)
{
    //_settings->mode = gpioMode::output; 
    _mode = mode;
    _isParamSet[modeParam] = true;
    _builder->manager(mode); 
}
void ioPin::setParam(const gpioPUPD &pupd)
{
    _settings->pupd = pupd; 
    _isParamSet[pupdParam] = true;
    _builder->manager(pupd); 
}
void ioPin::setParam(const gpioOutputType &outputType)
{
    _settings->oType = outputType; 
    _isParamSet[oTypeParam] = true;
    _builder->manager(outputType); 
}
void ioPin::setParam(const gpioOutputSpeed &outputSpeed)
{
    _settings->oSpeed = outputSpeed; 
    _isParamSet[oSpeedParam] = true;
    _builder->manager(outputSpeed); 
}
void ioPin::setParam(const pinState &state)
{
    _settings->state = state; 
    _isParamSet[stateParam] = true;
    _builder->writeODR(state);
}


void ioPin::setPort(GPIO_TypeDef *GPIOx)
{ 
    setParam(GPIOx); 
}

void ioPin::setPort(const gpioPort &port)
{
    setParam(port);
}
void ioPin::setPin(const gpioPin &pin)
{ 
    setParam(pin); 
}

void ioPin::setMode(const gpioMode &mode)
{
    setParam(mode);
}

void ioPin::setPUPD(const gpioPUPD &pupd)
{
    setParam(pupd);
}
void ioPin::setOutputType(const gpioOutputType &outputType)
{
    setParam(outputType);
}

void ioPin::setOutputSpeed(const gpioOutputSpeed &outputSpeed)
{
    setParam(outputSpeed);
}

bool ioPin::read()
{
    return _builder->readIDR(); 
}
void ioPin::write(const pinState &state)
{
    setParam(state);
}

bool ioPin::reset(bool forceReset)
{

}