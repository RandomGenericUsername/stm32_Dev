#include "ioPin.hh"

//template ioPin::ioPin<ioPinParams>(ioPinParams params);

ioPin::ioPin()
{
    init();
}

//ioPin::ioPin(const ioPinParams &params)
//{
    //init();
    //init(params);
//}
ioPin::~ioPin()
{

}



void ioPin::setPort(const GPIO_TypeDef *GPIOx)
{
    init(GPIOx);
}
void ioPin::setPort(const gpioPort::gpioPort &port)
{
    init(port);
}
void ioPin::setPin(const gpioPin::gpioPin &pin)
{
    init(pin);
}

void ioPin::setMode(const gpioMode::gpioMode &mode)
{
    init(mode);
}
void ioPin::setPUPD(const gpioPUPD::gpioPUPD &pupd)
{
    init(pupd);
}
void ioPin::setOutputType(const gpioOutputType::gpioOutputType &outputType)
{
    init(outputType);
}
void ioPin::setOutputSpeed(const gpioOutputSpeed::gpioOutputSpeed &outputSpeed)
{
    init(outputSpeed);
}

bool ioPin::read()
{
}
void ioPin::write(const gpioState::gpioState &state)
{
    init(state);
}

bool ioPin::reset(bool forceReset)
{

}












bool ioPin::setDefaultParams()
{
    _settings[paramIndex::port] = gpioPort::gpioPort::null;
    _settings[paramIndex::pin] =  gpioPin::gpioPin::null;
    _settings[paramIndex::mode] = gpioMode::gpioMode::input;
    _settings[paramIndex::pin] = gpioPUPD::gpioPUPD::disabled;
    //_settings[paramIndex::]  = gpioOutputType::gpioOutputType::pushPull,
    //_settings[paramIndex::] d = gpioOutputSpeed::gpioOutputSpeed::low,
    //_settings[paramIndex::]  = gpioState::gpioState::low,
    return true;
}

bool ioPin::init()
{
    if(&_settings != nullptr)
    {
        setDefaultParams(); 
        _status = gpioStatus::reset;
        _isParamSet = 0;
        return true;
    } 
    else return false;
}
bool ioPin::init(const GPIO_TypeDef *port)
{
    _settings[paramIndex::port] = getGPIOIndex(port);
    _isParamSet |= 0x1 << paramIndex::port;
    return true;
}
bool ioPin::init(const gpioPort::gpioPort &port)
{
    _settings[paramIndex::port] = port;
    _isParamSet |= 0x1 << paramIndex::port;

}
bool ioPin::init(const settings_t params[])
{
    //_settings = params;
    _isParamSet = 127; 
    return true;
}
bool ioPin::init(const gpioPin::gpioPin &pin)
{
    _settings[paramIndex::pin] = pin;
    _isParamSet |= 0x1 << paramIndex::pin;
    
    return true;
}
bool ioPin::init(const gpioMode::gpioMode &mode)
{
    _settings[paramIndex::mode] = mode;
    _isParamSet |= 0x1 << paramIndex::mode;
}
bool ioPin::init(const gpioPUPD::gpioPUPD &pupd)
{
    _settings[paramIndex::pupd] = pupd;
    _isParamSet |= 0x1 << paramIndex::pupd;
}

bool ioPin::init(const gpioOutputType::gpioOutputType &oType)
{
    _settings[paramIndex::oType] = oType;
    _isParamSet |= 0x1 << paramIndex::oType;
}
bool ioPin::init(const gpioOutputSpeed::gpioOutputSpeed &oSpeed)
{
    _settings[paramIndex::oSpeed] = oSpeed;
    _isParamSet |= 0x1 << paramIndex::oSpeed;
}
bool ioPin::init(const gpioState::gpioState &state)
{
    _settings[paramIndex::state] = state;
    _isParamSet |= 0x1 << paramIndex::state;

}