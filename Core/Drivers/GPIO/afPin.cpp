#include "afPin.hh" 

afPin::afPin():ioPin()
{
    init();    
}

afPin::~afPin()
{
}


void afPin::setAlternatefunction(const gpioAlternateFunction &)
{

}


void afPin::init()
{
    ioPin::initHandler(gpioMode::alternateFunction);
    _alternateFunction = gpioAlternateFunction::_0;
}
void afPin::init(const gpioAlternateFunction & af)
{
    uint32_t afLowRegisterMask = 0x7U; /* 0x7 -> 0b111 */
    paramType pin = _settings[static_cast<paramType>(gpioParameters::pin)];
    paramType alternateFunction = static_cast<paramType>(af);
    _instance->AFR[pin >> 3 ] &= ~ (GPIO_AFRL_AFSEL0_Msk << (4U * (pin & afLowRegisterMask)));
    _instance->AFR[pin >> 3 ] |= (alternateFunction << (4U * (pin & afLowRegisterMask)));

}

template<>
bool afPin::initHandler(const gpioPort & param)
{
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioPin & param)
{
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioMode & param)
{
    _status = gpiostatusCode::wrongParamPassed;
    return false;
}
template<>
bool afPin::initHandler(const gpioPUPD & param)
{
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioOutputType & param)
{
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioOutputSpeed & param)
{
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioState &param)
{
    _status = gpiostatusCode::wrongParamPassed;
}
template<>
bool afPin::initHandler(const gpioAlternateFunction &param)
{
    
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        _alternateFunction = param;
        if(isReady())
        {
            init(param);
            _status = gpiostatusCode::ready;
            return true;
        }
        else
        {
            gpioParameters paramType = getParamIndex(param);
            _queuedSettings |= static_cast<uint16_t>(0x1 << static_cast<paramIndex>(paramType));
            _status = gpiostatusCode::reset;
            return false;
        }


    }
    else if(_status == gpiostatusCode::busy)
    {
        
    }
    else
    {

    }
    return false;
}
        
gpioParameters afPin::getParamIndex(const gpioAlternateFunction &af)
{
    return gpioParameters::alternateFunction;
}