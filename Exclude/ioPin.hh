#ifndef _IO_PIN_H
#define _IO_PIN_H

#include "macros.hh"
#include "type_traits"
#include "tuple"


typedef bool *(*handler)();
class ioPin
{
    public:

        explicit ioPin();
        ~ioPin();
        template<class ...Args>
        explicit ioPin(const Args &...args);
        explicit ioPin(const ioPin &pin);
        ioPin& operator=(const ioPin &pin);

        bool setPort(const gpioPort &port);
        bool setPin(const gpioPin &pin);
        bool setMode(const gpioMode &mode);
        bool setPUPD(const gpioPUPD &pupd);
        bool setOutputType(const gpioOutputType &outputType);
        bool setOutputSpeed(const gpioOutputSpeed &outputSpeed);
        bool read();
        bool write(const gpioState &state);
        bool toggle();
        bool reset(const bool &forceReset = false);

        static bool isAllocated(const gpioPort &port, const gpioPin &pin);
        bool isReady();

        void failSafeMode(const bool &enable = true);
        void enableDebug(const bool &enable = true);

    protected:

        bool initHandler();
        template<class T>
        bool initHandler(const T &);
        bool portHandler(const gpioPort &);
        bool pinHandler(const gpioPin &);
        bool modeHandler(const gpioMode &, const bool & = true);
        bool readHandler();
        template<class T>
        bool settingsHandler(const T &);
        bool initQueuedSettings();

        static bool assertPort(const ioPin &);
        bool assertPort();
        static bool assertPin(const ioPin &);
        bool assertPin();

        template <typename T>
        paramIndex assertParam(const T &);
        
        GPIO_TypeDef *_instance;
        gpiostatusCode _status;
        uint16_t _queuedSettings;
        bool _failSafeMode;
        bool _debug;

    private:

        gpioPort _port;
        gpioPin _pin;
        gpioMode _mode;
        gpioPUPD _pupd;
        gpioOutputSpeed _outputSpeed;
        gpioOutputType _outputType;
        gpioState _state;

        handler _handler[numberOfPinParams];
        void setDefaultParams();

        void init(const gpioPort &);
        void init(const gpioPin &);
        void init(const gpioMode &);
        void init(const gpioPUPD &);
        void init(const gpioOutputType &);
        void init(const gpioOutputSpeed &);
        void init(const gpioState &);


        static uint16_t allocatedPins[NUMBER_OF_PORTS];

};

template<class ...Args>
ioPin::ioPin(const Args &...args):ioPin()
{
    //function
    //assert and capture the parameters
    (initHandler(args),...);
}

template<class T>
bool ioPin::initHandler(const T &arg)
{
    //capture the number enconding the argument type
    paramIndex argType = assertParam(arg);
    //if the arg does not correspond to any defined parameter, return error
    if(argType == -1)
    {
        return false;
    }
    //set the current arg on the settings array 
    _settings[argType] = static_cast<paramType>(arg);
    //handle posssible errors


    return _handler[argType]();

    if constexpr(std::is_same_v<const gpioPort&, decltype(arg)>)
        return portHandler(arg);
    else if constexpr(std::is_same_v<const gpioPin&, decltype(arg)>)
        return pinHandler(arg);
    else if constexpr(std::is_same_v<const gpioMode&, decltype(arg)>)
        return modeHandler(arg);
    else if constexpr(std::is_same_v<const gpioPUPD&, decltype(arg)> || std::is_same_v<const gpioOutputSpeed&, decltype(arg)> || \
                      std::is_same_v<const gpioOutputType&, decltype(arg)> || std::is_same_v<const gpioState&, decltype(arg)>)
        return settingsHandler(arg);
}



//template<>
//bool ioPin::initHandler<gpioPort>(const gpioPort &param);
//template<>
//bool ioPin::initHandler<gpioPin>(const gpioPin &param);
//template<>
//bool ioPin::initHandler<gpioMode>(const gpioMode &param);
//template<>
//bool ioPin::initHandler<gpioPUPD>(const gpioPUPD &param);
//template<>
//bool ioPin::initHandler<gpioOutputSpeed>(const gpioOutputSpeed &param);
//template<>
//bool ioPin::initHandler<gpioOutputType>(const gpioOutputType &param);
//template<>
//bool ioPin::initHandler<gpioState>(const gpioState &param);
//template<>
//bool ioPin::initHandler<bool>(const bool &param);




#endif


