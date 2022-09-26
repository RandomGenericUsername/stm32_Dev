#ifndef _IO_PIN_H
#define _IO_PIN_H

#include "pinBuilder.hh"
#include "macros.hh"



class ioPin
{
    private:


        ioPinParams *_settings;
        pinBuilder *_builder;
        gpioStatus _status{gpioStatus::reset};
        bool _isParamSet[numberOfPinParams]{false};

        void setParam();
        void setParam(const GPIO_TypeDef *GPIOx);
        void setParam(const gpioPort &GPIOx);
        void setParam(const gpioPin &pin);
        void setParam(const gpioMode &mode);
        void setParam(const gpioPUPD &pupd);
        void setParam(const gpioOutputType &outputType);
        void setParam(const gpioOutputSpeed &outputSpeed);
        void setParam(const gpioState &state);


    public:

        explicit ioPin()
        { 
            _settings = new ioPinParams;
            setParam();
            _builder = new pinBuilder(_settings, _isParamSet);

        }


        ~ioPin()
        {
            delete _builder;
            delete _settings;
        }
    
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
        void write(const gpioState &state);

        bool reset(bool forceReset = false);

};

#endif