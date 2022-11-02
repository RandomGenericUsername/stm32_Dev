#include "UART.hh"

UART::UART(/* args */)
{
}

UART::~UART()
{
}


bool UART::initHandler()
{
    //set default params.
}
template<> bool UART::initHandler<USART_TypeDef*>(USART_TypeDef *const &)
{

}
template<> bool UART::initHandler<rx>(const rx &)
{

}
template<> bool UART::initHandler<tx>(const tx &)
{

}
template<> bool UART::initHandler<baudRateValues>(const baudRateValues &)
{

}
template<> bool UART::initHandler<wordLength>(const wordLength &)
{

}
template<> bool UART::initHandler<parity>(const parity &)
{

}