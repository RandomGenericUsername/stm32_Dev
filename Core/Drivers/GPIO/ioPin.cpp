#include "ioPin.hh"

//template bool ioPin::settingsManager(const gpioMode &);
//template bool ioPin::settingsManager(const gpioPUPD &);
//template bool ioPin::settingsManager(const gpioOutputType &);
//template bool ioPin::settingsManager(const gpioOutputSpeed &);

uint16_t ioPin::initializedPins[NUMBER_OF_PORTS]{0};

ioPin::ioPin()
{
    init();
}

ioPin::~ioPin()
{


}

ioPin& ioPin::operator=(const ioPin &pin)
{

}

template<>
bool ioPin::initHandler<gpioPort>(const gpioPort &port)
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(port);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(port);
        return portManager(port);

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
bool ioPin::initHandler<gpioPin>(const gpioPin &pin)
{

    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(pin);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(pin);
        return pinManager(pin);

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
bool ioPin::initHandler(const gpioMode &mode)
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(mode);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(mode);
        return settingsManager(mode);

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
bool ioPin::initHandler(const gpioPUPD &param)
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(param);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(param);
        return settingsManager(param);

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
bool ioPin::initHandler(const gpioOutputType &param)
{

    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(param);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(param);
        return settingsManager(param);

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
bool ioPin::initHandler(const gpioOutputSpeed &param)
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(param);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(param);
        return settingsManager(param);

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
bool ioPin::initHandler(const gpioState &param)
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(param);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(param);
        return settingsManager(param);

    }
    else if(_status == gpiostatusCode::busy)
    {
        
    }
    else
    {

    }
    return false;
}

template<class T>
bool ioPin::settingsManager(const T &param)
{
    bool retVal = false;
    if(isReady())
    {
        init(param);
        _status = gpiostatusCode::ready;
        retVal = true;
    }
    else
    {
        //queues the current setting
        gpioParameters paramType = getParamIndex(param);
        _queuedSettings |= static_cast<uint16_t>(0x1 << static_cast<paramIndex>(paramType));
        _status = gpiostatusCode::reset;
        retVal = false;
    }
    return retVal;
}


void ioPin::setPort(const gpioPort &port)
{
    initHandler(port);
}
void ioPin::setPin(const gpioPin &pin)
{
    initHandler(pin);
}

void ioPin::setMode(const gpioMode &mode)
{
    initHandler(mode);
}
void ioPin::setPUPD(const gpioPUPD &pupd)
{
    initHandler(pupd);
}
void ioPin::setOutputType(const gpioOutputType &outputType)
{
    initHandler(outputType);
}
void ioPin::setOutputSpeed(const gpioOutputSpeed &outputSpeed)
{
    initHandler(outputSpeed);
}

bool ioPin::read()
{
    return _instance->IDR & 0x1 << _settings[static_cast<paramType>(gpioParameters::pin)];
}
void ioPin::write(const gpioState &state)
{
    initHandler(state);
}

bool ioPin::reset(const bool &forceReset)
{
    return true;
}


bool ioPin::isPinSet(const gpioPort &port, const gpioPin &pin)
{
    if(pin != gpioPin::null && port != gpioPort::null)
    {
        if((initializedPins[static_cast<paramType>(port)] & (0x1UL << static_cast<paramType>(pin))))
        {
            return true;
        }
    }
    return false;
}

bool ioPin::isReady(const ioPin &pinObj)
{
    if(assertPin(pinObj) && assertPort(pinObj))
    {
        return true;
    }
    return false;
}

bool ioPin::isReady()
{
    return isReady(*this);
}

void ioPin::enableExceptions(const bool &enable)
{
    if(enable) _enableExceptions = true;
    else _enableExceptions = false;
}

bool ioPin::portManager(const gpioPort &param)
{
    //if pin is set, check for stagged and init
    bool retVal = false;
    if(assertPin())
    {
        if(isPinSet( static_cast<gpioPort>(param), static_cast<gpioPin>(_settings[static_cast<paramIndex>(gpioParameters::pin)]) ))
        {
            _status = gpiostatusCode::alreadyAllocatedPinError;
            retVal = false;
            if(_enableExceptions) gpioExceptionHandler(_status);
        }
        else
        {
            init(param);
            _status = gpiostatusCode::ready;
            retVal = true;
            initializedPins[_settings[static_cast<paramType>(gpioParameters::port)]] |= static_cast<uint16_t>(0x1 << _settings[static_cast<paramType>(gpioParameters::pin)]);
            if(_queuedSettings != 0)
            {
                if(!initQueuedSettings())
                {
                    _status = gpiostatusCode::initQueuedSettingsFailed;
                    retVal = false;
                    if(_enableExceptions) gpioExceptionHandler(_status);
                } 
            }
        }
    }
    else
    {
        init(param);
        _status = gpiostatusCode::reset;
        retVal = false;
    }
    return retVal;
}
bool ioPin::pinManager(const gpioPin &param)
{
    bool retVal = false;
    if(assertPort())
    {
        if( isPinSet( static_cast<gpioPort>(_settings[static_cast<paramIndex>(gpioParameters::port)]), static_cast<gpioPin>(param) ) )
        {
            _status = gpiostatusCode::alreadyAllocatedPinError;
            retVal = false;
            if(_enableExceptions) gpioExceptionHandler(_status);
        }
        else
        {
            _status = gpiostatusCode::ready;
            retVal = true;
            initializedPins[_settings[static_cast<paramType>(gpioParameters::port)]] |= static_cast<uint16_t>(0x1 << _settings[static_cast<paramType>(gpioParameters::pin)]);
            if(_queuedSettings != 0)
            {
                if(!initQueuedSettings())
                {
                    _status = gpiostatusCode::initQueuedSettingsFailed;
                    retVal = false;
                    if(_enableExceptions) gpioExceptionHandler(_status);
                } 
            }
        }
    }
    else
    {
        _status = gpiostatusCode::reset;
        retVal = false;
    }
    return retVal;
}

bool ioPin::initQueuedSettings()
{
    paramIndex start = static_cast<paramIndex>(gpioParameters::mode);
    paramIndex end = (static_cast<paramIndex>(gpioParameters::state) + 1);

    while(_queuedSettings && start != end)
    {
        if((0x1 << start) & _queuedSettings)
        {
            if(start == static_cast<paramType>(gpioParameters::mode)) init(static_cast<gpioMode>(_settings[start]));
            else if(start == static_cast<paramType>(gpioParameters::pupd)) init(static_cast<gpioPUPD>(_settings[start]));
            else if(start == static_cast<paramType>(gpioParameters::oType)) init(static_cast<gpioOutputType>(_settings[start]));
            else if(start == static_cast<paramType>(gpioParameters::oSpeed)) init(static_cast<gpioOutputSpeed>(_settings[start]));
            else if(start == static_cast<paramType>(gpioParameters::state)) init(static_cast<gpioState>(_settings[start]));
            _queuedSettings &= ~(0x1 << start);
        }
        start++;
    }
    
    if(_queuedSettings != 0 && start == end)
    {
        return false;
    }
    else 
    {
        return true;
    }
}



void ioPin::setDefaultParams()
{
    _settings[static_cast<paramIndex>(gpioParameters::port)]   =  static_cast<paramType>(gpioPort::null);
    _settings[static_cast<paramIndex>(gpioParameters::pin)]    =  static_cast<paramType>(gpioPin::null);
    _settings[static_cast<paramIndex>(gpioParameters::mode)]   =  static_cast<paramType>(gpioMode::input);
    _settings[static_cast<paramIndex>(gpioParameters::pupd)]   =  static_cast<paramType>(gpioPUPD::disabled);
    _settings[static_cast<paramIndex>(gpioParameters::oType)]  =  static_cast<paramType>(gpioOutputType::pushPull);
    _settings[static_cast<paramIndex>(gpioParameters::oSpeed)] =  static_cast<paramType>(gpioOutputSpeed::low);
    _settings[static_cast<paramIndex>(gpioParameters::state)]  =  static_cast<paramType>(gpioState::low);
}

void ioPin::init()
{
    _instance = nullptr;
    setDefaultParams(); 
    _status = gpiostatusCode::reset;
    _queuedSettings = 0;
    _enableExceptions = false;
}

void ioPin::init(const gpioPort &port)
{
    _instance = getGPIO(port);
    RCC->AHB1ENR |= static_cast<uint32_t>(RCC_AHB1ENR_GPIOAEN << static_cast<paramType>(port));
}

void ioPin::init(const gpioPin &pin)
{

}

void ioPin::init(const gpioMode &mode)
{
    paramType _pin = _settings[static_cast<paramType>(gpioParameters::pin)];
    paramType _mode = static_cast<paramType>(mode);
    this->_instance->MODER &= ~(uint32_t)(GPIO_MODER_MODE0_Msk << (2U * _pin));
    this->_instance->MODER |= (uint32_t)(_mode << (2U * _pin));
}
void ioPin::init(const gpioOutputType &oType)
{
    paramType _pin = _settings[static_cast<paramType>(gpioParameters::pin)];
    paramType _oType = static_cast<paramType>(oType);
    this->_instance->OTYPER &= ~(uint32_t)(GPIO_OTYPER_OT0_Msk << _pin);
    this->_instance->OTYPER |= (uint32_t)( _oType<< _pin);
}

void ioPin::init(const gpioOutputSpeed &oSpeed)
{
    paramType _pin = _settings[static_cast<paramType>(gpioParameters::pin)];
    paramType param = static_cast<paramType>(oSpeed);
    this->_instance->OSPEEDR &= ~(uint32_t)(GPIO_OSPEEDR_OSPEED0_Msk << 2U * _pin);
    this->_instance->OSPEEDR |= (uint32_t)(param << (2U * _pin));
}

void ioPin::init(const gpioPUPD &pupd)
{
    paramType _pin = _settings[static_cast<paramType>(gpioParameters::pin)];
    paramType param = static_cast<paramType>(pupd);
    this->_instance->PUPDR &= ~(uint32_t)(GPIO_PUPDR_PUPD0_Msk << (2U * _pin));
    this->_instance->PUPDR |= (uint32_t)(param << (2U * _pin));
}

void ioPin::init(const gpioState &state)
{
    paramType _pin = _settings[static_cast<paramType>(gpioParameters::pin)];
    if(state == gpioState::high) this->_instance->ODR |= static_cast<uint32_t>(0x1 << _pin);
    else this->_instance->ODR &= ~static_cast<uint32_t>(0x1 << _pin);
}

bool ioPin::assertPort(const ioPin & pinObj)
{
    if(pinObj._settings[static_cast<paramIndex>(gpioParameters::port)] != static_cast<paramType>(gpioPort::null))
    {
        return true;
    }
    return false;
}
bool ioPin::assertPort()
{
   return assertPort(*this);
}

bool ioPin::assertPin(const ioPin &pinObj)
{
    if(pinObj._settings[static_cast<paramIndex>(gpioParameters::pin)] != static_cast<paramType>(gpioPin::null))
    {
        return true;
    }
    return false;
}
bool ioPin::assertPin()
{
    return assertPin(*this);
}

gpioParameters ioPin::getParamIndex(const gpioPort &port)
{
    return gpioParameters::port;
}
gpioParameters ioPin::getParamIndex(const gpioPin &pin)
{
    return gpioParameters::pin;
}
gpioParameters ioPin::getParamIndex(const gpioMode &mode)
{
    return gpioParameters::mode;
}
gpioParameters ioPin::getParamIndex(const gpioOutputType &gpioOutputType)
{
    return gpioParameters::oType;
}
gpioParameters ioPin::getParamIndex(const gpioOutputSpeed &oSpeed)
{
    return gpioParameters::oSpeed;
}
gpioParameters ioPin::getParamIndex(const gpioPUPD &pudp)
{
    return gpioParameters::pupd;
}
gpioParameters ioPin::getParamIndex(const gpioState &state)
{
    return gpioParameters::state;
}
