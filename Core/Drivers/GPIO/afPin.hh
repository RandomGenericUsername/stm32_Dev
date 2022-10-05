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

        template<class T>
        bool manager(const T &, const bool &exceptions = false);
        bool afManager(const gpioAlternateFunction &);
        void init();
        void init(const gpioAlternateFunction &);

        gpioAlternateFunction _alternateFunction{gpioAlternateFunction::_0};

};

template<class T>
bool afPin::manager(const T &param, const bool &exceptions)
{
    gpioParameters whichParam = ioPin::getParamIndex(param);
    
    if(whichParam == gpioParameters::mode) 
    {
        ioPin::_status = gpiostatusCode::wrongParamPassed;
        if(ioPin::_enableExceptions) gpioExceptionHandler(_status);
        return false;
    }
    else if(whichParam == gpioParameters::alternateFunction)
    {

        //_alternateFunction = af;
    }
    else
    {
        ioPin::manager(param, ioPin::_enableExceptions);
    }
}

template<class ...Args>
afPin::afPin(const Args &...args)
{
    ioPin::init();
    (manager(args, _enableExceptions),...);
}

#endif /* AFD36E78_6321_4D81_8CF5_014B4FBE2340 */
