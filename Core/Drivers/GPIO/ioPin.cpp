#include "ioPin.hh"

uint16_t ioPin::allocatedPins[NUMBER_OF_PORTS]{0};

ioPin::ioPin() { initHandler(); }
ioPin::~ioPin() { }
ioPin::ioPin(const ioPin &Obj) { } 
ioPin& ioPin::operator=(const ioPin &pin) { }

bool ioPin::setPort(const gpioPort &port) { return initHandler(port); }
bool ioPin::setPin(const gpioPin &pin) { return initHandler(pin); } 
bool ioPin::setMode(const gpioMode &mode) { return initHandler(mode); }
bool ioPin::setPUPD(const gpioPUPD &pupd) { return initHandler(pupd); }
bool ioPin::setOutputType(const gpioOutputType &outputType) { return initHandler(outputType); }
bool ioPin::setOutputSpeed(const gpioOutputSpeed &outputSpeed) { return initHandler(outputSpeed);}
bool ioPin::read() { return readHandler(); }
bool ioPin::write(const gpioState &state) { return initHandler(state); }
bool ioPin::toggle()
{
    if(_settings[static_cast<paramType>(gpioParameters::state)] == static_cast<paramType>(gpioState::high))
    {
        return write(gpioState::low);
    }
    else
    {
        return write(gpioState::high);
    }
}
bool ioPin::reset(const bool &forceReset) { return true; }


bool ioPin::isAllocated(const gpioPort &port, const gpioPin &pin)
{
    if(pin != gpioPin::null && port != gpioPort::null)
    {
        if((allocatedPins[static_cast<paramType>(port)] & (0x1UL << static_cast<paramType>(pin))))
        {
            return true;
        }
    }
    return false;
}

bool ioPin::isReady()
{
    if(assertPin() && assertPort())
    {
        return true;
    }
    return false;
}


void ioPin::failSafeMode(const bool &enable)
{
    _failSafeMode = enable;
}

void ioPin::enableDebug(const bool &enable)
{
   _debug = enable; 
}


bool ioPin::initHandler()
{
    _instance = nullptr;
    setDefaultParams(); 
    _status = gpiostatusCode::reset;
    _queuedSettings = 0;
    _failSafeMode = false;
    return true;
}

template<>
bool ioPin::initHandler<gpioPort>(const gpioPort &port)
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(port);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(port);
        return portHandler(port);

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
        return pinHandler(pin);

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
        return modeHandler(mode);

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
        return settingsHandler(param);

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
        return settingsHandler(param);

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
        return settingsHandler(param);

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
        return settingsHandler(param);

    }
    else if(_status == gpiostatusCode::busy)
    {
        
    }
    else
    {

    }
    return false;
}

bool ioPin::readHandler()
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        if(!isReady())
        {
            _status = gpiostatusCode::readingDeallocatedPin;
            return false;
        }
        return _instance->IDR & 0x1 << _settings[static_cast<paramType>(gpioParameters::pin)];
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
bool ioPin::initHandler(const bool &enable)
{
    failSafeMode(enable);
    return true;
}

template<class T>
bool ioPin::settingsHandler(const T &param)
{
    if(isReady())
    {
        init(param);
        _status = gpiostatusCode::ready;
    }
    else
    {
        //queues the current setting
        gpioParameters paramType = getParamIndex(param);
        _queuedSettings |= static_cast<uint16_t>(0x1 << static_cast<paramIndex>(paramType));
        _status = gpiostatusCode::reset;
    }
    return true;
}



bool ioPin::portHandler(const gpioPort &param)
{
    //if pin is set, check for stagged and init
    if(assertPin())
    {
        if(isAllocated( static_cast<gpioPort>(param), static_cast<gpioPin>(_settings[static_cast<paramIndex>(gpioParameters::pin)]) ))
        {
            _status = gpiostatusCode::alreadyAllocatedPinError;
            if(_failSafeMode) gpioExceptionHandler(_status);
            return false;
        }
        else
        {
            init(param);
            _status = gpiostatusCode::ready;
            allocatedPins[_settings[static_cast<paramType>(gpioParameters::port)]] |= static_cast<uint16_t>(0x1 << _settings[static_cast<paramType>(gpioParameters::pin)]);
            if(_queuedSettings != 0)
            {
                if(!initQueuedSettings())
                {
                    _status = gpiostatusCode::initQueuedSettingsFailed;
                    return false;
                } 
            }
        }
    }
    else
    {
        init(param);
        _status = gpiostatusCode::reset;
    }
    return true;
}
bool ioPin::pinHandler(const gpioPin &param)
{
    if(assertPort())
    {
        if( isAllocated( static_cast<gpioPort>(_settings[static_cast<paramIndex>(gpioParameters::port)]), static_cast<gpioPin>(param) ) )
        {
            _status = gpiostatusCode::alreadyAllocatedPinError;
            if(_failSafeMode) gpioExceptionHandler(_status);
            return false;
        }
        else
        {
            _status = gpiostatusCode::ready;
            allocatedPins[_settings[static_cast<paramType>(gpioParameters::port)]] |= static_cast<uint16_t>(0x1 << _settings[static_cast<paramType>(gpioParameters::pin)]);
            if(_queuedSettings != 0)
            {
                if(!initQueuedSettings())
                {
                    _status = gpiostatusCode::initQueuedSettingsFailed;
                    return false;
                } 
            }
        }
    }
    else
    {
        _status = gpiostatusCode::reset;
    }
    return true;
}

bool ioPin::modeHandler(const gpioMode &mode, const bool &failSafe)
{
    if(failSafe)
    {
        if(mode == gpioMode::alternateFunction || mode == gpioMode::analogInput)
        {
            _status = gpiostatusCode::modeNotAllowed;
            return false;
        }
    }
    settingsHandler(mode);
    return true;

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

bool ioPin::assertPort(const ioPin &obj)
{
    if(obj._settings[static_cast<paramIndex>(gpioParameters::port)] != static_cast<paramType>(gpioPort::null))
    {
        return true;
    }
    return false;
}

bool ioPin::assertPort() { return assertPort(*this); }

bool ioPin::assertPin(const ioPin &obj)
{
    if(obj._settings[static_cast<paramIndex>(gpioParameters::pin)] != static_cast<paramType>(gpioPin::null))
    {
        return true;
    }
    return false;
}

bool ioPin::assertPin() { return assertPin(*this); }

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
