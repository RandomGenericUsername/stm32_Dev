#include "afPin.hh" 

afPin::afPin():ioPin()
{
    initHandler();    
}

afPin::~afPin()
{
}


void afPin::setAlternatefunction(const gpioAlternateFunction &)
{

}


bool afPin::initHandler() { return setAlternateFunctionMode(); }

void afPin::init(const gpioAlternateFunction & af)
{
    uint32_t afLowRegisterMask = 0x7U; /* 0x7 -> 0b111 */
    paramType pin = _settings[static_cast<paramType>(gpioParameters::pin)];
    paramType alternateFunction = static_cast<paramType>(af);
    _instance->AFR[pin >> 3 ] &= ~ (GPIO_AFRL_AFSEL0_Msk << (4U * (pin & afLowRegisterMask)));
    _instance->AFR[pin >> 3 ] |= (alternateFunction << (4U * (pin & afLowRegisterMask)));

}

bool afPin::setAlternateFunctionMode()
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        //gpioParameters _paramIndex = ioPin::getParamIndex(gpioMode::alternateFunction);
        //_settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(gpioMode::alternateFunction);
        return modeHandler(gpioMode::alternateFunction, false);

    }
    else if(_status == gpiostatusCode::busy)
    {
        
    }
    else
    {

    }
    return false;
}

template<>
bool afPin::initHandler(const gpioPort & param)
{
    if(!ioPin::initHandler(param))return false;
    if(isReady() && _queuedSetting)
    {
        init(_alternateFunction);
        _queuedSetting = false;
    }
    return true;
}
template<>
bool afPin::initHandler(const gpioPin & param)
{
    if(!ioPin::initHandler(param))return false;
    if(isReady() && _queuedSetting)
    {
        init(_alternateFunction);
        _queuedSetting = false;
    }
    return true;
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
bool afPin::initHandler(const gpioAlternateFunction &param)
{
    
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        _alternateFunction = param;
        if(isReady())
        {
            init(param);
            _status = gpiostatusCode::ready;
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

        