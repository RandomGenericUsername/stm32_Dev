#include "ioPin.hh"

ioPin::ioPin()
{
    init();
}


ioPin::~ioPin()
{
    delete _builder;
}


void ioPin::setPort(GPIO_TypeDef *GPIOx)
{

}
void ioPin::setPort(const gpioPort &port)
{

}
void ioPin::setPin(const gpioPin &pin)
{

}

void ioPin::setMode(const gpioMode &mode)
{

}
void ioPin::setPUPD(const gpioPUPD &pupd)
{

}
void ioPin::setOutputType(const gpioOutputType &outputType)
{

}
void ioPin::setOutputSpeed(const gpioOutputSpeed &outputSpeed)
{

}

bool ioPin::read()
{

}
void ioPin::write(const pinState &state)
{

}

bool ioPin::reset(bool forceReset)
{

}












bool ioPin::setDefaultParams()
{
    _settings = {
       .port = gpioPort::null,
       .pin = gpioPin::null,
       .mode = gpioMode::input,
       .pupd = gpioPUPD::disabled,
       .oType = gpioOutputType::pushPull,
       .oSpeed = gpioOutputSpeed::low,
       .state = pinState::low,
    };
    return true;
}

bool ioPin::init()
{
    if(&_settings != nullptr)
    {
        setDefaultParams(); 
        _status = gpioStatus::reset;
        _isParamSet = 0;
        _builder = new pinBuilder(&_settings, &_isParamSet, &_status);
        return true;
    } 
    else return false;
}
bool ioPin::init(const GPIO_TypeDef *port)
{
    _settings.port= getGPIOIndex(port);
    _isParamSet |= 0x1 << portParam;
    bool temp = _builder->manager(_settings.port);
    return temp;
}
bool ioPin::init(const gpioPort &port)
{
    _settings.port = port;
    _isParamSet |= 0x1 << portParam;
    return _builder->manager(port);

}
bool ioPin::init(const gpioPin &pin)
{
    _settings.pin = pin;
    _isParamSet |= 0x1 << pinParam;
    _builder->manager(pin);
    return true;
}
bool ioPin::init(const gpioMode &mode)
{
    _settings.mode = mode;
    _isParamSet |= 0x1 << modeParam;
    return _builder->manager(mode);
}
bool ioPin::init(const gpioPUPD &pupd)
{
    _settings.pupd = pupd;
    _isParamSet |= 0x1 << pupdParam;
    return _builder->manager(pupd);
}

bool ioPin::init(const gpioOutputType &oType)
{
    _settings.oType = oType;
    _isParamSet |= 0x1 << oTypeParam;
    return _builder->manager(oType);
}
bool ioPin::init(const gpioOutputSpeed &oSpeed)
{
    _settings.oSpeed = oSpeed;
    _isParamSet |= 0x1 << oSpeedParam;
    return _builder->manager(oSpeed);
}
bool ioPin::init(const pinState &state)
{
    _settings.state = state;
    _isParamSet |= 0x1 << stateParam;
    return _builder->manager(state);

}