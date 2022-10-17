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
        bool reset(const bool &forceReset = false);

        static bool isAllocated(const gpioPort &port, const gpioPin &pin);
        bool isReady();
        void failSafeMode(const bool &enable = true);
        void enableDebug(const bool &enable = true);

    protected:

        template<class T>
        bool initHandler(const T &);
        bool portManager(const gpioPort &);
        bool pinManager(const gpioPin &);
        template<class T>
        bool settingsManager(const T &);
        bool initQueuedSettings();
        void init();

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

        static uint16_t allocatedPins[NUMBER_OF_PORTS];

};

template<class ...Args>
ioPin::ioPin(const Args &...args):ioPin()
{
    (initHandler(args),...);
}


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


