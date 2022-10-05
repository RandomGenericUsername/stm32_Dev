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

bool afPin::afManager(const gpioAlternateFunction &)
{

}

void afPin::init()
{
    _alternateFunction = gpioAlternateFunction::_0;
}
void afPin::init(const gpioAlternateFunction & af)
{

}