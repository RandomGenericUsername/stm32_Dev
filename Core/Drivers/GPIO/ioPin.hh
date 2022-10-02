#ifndef _IO_PIN_H
#define _IO_PIN_H

#include "macros.hh"


class ioPin
{
    public:

        explicit ioPin();
        ~ioPin();
        template<class ...Args>
        explicit ioPin(Args ...args);
    
        explicit ioPin(const ioPin &pin);

        ioPin& operator=(const ioPin &pin);

        void setPort(const gpioPort &port);
        void setPin(const gpioPin &pin);
        void setMode(const gpioMode &mode);
        void setPUPD(const gpioPUPD &pupd);
        void setOutputType(const gpioOutputType &outputType);
        void setOutputSpeed(const gpioOutputSpeed &outputSpeed);
        bool read();
        void write(const gpioState &state);
        bool reset(bool forceReset = false);

        static bool isPinSet(const gpioPort &port, const gpioPin &pin);
        bool isReady(const ioPin &pinObj);
        bool isReady();

    private:


        template<class T>
        bool manager(const T &);
        bool initQueuedSettings();
        bool checkQueuedSettings(bool(*callback)(const ioPin&), const ioPin&);
        bool isOverWriting();

        void setDefaultParams();
        void init();

        void init(const gpioPort &);
        void init(const gpioPin &);
        void init(const gpioMode &);
        void init(const gpioPUPD &);
        void init(const gpioOutputType &);
        void init(const gpioOutputSpeed &);
        void init(const gpioState &);

        static bool assertPort(const ioPin &);
        bool assertPort();
        static bool assertPin(const ioPin &);
        bool assertPin();
        gpioParameters getParamIndex(const gpioPort &port);
        gpioParameters getParamIndex(const gpioPin &pin);
        gpioParameters getParamIndex(const gpioMode &mode);
        gpioParameters getParamIndex(const gpioOutputType &gpioOutputType);
        gpioParameters getParamIndex(const gpioOutputSpeed &oSpeed);
        gpioParameters getParamIndex(const gpioPUPD &pudp);
        gpioParameters getParamIndex(const gpioState &state);

        GPIO_TypeDef *_instance;
        paramType _settings[numberOfPinParams];
        gpioStatus _status;
        uint16_t _queuedSettings = 0;

        static uint16_t initializedPins[NUMBER_OF_PORTS];
        static gpioExtITAllocated initializedInterrupt[NUMBER_OF_AVAILABLE_EXT_INTERRUPT];

};

template<class ...Args>
ioPin::ioPin(Args ...args)
{
    init();
    if(!(manager(args),...) && isReady()) gpioExceptionHandler();
}


template<class T>
bool ioPin::manager(const T &param)
{
    gpioParameters _paramIndex = getParamIndex(param);
    _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(param);

    switch (static_cast<paramType>(_paramIndex))
    {
        case static_cast<paramType>(gpioParameters::port):

            if(assertPin())
            {
                if( isPinSet( static_cast<gpioPort>(param), static_cast<gpioPin>(_settings[static_cast<paramIndex>(gpioParameters::pin)]) ) )
                {
                    _status = gpioStatus::error;
                    return false;
                }
            }
            init(param);
            return checkQueuedSettings(&assertPin, *this);
            break;

        case static_cast<paramType>(gpioParameters::pin):

            if(assertPort())
            {
                if( isPinSet( static_cast<gpioPort>(_settings[static_cast<paramIndex>(gpioParameters::port)]), static_cast<gpioPin>(param) ) )
                {
                    _status = gpioStatus::error;
                    return false;
                }
            }
            init(param);
            return checkQueuedSettings(&assertPort, *this);
            break;

        default:

            if(isReady())
            {
                if(_queuedSettings == 0)
                { 
                    init(param);
                    return true;
                }
                else return initQueuedSettings();
            }
            else
            {
                //queues the current setting
                _queuedSettings |= static_cast<uint32_t>(0x1 << static_cast<paramType>(_paramIndex));
                return false;
            }
            break;
    }
}


#endif


