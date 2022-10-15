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

        gpioParameters getParamIndex(const gpioAlternateFunction &af);

        template<class T>
        bool initHandler(const T &, const bool &exceptions = true);
        void init();
        void init(const gpioAlternateFunction &);
        
        gpioAlternateFunction _alternateFunction;

};


template<class ...Args>
afPin::afPin(const Args &...args):afPin()
{
    (initHandler(args, _enableExceptions),...);
}

#endif /* AFD36E78_6321_4D81_8CF5_014B4FBE2340 */
