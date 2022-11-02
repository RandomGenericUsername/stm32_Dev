#ifndef _AF_PIN_H_ 
#define _AF_PIN_H_

#include "ioPin.hh"

class afPin : public ioPin
{
    public:

        explicit afPin();
        template<class ...Args>
        explicit afPin(const Args &...args);
        ~afPin();

        void setAlternatefunction(const gpioAlternateFunction &);

        void setMode(const gpioMode &) = delete;    
        bool read() = delete;
        void write(const gpioState &) = delete;


    private:


        bool setAlternateFunctionMode();
        bool initHandler();
        template<class T>
        bool initHandler(const T &);
        void init(const gpioAlternateFunction &);
        
        gpioAlternateFunction _alternateFunction{gpioAlternateFunction::_0};
        bool _queuedSetting{false};

};


template<class ...Args>
afPin::afPin(const Args &...args):afPin()
{
    (initHandler(args),...);
}

#ifdef FAIL_SAFE_MODE
template<typename T>
bool afPin::initHandler(const T &param)
{
    _status = gpiostatusCode::wrongParamPassed;
    if(_failSafeMode) gpioExceptionHandler(_status);
    return false;
}
#endif

template<>
bool afPin::initHandler<gpioPort>(const gpioPort &param);
template<>
bool afPin::initHandler<gpioPin>(const gpioPin &param);
template<>
bool afPin::initHandler<gpioPUPD>(const gpioPUPD &param);
template<>
bool afPin::initHandler<gpioOutputSpeed>(const gpioOutputSpeed &param);
template<>
bool afPin::initHandler<gpioOutputType>(const gpioOutputType &param);
template<>
bool afPin::initHandler<gpioAlternateFunction>(const gpioAlternateFunction &param);
template<>
bool afPin::initHandler<bool>(const bool &param);

#endif /* AFD36E78_6321_4D81_8CF5_014B4FBE2340 */
