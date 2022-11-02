#ifndef BD2B9E46_6CC2_425C_90B4_EC09601ED912
#define BD2B9E46_6CC2_425C_90B4_EC09601ED912

#include "stm32f411xe.h"

namespace usartTypes
{

    enum class wordLength
    {
        _8_DataBits = 0x0U,
        _9_DataBits = USART_CR1_M,
    };

    enum class oversamplingMode
    {
        By16 = 0x0U,
        By8 = USART_CR1_OVER8,
    };

    enum class wakeUpMethod
    {
        idleLines = 0x0U,
        AddressMark = USART_CR1_WAKE,
    };

    enum class parity
    {
        even = 0x0,
        odd = USART_CR1_PS,
        disabled = (int32_t) (-1),
    };

    enum class parityInterrupt
    {
        disabled = 0x0U,
        enabled = USART_CR1_PEIE,
    };

    enum class txEmptyInterrupt
    {
        disabled = 0x0U,
        enabled = USART_CR1_TXEIE,
    };

    enum class txCompleteInterrupt
    {
        disabled = 0x0U,
        enabled = USART_CR1_TCIE,
    };

    enum class rxNotCompleteInterrupt
    {
        disabled = 0x0U,
        enabled = USART_CR1_RXNEIE,
    };

    enum class idleInterrupt
    {
        disabled = 0x0U,
        enabled = (uint32_t)(USART_CR1_IDLEIE),
    };

    enum class stopBits
    {
        one = 0x0U,
        half = (uint32_t)(USART_CR2_STOP_0),
        two = (uint32_t)(USART_CR2_STOP_1),
    };

    enum class tx
    {
        disabled = 0x0,
        enabled = 0x1U,
    };
    
    enum class rx
    {
        disabled = 0x0,
        enabled = 0x1U,
    };

    enum class mode
    {
        blocking = 0x0,
        interrupt = 0x1,
        DMA = 0x2,
    };

    enum class baudRateValues
    {
        _1200 = 1200,
        _2400 = 2400,
        _9600 = 9600,
        _19200 = 19200,
        _38400 = 38400,
        _57600 = 57600,
        _115200 = 115200,
        _230400 = 230400,
        _460800 = 460800,
        _921600 = 921600,
    };

    enum class status
    {

        reset = (int8_t)0x0U,
        ready = (int8_t)0x1U,
        rxBusy = (int8_t)0x2U,
        txBusy = (int8_t)0x4U,
        undefinedError = (int8_t)0x8U,
    };

    struct baud_t
    {
        uint8_t fractionalPart { 0 };
        uint32_t mantisa { 0 };
        uint32_t actualBaudRate { 0 };
        float baudRateErrorPercentage { 0 };
    };
    struct interrupts_t{

        rxNotCompleteInterrupt RXNE { rxNotCompleteInterrupt::disabled };
        txEmptyInterrupt TXE { txEmptyInterrupt::disabled };
        txCompleteInterrupt TXC { txCompleteInterrupt::disabled };
        idleInterrupt idle { idleInterrupt::disabled };
        parityInterrupt parity { parityInterrupt::disabled };
    };

}
#endif /* BD2B9E46_6CC2_425C_90B4_EC09601ED912 */
