#ifndef E85AA768_00D4_4E5B_9CA2_51ABE234B873
#define E85AA768_00D4_4E5B_9CA2_51ABE234B873

#include "afPin.hh"
#include "USART_Types.hh"
#include "type_traits"


using namespace usartTypes;
class UART
{

    public:

        UART();
        ~UART();
        template<typename ...Args>
        UART(const Args &...args);

        char *rxCharBuffer;
        char *txCharBuffer;

    private:

        bool initHandler();
        template<typename T>
        bool initHandler(const T &);

        USART_TypeDef *_instance {nullptr};
        USART_TypeDef _resetValues {0};

        
        rx _rx { rx::disabled};
        tx _tx { tx::disabled};
        baudRateValues _baudRate { baudRateValues::_9600 };
        wordLength _wordLength { wordLength::_8_DataBits};
        parity _paritiy { parity::disabled };
        stopBits _stopBits { stopBits::one };
        uint8_t _interruptPriority { 15 };
        double _internalClockFrequency { 16E6 };
        oversamplingMode _oversampling { oversamplingMode::By16 };
        uint32_t _rxBufferLength { 128 };
        uint32_t _txBufferLength { 128 };
        char _terminationCharacter { '\n' };
        mode _mode { mode::blocking };
        interrupts_t _interrupts;
        baud_t _baudValues;

        afPin *_txPin {nullptr};
        afPin *_rxPin {nullptr};

        status _status {status::reset};
        bool _rxComplete {false};
        bool _txComplete {false};
        uint32_t _rxCount {0};
        uint32_t _txCount {0};
};


template<typename ...Args>
UART::UART(const Args &...args)
{
    (initHandler(args),...);
}

template<typename T>
bool UART::initHandler(const T &param)
{
    if(std::is_same_v<param, USART_TypeDef *const&>)
    {

    }
}

template<> bool UART::initHandler<USART_TypeDef*>(USART_TypeDef *const&);
template<> bool UART::initHandler<rx>(const rx &);
template<> bool UART::initHandler<tx>(const tx &);
template<> bool UART::initHandler<baudRateValues>(const baudRateValues &);
template<> bool UART::initHandler<wordLength>(const wordLength &);
template<> bool UART::initHandler<parity>(const parity &);



#endif /* E85AA768_00D4_4E5B_9CA2_51ABE234B873 */
