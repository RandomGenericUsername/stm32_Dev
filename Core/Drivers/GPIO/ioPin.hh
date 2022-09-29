#ifndef _IO_PIN_H
#define _IO_PIN_H

#include "macros.hh"


class ioPin
{
    private:

        GPIO_TypeDef *_instance;
        settings_t _settings[numberOfBasicPinParams];
        gpioStatus::gpioStatus _status;
        isParamSet_t _isParamSet;

        uint8_t _numberOfQuededSettings = 0;
        uint8_t _queuedSettings;

        void setInstance();
        void enablePeripheralClock(bool enable = true);

        bool setDefaultParams();
        uint8_t getParamIndex(const gpioPort::gpioPort &port);
        uint8_t getParamIndex(const gpioPin::gpioPin &pin);
        uint8_t getParamIndex(const gpioMode::gpioMode &mode);
        uint8_t getParamIndex(const gpioOutputType::gpioOutputType &gpioOutputType);
        uint8_t getParamIndex(const gpioOutputSpeed::gpioOutputSpeed &oSpeed);
        uint8_t getParamIndex(const gpioPUPD::gpioPUPD &pudp);
        uint8_t getParamIndex(const gpioState::gpioState &state);

        bool init();
        bool init(const GPIO_TypeDef *);
        bool init(const gpioPort::gpioPort &);
        bool init(const settings_t []);

        bool init(const gpioPin::gpioPin &);
        bool init(const gpioMode::gpioMode &);
        bool init(const gpioPUPD::gpioPUPD &);
        bool init(const gpioOutputType::gpioOutputType &);
        bool init(const gpioOutputSpeed::gpioOutputSpeed &);
        bool init(const gpioState::gpioState &);

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
        void setPort(const gpioPort::gpioPort &port);
        void setPin(const gpioPin::gpioPin &pin);

        void setMode(const gpioMode::gpioMode &mode);
        void setPUPD(const gpioPUPD::gpioPUPD &pupd);
        void setOutputType(const gpioOutputType::gpioOutputType &outputType);
        void setOutputSpeed(const gpioOutputSpeed::gpioOutputSpeed &outputSpeed);

        bool read();
        void write(const gpioState::gpioState &state);

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


