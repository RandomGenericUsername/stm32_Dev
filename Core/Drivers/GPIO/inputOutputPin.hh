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

        bool setPort(const gpioPort &port);
        bool setPin(const gpioPin &pin);
        bool setMode(const gpioMode &mode);
        bool setInputMode();
        bool setOutputMode();
        bool setPUPD(const gpioPUPD &pupd);
        bool setOutputType(const gpioOutputType &outputType);
        bool setOutputSpeed(const gpioOutputSpeed &outputSpeed);
        bool read();
        bool write(const gpioState &state);
        bool toggle();
        bool reset(const bool &forceReset = false);
        bool isReady();
        static bool isAllocated(const gpioPort &port, const gpioPin &pin);

        void hardExceptionMode(const bool &enable = true);
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

};

template <typename ...Args>
inputOutputPin::inputOutputPin(const Args &...args):inputOutputPin()
{
    //(_handler->initHandler(args, _handler, &_handler->setParam), ...);
    (_handler->initHandler(args), ...);

}


#endif /* D049C379_08EF_4419_A5EA_DD6F89F46E89 */
