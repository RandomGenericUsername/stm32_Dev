#ifndef _IO_PIN_H
#define _IO_PIN_H

#include "macros.hh"
#include "pinBuilder.hh"


class ioPin
{
    private:

        ioPinParams _settings;
        gpioStatus _status;
        uint32_t _isParamSet;

        pinBuilder *_builder;

        bool setDefaultParams();

        bool init();
        bool init(const GPIO_TypeDef *);
        bool init(const gpioPort &);

        bool init(const gpioPin &);
        bool init(const gpioMode &);
        bool init(const gpioPUPD &);
        bool init(const gpioOutputType&);
        bool init(const gpioOutputSpeed&);
        bool init(const pinState &);

    public:

        explicit ioPin();
        template<class ...Args>
        explicit ioPin(Args ...args);
        ~ioPin();
    
        explicit ioPin(const ioPin &pin);

        ioPin& operator=(const ioPin &pin);

        void setPort(GPIO_TypeDef *GPIOx);
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

#endif
