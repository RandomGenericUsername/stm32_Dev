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

        bool setPort(const gpioPort &port);
        bool setPin(const gpioPin &pin);
        bool setMode(const gpioMode &mode);
        bool setPUPD(const gpioPUPD &pupd);
        bool setOutputType(const gpioOutputType &outputType);
        bool setOutputSpeed(const gpioOutputSpeed &outputSpeed);
        bool read();
        bool write(const gpioState &state);
        bool toggle();
        bool reset(const bool &forceReset = false);

        static bool isAllocated(const gpioPort &port, const gpioPin &pin);
        bool isReady();
        void failSafeMode(const bool &enable = true);
        void enableDebug(const bool &enable = true);

    protected:

        bool initHandler();
        template<class T>
        bool initHandler(const T &);
        bool portHandler(const gpioPort &);
        bool pinHandler(const gpioPin &);
        bool modeHandler(const gpioMode &, const bool & = true);
        bool readHandler();
        template<class T>
        bool settingsHandler(const T &);
        bool initQueuedSettings();

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
        bool _failSafeMode;
        bool _debug;

    private:

        void setDefaultParams();

        void init(const gpioPort &);
        void init(const gpioPin &);
        void init(const gpioMode &);
        void init(const gpioPUPD &);
        void init(const gpioOutputType &);
        void init(const gpioOutputSpeed &);
        void init(const gpioState &);


        static uint16_t allocatedPins[NUMBER_OF_PORTS];

};

template<class ...Args>
ioPin::ioPin(const Args &...args):ioPin()
{
    (initHandler(args),...);
}
#ifdef FAIL_SAFE_MODE
template<class T>
bool ioPin::initHandler(const T &)
{
    //not supposed to get here
    _status = gpiostatusCode::wrongParamPassed;
    if(_failSafeMode) gpioExceptionHandler(_status);
    return false;
}
#endif

template<>
bool ioPin::initHandler<gpioPort>(const gpioPort &param);
template<>
bool ioPin::initHandler<gpioPin>(const gpioPin &param);
template<>
bool ioPin::initHandler<gpioMode>(const gpioMode &param);
template<>
bool ioPin::initHandler<gpioPUPD>(const gpioPUPD &param);
template<>
bool ioPin::initHandler<gpioOutputSpeed>(const gpioOutputSpeed &param);
template<>
bool ioPin::initHandler<gpioOutputType>(const gpioOutputType &param);
template<>
bool ioPin::initHandler<gpioState>(const gpioState &param);
template<>
bool ioPin::initHandler<bool>(const bool &param);




#endif


