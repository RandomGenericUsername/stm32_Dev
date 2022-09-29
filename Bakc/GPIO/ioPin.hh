#ifndef _IO_PIN_H
#define _IO_PIN_H

#include "macros.hh"
#include "pinBuilder.hh"


class ioPin
{
    private:

        GPIO_TypeDef *_instance;
        ioPinParams _settings;
        gpioStatus _status;
        IsParamSet _isParamSet;

        uint8_t _numberOfQuededSettings = 0;
        uint8_t _queuedSettings;

        void setInstance();
        void enablePeripheralClock(bool enable = true);

        bool setDefaultParams();
        uint8_t getParamIndex(const gpioPort &port);
        uint8_t getParamIndex(const gpioPin &pin);
        uint8_t getParamIndex(const gpioMode &mode);
        uint8_t getParamIndex(const gpioOutputType &oType);
        uint8_t getParamIndex(const gpioOutputSpeed &oSpeed);
        uint8_t getParamIndex(const gpioPUPD &pudp);
        uint8_t getParamIndex(const pinState &state);

        bool init();
        bool init(const GPIO_TypeDef *);
        bool init(const gpioPort &);
        bool init(const ioPinParams &);

        bool init(const gpioPin &);
        bool init(const gpioMode &);
        bool init(const gpioPUPD &);
        bool init(const gpioOutputType&);
        bool init(const gpioOutputSpeed&);
        bool init(const pinState &);

        template<class T>
        bool manager(const T &);

        template<class T>
        void queueSetting(const T &);

        void initQueuedSettings();

    public:

        explicit ioPin();
        template<class ...Args>
        explicit ioPin(Args ...args);
        ~ioPin();
    
        explicit ioPin(const ioPin &pin);

        ioPin& operator=(const ioPin &pin);

        void setPort(const GPIO_TypeDef *GPIOx);
        void setPort(const gpioPort &port);
        void setPin(const gpioPin &pin);

        void setMode(const gpioMode &mode);
        void setPUPD(const gpioPUPD &pupd);
        void setOutputType(const gpioOutputType &outputType);
        void setOutputSpeed(const gpioOutputSpeed &outputSpeed);

        bool read();
        void write(const pinState &state);

        bool reset(bool forceReset = false);

};


template<class ...Args>
ioPin::ioPin(Args ...args)
{
    init();
    (init(args),...);
}

template<class T>
bool ioPin::manager(const T &)
{

}

template<class T>
void queueSetting(const T &)
{

}

#endif
