#include "inputOutputPinHandler.hh"



inputOutputPinHandler::inputOutputPinHandler(const gpioPort *port, const gpioPin *pin, const gpioMode *mode, const gpioPUPD *pupd,\
            const gpioOutputSpeed *outputSpeed, const gpioOutputType *outputType, const gpioState *state, \
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
}

inputOutputPinHandler::~inputOutputPinHandler()
{
}
