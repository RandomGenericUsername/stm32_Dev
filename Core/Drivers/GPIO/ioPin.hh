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
        bool _enableExceptions;

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

        static uint16_t initializedPins[NUMBER_OF_PORTS];

};

template<class ...Args>
ioPin::ioPin(const Args &...args):ioPin()
{
    (initHandler(args),...);
}

//template<class T>
//bool ioPin::initHandler(const T &param)
//{
//    gpioExceptionHandler(gpiostatusCode::undefinedError);
//}




#endif


