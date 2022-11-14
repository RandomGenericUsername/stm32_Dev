#include "inputOutputPin.hh"

inputOutputPin::inputOutputPin(/* args */)
{
    _handler = new inputOutputPinHandler(&_port, &_pin, &_mode, &_pupd, &_outputSpeed, &_outputType, &_pinState, &_status, &_hardException, &_debug);
}

inputOutputPin::~inputOutputPin()
{
    delete _handler;
}

bool inputOutputPin::setPort(const gpioPort &port)
{
    return _handler->initHandler(port);
}
bool inputOutputPin::setPin(const gpioPin &pin)
{
    return _handler->initHandler(pin);
}
bool inputOutputPin::setMode(const gpioMode &mode)
{
    return _handler->initHandler(mode);
}
bool inputOutputPin::setInputMode()
{
    return _handler->initHandler(gpioMode::input);
}
bool inputOutputPin::setOutputMode()
{
    return _handler->initHandler(gpioMode::output);
}
bool inputOutputPin::setPUPD(const gpioPUPD &pupd)
{
    return _handler->initHandler(pupd);
}
bool inputOutputPin::setOutputType(const gpioOutputType &outputType)
{
    return _handler->initHandler(outputType);
}
bool inputOutputPin::setOutputSpeed(const gpioOutputSpeed &outputSpeed)
{
    return _handler->initHandler(outputSpeed);
}
bool inputOutputPin::read()
{
}
bool inputOutputPin::write(const gpioState &state)
{
    return _handler->initHandler(state);
}
bool inputOutputPin::toggle()
{
}
bool inputOutputPin::reset(const bool &forceReset)
{
}
bool inputOutputPin::isReady()
{
    return _handler->isReady();
}
bool inputOutputPin::isAllocated(const gpioPort &port, const gpioPin &pin)
{
    return inputOutputPinHandler::isAllocated(port, pin);
}
void inputOutputPin::hardExceptionMode(const bool &enable)
{
    if(enable)
        _handler->initHandler(gpioHardException::enable);
    else
        _handler->initHandler(gpioHardException::disable);
}
void inputOutputPin::enableDebug(const bool &enable)
{
    if(enable)
        _handler->initHandler(gpioDebug::enable);
    else
        _handler->initHandler(gpioDebug::disable);
}
