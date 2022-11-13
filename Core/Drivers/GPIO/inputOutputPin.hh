#ifndef D049C379_08EF_4419_A5EA_DD6F89F46E89
#define D049C379_08EF_4419_A5EA_DD6F89F46E89

#include "inputOutputPinHandler.hh"

class inputOutputPin
{
    public:
        explicit inputOutputPin();
        template <typename ...Args>
        explicit inputOutputPin(const Args &...args);
        ~inputOutputPin();

        bool setPort(const gpioPort &port, const bool &handleError = false);
        bool setPin(const gpioPin &pin, const bool &handleError = false);
        bool setMode(const gpioMode &mode, const bool &handleError = false);
        bool setInputMode(const bool &handleError = false);
        bool setOutputMode(const bool &handleError = false);
        bool setPUPD(const gpioPUPD &pupd, const bool &handleError = false);
        bool setOutputType(const gpioOutputType &outputType, const bool &handleError = false);
        bool setOutputSpeed(const gpioOutputSpeed &outputSpeed, const bool &handleError = false);
        bool read(const bool &handleError = false);
        bool write(const gpioState &state, const bool &handleError = false);
        bool toggle(const bool &handleError = false);
        bool reset(const bool &forceReset = false, const bool &handleError = false);
        bool isReady();

        static bool isAllocated(const gpioPort &port, const gpioPin &pin);

        void failSafeMode(const bool &enable = true);
        void enableDebug(const bool &enable = true);

    protected:

    private:

        gpioPort _port{gpioPort::null};
        gpioPin _pin{gpioPin::null};
        gpioMode _mode{gpioMode::input};
        gpioPUPD _pupd{gpioPUPD::disabled};
        gpioOutputSpeed _outputSpeed{gpioOutputSpeed::low};
        gpioOutputType _outputType{gpioOutputType::pushPull};
        gpioState _pinState{gpioState::low};
        gpiostatusCode _status{gpiostatusCode::reset};
        bool _hardException{false};
        bool _debug{false};
        inputOutputPinHandler *_handler{nullptr};
        void init();

};

template <typename ...Args>
inputOutputPin::inputOutputPin(const Args &...args):inputOutputPin()
{
    //(_handler->errorHandler(args, _handler, &_handler->setParam), ...);
    (_handler->initHandler(args), ...);
}


#endif /* D049C379_08EF_4419_A5EA_DD6F89F46E89 */
