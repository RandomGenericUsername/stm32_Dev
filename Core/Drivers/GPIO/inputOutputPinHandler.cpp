#include "inputOutputPinHandler.hh"

uint16_t inputOutputPinHandler::allocatedPins[NUMBER_OF_PORTS]{0};

inputOutputPinHandler::inputOutputPinHandler(const gpioPort *port, const gpioPin *pin, const gpioMode *mode, const gpioPUPD *pupd,
                                             const gpioOutputSpeed *outputSpeed, const gpioOutputType *outputType, const gpioState *state,
                                             const gpiostatusCode *status, const bool *failSafe, const bool *debug)
{
    _port = const_cast<gpioPort *>(port);
    _pin = const_cast<gpioPin *>(pin);
    _mode = const_cast<gpioMode *>(mode);
    _pupd = const_cast<gpioPUPD *>(pupd);
    _outputSpeed = const_cast<gpioOutputSpeed *>(outputSpeed);
    _outputType = const_cast<gpioOutputType *>(outputType);
    _pinState = const_cast<gpioState *>(state);
    _status = const_cast<gpiostatusCode *>(status);
    _hardException = const_cast<bool *>(failSafe);
    _debug = const_cast<bool *>(debug);
    _queuedSettings = 0;
}

inputOutputPinHandler::~inputOutputPinHandler()
{
}

bool inputOutputPinHandler::portSettings(const gpioPort &port, inputOutputPinHandler *obj)
{
    if (isReallocating(port, obj))
    {
        *obj->_status = gpiostatusCode::alreadyAllocatedPinError;
        if (*obj->_hardException == true)
            while (1)
                ;
        return false;
    }
    if (!setParam(port, obj))
        return false;
    init(*obj->_port, obj);
    if (isReady(obj))
    {
        allocatedPins[static_cast<paramType>(*obj->_port)] |= 0x1 << static_cast<paramType>(*obj->_pin);
        if (obj->_queuedSettings != 0)
            return initQueuedSettings(obj);
    }
    return true;
}

bool inputOutputPinHandler::pinSettings(const gpioPin &pin, inputOutputPinHandler *obj)
{
    if (isReallocating(pin, obj))
    {
        *obj->_status = gpiostatusCode::alreadyAllocatedPinError;
        if (*obj->_hardException == true)
            while (1)
                ;
        return false;
    }
    if (!setParam(pin, obj))
        return false;
    init(*obj->_pin, obj);
    if (isReady(obj))
    {
        allocatedPins[static_cast<paramType>(*obj->_port)] |= 0x1 << static_cast<paramType>(*obj->_pin);
        if (obj->_queuedSettings != 0)
            return initQueuedSettings(obj);
    }
    return true;
}

bool inputOutputPinHandler::modeSettings(const gpioMode &mode, inputOutputPinHandler *obj, const bool &checkMode)
{
    if (checkMode)
    {
        if (mode == gpioMode::alternateFunction || mode == gpioMode::analogInput)
        {
            *obj->_status = gpiostatusCode::modeNotAllowed;
            if (*obj->_hardException == true)
                while (1)
                    ;
            return false;
        }
    }
    return generalSettings(mode, obj);
}

bool inputOutputPinHandler::initQueuedSettings(inputOutputPinHandler *obj)
{
    uint8_t IterationN{0};
    while (obj->_queuedSettings && IterationN < NUMBER_OF_PIN_PARAMS)
    {
        if ((0x1 << IterationN) & obj->_queuedSettings)
        {
            if (IterationN == static_cast<paramType>(gpioParameters::mode))
                init(*obj->_mode, obj);
            else if (IterationN == static_cast<paramType>(gpioParameters::pupd))
                init(*obj->_pupd, obj);
            else if (IterationN == static_cast<paramType>(gpioParameters::outputType))
                init(*obj->_outputType, obj);
            else if (IterationN == static_cast<paramType>(gpioParameters::outputSpeed))
                init(*obj->_outputSpeed, obj);
            else if (IterationN == static_cast<paramType>(gpioParameters::state))
                init(*obj->_pinState, obj);
            obj->_queuedSettings &= ~(0x1 << IterationN);
        }
        IterationN++;
    }
    if (obj->_queuedSettings != 0 || IterationN > NUMBER_OF_PIN_PARAMS)
    {
        *obj->_status = gpiostatusCode::initQueuedSettingsFailed;
        if (*obj->_hardException == true)
            while (1)
                ;
        return false;
    }
    return true;
}
bool inputOutputPinHandler::isPortSet(const inputOutputPinHandler &obj)
{
    if (*obj._port != gpioPort::null)
        return true;
    return false;
}

bool inputOutputPinHandler::isPinSet(const inputOutputPinHandler &obj)
{
    if (*obj._pin != gpioPin::null)
        return true;
    return false;
}
bool inputOutputPinHandler::isReady(const inputOutputPinHandler *obj)
{
    if (isPinSet(*obj) && isPortSet(*obj))
        return true;
    return false;
}
bool inputOutputPinHandler::isReady()
{
    return inputOutputPinHandler::isReady(this);
}
bool inputOutputPinHandler::isAllocated(const gpioPort &port, const gpioPin &pin)
{
    if (port != gpioPort::null && pin != gpioPin::null)
    {
        if ((allocatedPins[static_cast<paramType>(port)] & (0x1UL << static_cast<paramType>(pin))))
        {
            return true;
        }
    }
    return false;
}
bool inputOutputPinHandler::isAllocated() { return inputOutputPinHandler::isAllocated(*this->_port, *this->_pin); }
bool inputOutputPinHandler::isReallocating(const gpioPort &port, const inputOutputPinHandler *obj)
{
    if (isAllocated(port, *obj->_pin))
        return true;
    return false;
}
bool inputOutputPinHandler::isReallocating(const gpioPin &pin, const inputOutputPinHandler *obj)
{
    if (isAllocated(*obj->_port, pin))
        return true;
    return false;
}

gpioPort inputOutputPinHandler::getGPIOIndex(const GPIO_TypeDef *gpio)
{
    if (gpio == GPIOA)
        return gpioPort::A;
    else if (gpio == GPIOB)
        return gpioPort::B;
    else if (gpio == GPIOC)
        return gpioPort::C;
    else if (gpio == GPIOD)
        return gpioPort::D;
    else if (gpio == GPIOE)
        return gpioPort::E;
    else if (gpio == GPIOH)
        return gpioPort::H;
}

GPIO_TypeDef *inputOutputPinHandler::getGPIO(const gpioPort &port)
{
    if (port == gpioPort::A)
        return GPIOA;
    else if (port == gpioPort::B)
        return GPIOB;
    else if (port == gpioPort::C)
        return GPIOC;
    else if (port == gpioPort::D)
        return GPIOD;
    else if (port == gpioPort::E)
        return GPIOE;
    else if (port == gpioPort::H)
        return GPIOH;
}
