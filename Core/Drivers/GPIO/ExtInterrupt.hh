#ifndef D180D2E6_4ACF_4C6F_B686_91971F3D2F08
#define D180D2E6_4ACF_4C6F_B686_91971F3D2F08

#include "ioPin.hh"

class ExtInterrupt : public ioPin
{
    public:
        explicit ExtInterrupt();
        template <class ...Args>
        ExtInterrupt(const Args &...args);
        ~ExtInterrupt();

        template <typename RetType = void, typename ...Args>
        RetType callback(RetType(*func)(Args &...args), Args &...args);

        void setMode(const gpioMode &) = delete;    
        void write(const gpioState &) = delete;
        static bool isAllocated(const gpioPin &);
        bool isAllocated();

    private:
        /* data */
        bool initHandler();
        template <typename T>
        bool initHandler(const T &);
        bool setInputMode();
        void init(const gpioExtTrigger &);

        gpioExtTrigger _trigger{gpioExtTrigger::disabled};
        uint8_t _priority{15};
        bool _queuedSetting{false};
        static gpioPort _allocatdInterrupts[NUMBER_OF_PINS];
};


template <class ...Args>
ExtInterrupt::ExtInterrupt(const Args &...args):ExtInterrupt()
{
    (initHandler(args),...);
}

#ifdef FAIL_SAFE_MODE
template<typename T>
bool ExtInterrupt::initHandler(const T & param)
{
    _status = gpiostatusCode::wrongParamPassed;
    if(_failSafeMode) gpioExceptionHandler(_status);
    return false;
}
#endif

template<>
bool ExtInterrupt::initHandler<gpioPort>(const gpioPort &param);
template<>
bool ExtInterrupt::initHandler<gpioPin>(const gpioPin &param);
template<>
bool ExtInterrupt::initHandler<gpioPUPD>(const gpioPUPD &param);
template<>
bool ExtInterrupt::initHandler<bool>(const bool &param);
template<>
bool ExtInterrupt::initHandler<gpioExtTrigger>(const gpioExtTrigger &param);



template <typename RetType, typename ...Args>
RetType ExtInterrupt::callback(RetType(*func)(Args &...args), Args &...args)
{
   return func(args...); 
}

#endif /* D180D2E6_4ACF_4C6F_B686_91971F3D2F08 */
