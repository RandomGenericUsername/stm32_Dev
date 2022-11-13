#include "inputOutputPin.hh"

inputOutputPin::inputOutputPin(/* args */)
{
    init();
}

inputOutputPin::~inputOutputPin()
{
    delete _handler;
}


void inputOutputPin::init()
{
    _handler = new inputOutputPinHandler(&_port, &_pin, &_mode, &_pupd, &_outputSpeed, &_outputType, &_pinState, &_status, &_hardException, &_debug);
}