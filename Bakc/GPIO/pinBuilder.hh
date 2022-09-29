#ifndef _PIN_BUILDER_H_
#define _PIN_BUILDER_H_

#include "GPIOTypes.hh"
#include "stm32f411xe.h"
#include "macros.hh"

class ioPin;

class pinBuilder
{

protected:


private:

    ioPinParams *_settings = nullptr;
    gpioStatus *_status = nullptr;
    IsParamSet *_isParamSet = nullptr;

    GPIO_TypeDef *_instance{nullptr};

    static const uint8_t _maxPendingParams = 5;
    uint8_t _numberOfPendingParams = 0;
    uint8_t _pendingParamsValues[_maxPendingParams]{0} ;

    void setInstance();
    void enablePeripheralClock(bool enable = true);

    void init(const gpioPort &port);
    void init(const gpioPin &pin);
    void init(const gpioMode &mode);
    void init(const gpioOutputType &oType);
    void init(const gpioOutputSpeed &oSpeed);
    void init(const gpioPUPD &pudp);
    void init(const pinState &state);

    uint8_t getParamIndex(const gpioPort &port);
    uint8_t getParamIndex(const gpioPin &pin);
    uint8_t getParamIndex(const gpioMode &mode);
    uint8_t getParamIndex(const gpioOutputType &oType);
    uint8_t getParamIndex(const gpioOutputSpeed &oSpeed);
    uint8_t getParamIndex(const gpioPUPD &pudp);
    uint8_t getParamIndex(const pinState &state);
    
    bool builder();

    template<class T>
    void queueSetting(const T &);

    void initQueuedSettings();


protected:


public:


    explicit pinBuilder();
    explicit pinBuilder(const ioPinParams *params, const IsParamSet *isParamSet, const gpioStatus *status);
    ~pinBuilder();

    template<class T>
    bool manager(const T &param);
    
    bool readIDR();
    bool writeODR(const pinState &state);

    bool assertPortAndPin(const pinBuilder &pinObj);
    bool assertPortAndPin();
    bool isPinSet(const gpioPort &port, const gpioPin &pin);
    bool isPinSet(const GPIO_TypeDef *port, const gpioPin &pin);
    bool setPtr(const ioPinParams *);
    bool setPtr(const gpioStatus *);
    bool setPtr(const IsParamSet *isParamSet);


};




template<class T>
void pinBuilder::queueSetting(const T &param)
{

    uint8_t paramType = getParamIndex(param);
    if(paramType == modeParam)
    {
        _pendingParamsValues[modeParam - 2] = static_cast<uint8_t>(param);
    }
    else if(paramType == pupdParam)
    {
        _pendingParamsValues[pupdParam -2] = static_cast<uint8_t>(param);
    }
    else if(paramType == oTypeParam)
    {
        _pendingParamsValues[oTypeParam -2] = static_cast<uint8_t>(param);
    }
    else if(paramType == oSpeedParam)
    {
        _pendingParamsValues[oSpeedParam -2] = static_cast<uint8_t>(param);
    }
    else if(paramType == stateParam)
    {
        _pendingParamsValues[stateParam - 2] = static_cast<uint8_t>(param);
    }
    _numberOfPendingParams++;
}



template<class T>
bool pinBuilder::manager(const T &param)
{
    bool retVal = false;
    uint8_t paramType = getParamIndex(param);

    switch (paramType)
    {
        case portParam:
            init(param);
            if(assertPortAndPin(*this) && _numberOfPendingParams != 0)
            {
                initQueuedSettings();
            }
            retVal = true;
            break;

        case pinParam:

            //future implementation 
            retVal = true;
            break;

        default:

            if(assertPortAndPin(*this))
            {
                if(_numberOfPendingParams == 0) init(param);
                else initQueuedSettings();
                retVal = true;
            }
            else
            {
                queueSetting(param);
                retVal = false;
            }

            break;
    }
    return retVal;
}



#endif




