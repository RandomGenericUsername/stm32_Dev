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
bool ioPin::read() { return readIOHandler(); }
bool ioPin::write(const gpioState &state) { return writeIOHandler(state); }
bool ioPin::toggle()
{
    if(_state == gpioState::high)
    {
        return write(gpioState::low);
    }
    else
    {
        return write(gpioState::high);
    }
}
bool ioPin::reset(const bool &forceReset) { return true; }

bool ioPin::isReady()
{
    if(assertPin() && assertPort())
    {
        _status = gpiostatusCode::ready;
        return true;
    }
    _status = gpiostatusCode::reset;
    return false;
}

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
    defaultSettings();
    return true;
}

bool ioPin::modeHandler(const gpioMode &mode, const bool &checkMode)
{
    if(checkMode)
    {
        if(mode == gpioMode::alternateFunction || mode == gpioMode::analogInput)
        {
            _status = gpiostatusCode::modeNotAllowed;
            return false;
        }
    }
    init(mode);
    return true;
}

bool ioPin::initQueuedSettings()
{
    paramIndex start = static_cast<paramIndex>(gpioParameters::mode);
    paramIndex end = static_cast<paramIndex>(gpioParameters::state);
    while(_queuedSettings && start <= end)
    {
        if((0x1 << start) & _queuedSettings)
        {
            if(start == static_cast<paramType>(gpioParameters::mode)) init(_mode);
            else if(start == static_cast<paramType>(gpioParameters::pupd)) init(_pupd);
            else if(start == static_cast<paramType>(gpioParameters::oType)) init(_outputType);
            else if(start == static_cast<paramType>(gpioParameters::oSpeed)) init(_outputSpeed);
            else if(start == static_cast<paramType>(gpioParameters::state)) init(_state);
            _queuedSettings &= ~(0x1 << start);
        }
        start++;
    }
    if(_queuedSettings != 0 && start == end)
        return false;
    return true;
}

bool ioPin::readIOHandler()
{
    if(_status == gpiostatusCode::reset)
    {
        _state = gpioState::undefined;
        _status = gpiostatusCode::readingDeallocatedPin;
        if(_failSafeMode)
            gpioExceptionHandler(_status);    
        return false;
    }
    if(_status != gpiostatusCode::reset && _status != gpiostatusCode::ready)
    {
        _state = gpioState::undefined;
        if(_failSafeMode)
            gpioExceptionHandler(_status);    
        return false;
    }
    //code only reaches here if no error ocurred
    uint32_t reading = _instance->IDR & 0x1 << static_cast<uint32_t>(_pin);
    if(reading)
        _state = gpioState::high;
    else 
        _state = gpioState::low;
    return static_cast<bool>(reading);
}

bool ioPin::writeIOHandler(const gpioState &state)
{
   return initHandler(state);
}


bool ioPin::assertPort(const ioPin &obj)
{
    if(obj._port != gpioPort::null)
    {
        return true;
    }
    return false;
}

bool ioPin::assertPort() { return assertPort(*this); }

bool ioPin::assertPin(const ioPin &obj)
{
    if(obj._pin != gpioPin::null)
    {
        return true;
    }
    return false;
}

bool ioPin::assertPin() { return assertPin(*this); }


void ioPin::defaultSettings()
{
    _instance = nullptr;
    _status = gpiostatusCode::reset;
    _queuedSettings = 0;
    _failSafeMode = false;
    _debug = false;
    _port = gpioPort::null;
    _pin = gpioPin::null;
    _mode = gpioMode::input;
    _pupd = gpioPUPD::disabled;
    _outputSpeed = gpioOutputSpeed::low;
    _outputType = gpioOutputType::pushPull;
    _state = gpioState::low;
}

bool ioPin::isReAllocating(const gpioPort &port)
{
    if(isAllocated(port, _pin))
    {
        _status = gpiostatusCode::alreadyAllocatedPinError;
        return true;
    }
    return false;
}


bool ioPin::isReAllocating(const gpioPin &pin)
{
    if(isAllocated(_port, pin))
    {
        _status = gpiostatusCode::alreadyAllocatedPinError;
        return true;
    }
    return false;
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
    paramType pin = static_cast<paramType>(_pin);
    paramType Mode = static_cast<paramType>(mode);
    this->_instance->MODER &= ~(uint32_t)(GPIO_MODER_MODE0_Msk << (2U * pin));
    this->_instance->MODER |= (uint32_t)(Mode << (2U * pin));
}
void ioPin::init(const gpioOutputType &oType)
{
    paramType pin = static_cast<paramType>(_pin);
    paramType OType = static_cast<paramType>(oType);
    this->_instance->OTYPER &= ~(uint32_t)(GPIO_OTYPER_OT0_Msk << pin);
    this->_instance->OTYPER |= (uint32_t)( OType<< pin);
}

void ioPin::init(const gpioOutputSpeed &oSpeed)
{
    paramType pin = static_cast<paramType>(_pin);
    paramType param = static_cast<paramType>(oSpeed);
    this->_instance->OSPEEDR &= ~(uint32_t)(GPIO_OSPEEDR_OSPEED0_Msk << 2U * pin);
    this->_instance->OSPEEDR |= (uint32_t)(param << (2U * pin));
}

void ioPin::init(const gpioPUPD &pupd)
{
    paramType pin = static_cast<paramType>(_pin);
    paramType param = static_cast<paramType>(pupd);
    this->_instance->PUPDR &= ~(uint32_t)(GPIO_PUPDR_PUPD0_Msk << (2U * pin));
    this->_instance->PUPDR |= (uint32_t)(param << (2U * pin));
}

void ioPin::init(const gpioState &state)
{
    paramType pin = static_cast<paramType>(_pin);
    if(state == gpioState::high) this->_instance->ODR |= static_cast<uint32_t>(0x1 << pin);
    else this->_instance->ODR &= ~static_cast<uint32_t>(0x1 << pin);
}