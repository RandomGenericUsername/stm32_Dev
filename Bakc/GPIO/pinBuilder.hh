#ifndef _PIN_BUILDER_H_
#define _PIN_BUILDER_H_

#include "GPIOTypes.hh"
#include "stm32f411xe.h"
#include "typeinfo"
#include "macros.hh"

class ioPin;

class pinBuilder
{
private:

    ioPinParams *_settings{nullptr};
    GPIO_TypeDef *_instance{nullptr};
    gpioStatus *_status{nullptr};
    bool *_isParamSet{nullptr};
    uint8_t _pendingParams = 0;

    void setInstance();
    void enablePeripheralClock(bool enable = true);

    void init(const gpioPort &port);
    void init(const GPIO_TypeDef *port);
    void init(const gpioPin &pin);
    void init(const gpioMode &mode);
    void init(const gpioOutputType &oType);
    void init(const gpioOutputSpeed &oSpeed);
    void init(const gpioPUPD &pudp);

    bool builder();
    bool assertPortAndPin(const pinBuilder &pinObj);

    uint8_t getParamIndex(const gpioPort &port) { return portParam; }
    uint8_t getParamIndex(const GPIO_TypeDef *port) { return portParam; }
    uint8_t getParamIndex(const gpioPin &pin) {return pinParam; }
    uint8_t getParamIndex(const gpioMode &mode) {return modeParam; }
    uint8_t getParamIndex(const gpioOutputType &oType) {return oTypeParam; }
    uint8_t getParamIndex(const gpioOutputSpeed &oSpeed) { return oSpeedParam; }
    uint8_t getParamIndex(const gpioPUPD &pudp) { return pupdParam; }

public:

    explicit pinBuilder(const ioPinParams *params, const bool isParamSet[]);
    ~pinBuilder();

    bool readIDR();
    bool writeODR(const pinState &state);

    bool isPinSet(const gpioPort &port, const gpioPin &pin);
    bool isPinSet(const GPIO_TypeDef *port, const gpioPin &pin);

    template<class T>
    bool manager(const T &param)
    {
        if(getParamIndex(param) == portParam)
        {
           init(param);
        } 
         
        if(assertPortAndPin(*this))
        {
            if(_pendingParams == 0)
            {
                if(getParamIndex(param) != pinParam && getParamIndex(param) != portParam) init(param);
            }
            else
            {
                for(uint8_t i = modeParam; i <= stateParam; i++)
                {
                    if(_isParamSet[i])
                    {
                        init(param);
                    }
                }
                _pendingParams = 0;
            }
            *_status = gpioStatus::ready;
            return true;
        }
        else
        {
            if(getParamIndex(param) != portParam && getParamIndex(param) != pinParam) _pendingParams++;
            *_status = gpioStatus::reset;
            return false;
        }
    }


};




#endif




