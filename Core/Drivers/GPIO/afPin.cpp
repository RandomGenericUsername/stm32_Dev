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
bool afPin::initHandler(const gpioPort & param, const bool &exceptions)
{
    ioPin::enableExceptions(exceptions);
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioPin & param, const bool &exceptions)
{
    ioPin::enableExceptions(exceptions);
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioMode & param, const bool &exceptions)
{
    _status = gpiostatusCode::wrongParamPassed;
    if(exceptions)
    {
        gpioExceptionHandler(_status);
    }
    return false;
}
template<>
bool afPin::initHandler(const gpioPUPD & param, const bool &exceptions)
{
    ioPin::enableExceptions(exceptions);
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioOutputType & param, const bool &exceptions)
{
    ioPin::enableExceptions(exceptions);
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioOutputSpeed & param, const bool &exceptions)
{
    ioPin::enableExceptions(exceptions);
    return ioPin::initHandler(param);
}
template<>
bool afPin::initHandler(const gpioState &param, const bool &exceptions)
{
    _status = gpiostatusCode::wrongParamPassed;
    if(exceptions)
    {
        gpioExceptionHandler(_status);
    }
    return false;
}
template<>
bool afPin::initHandler(const gpioAlternateFunction &param, const bool &exceptions)
{
    if(exceptions) ioPin::enableExceptions();
    
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