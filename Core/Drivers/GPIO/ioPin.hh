#ifndef _IO_PIN_H
#define _IO_PIN_H

#include "macros.hh"


class ioPin
{
    public:

        explicit ioPin();
        ~ioPin();
        template<class ...Args>
        explicit ioPin(const Args &...args);
    
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
        bool reset(const bool &forceReset = false);

        static bool isPinSet(const gpioPort &port, const gpioPin &pin);
        bool isReady(const ioPin &pinObj);
        bool isReady();
        void enableExceptions(const bool &enable = true);

    private:

        template<class T>
        bool initHandler(const T &, const bool &);

        template<class T>
        bool manager(const T &, const bool &enableException = false);
        bool portManager(const gpioPort &);
        bool pinManager(const gpioPin &);
        template<class T>
        bool settingsManager(const T &);
        bool initQueuedSettings();

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
        gpiostatusCode _status;
        uint16_t _queuedSettings;
        bool _enableExceptions;

        static uint16_t initializedPins[NUMBER_OF_PORTS];

};

template<class T>
bool ioPin::initHandler(const T &param, const bool &enableExceptions)
{
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(param);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(param);
        return settingsManager(param);

    }
    else if(_status == gpiostatusCode::busy)
    {
        
    }
    else
    {

    }
}

template<class ...Args>
ioPin::ioPin(const Args &...args):ioPin()
{
    //init();
    (manager(args, _enableExceptions),...);
}

template<class T>
bool ioPin::settingsManager(const T &param)
{
    bool retVal = false;
    if(isReady())
    {
        init(param);
        _status = gpiostatusCode::ready;
        retVal = true;
    }
    else
    {
        //queues the current setting
        gpioParameters paramType = getParamIndex(param);
        _queuedSettings |= static_cast<uint16_t>(0x1 << static_cast<paramIndex>(paramType));
        _status = gpiostatusCode::reset;
        retVal = false;
    }
    return retVal;
}

template<class T>
bool ioPin::manager(const T &param, const bool &enableExceptions)
{   
    bool retVal = false;
    if(_status == gpiostatusCode::ready || _status == gpiostatusCode::reset)
    {
        gpioParameters _paramIndex = getParamIndex(param);
        _settings[static_cast<paramIndex>(_paramIndex)] = static_cast<paramType>(param);

        switch (static_cast<paramType>(_paramIndex))
        {
            case static_cast<paramType>(gpioParameters::port):
                retVal = portManager(static_cast<gpioPort>(param));
                break;

            case static_cast<paramType>(gpioParameters::pin):
                retVal = pinManager(static_cast<gpioPin>(param));
                break;

            default:
                retVal = settingsManager(param);
                break;
        }
    }
    else if(_status == gpiostatusCode::busy)
    {
        
    }
    else
    {

    }
    return retVal;

}


#endif


