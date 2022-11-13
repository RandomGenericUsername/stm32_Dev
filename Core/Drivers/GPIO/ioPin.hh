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
        bool read(const bool &extrict = false);
        bool write(const gpioState &state);
        bool toggle();
        bool reset(const bool &forceReset = false);
        bool isReady();

        static bool isAllocated(const gpioPort &port, const gpioPin &pin);

        void failSafeMode(const bool &enable = true);
        void enableDebug(const bool &enable = true);

    protected:

        bool initHandler();
        template<class T>
        bool initHandler(const T &);
        bool modeHandler(const gpioMode &, const bool &checkMode = false);
        template<class T>
        bool settingsHandler(const T &);
        bool initQueuedSettings();

        bool readIO(const bool &extrict);
        bool writeIO(const gpioState &state);

        static bool assertPort(const ioPin &);
        bool assertPort();
        static bool assertPin(const ioPin &);
        bool assertPin();

        

    private:

        GPIO_TypeDef *_instance;
        gpiostatusCode _status;
        uint16_t _queuedSettings;
        bool _failSafeMode;
        bool _debug;
        gpioPort _port;
        gpioPin _pin;
        gpioMode _mode;
        gpioPUPD _pupd;
        gpioOutputSpeed _outputSpeed;
        gpioOutputType _outputType;
        gpioState _state;

        void defaultSettings();
        template <typename T>
        constexpr static bool assertParam(const T &);
        template <typename T>
        static constexpr paramIndex getParamIndex(const T &);
        template <typename T>
        void setParam(const T &param);
        template <typename T>
        bool initParam(const T &param);
        bool avoidReAllocatingPort(const gpioPort &port);
        bool avoidReAllocatingPin(const gpioPin &pin);


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
    if constexpr(
    std::is_same_v<const gpioPort&, decltype(arg)>         || \
    std::is_same_v<const gpioPin&, decltype(arg)>          || \
    std::is_same_v<const gpioMode&, decltype(arg)>         || \
    std::is_same_v<const gpioPUPD&, decltype(arg)>         || \
    std::is_same_v<const gpioOutputSpeed&, decltype(arg)>  || \
    std::is_same_v<const gpioOutputType&, decltype(arg)>   || \
    std::is_same_v<const gpioState&, decltype(arg)>        || \
    std::is_same_v<const gpioFailSafe&, decltype(arg)>     || \
    std::is_same_v<const gpioDebug&, decltype(arg)> )
    {
        //if pin is in other state than reset or ready, return an error and handle it
        if(_status != gpiostatusCode::reset && _status != gpiostatusCode::ready)
        {
            //handles all other states
            //return errorHandler
            return false;
        }
        //this executes if state is ready or reset
        return initParam(arg);


    }
    //code reaches here if not allowed param is passed to this function
    //then return false and set error status
    _status = gpiostatusCode::wrongParamPassed;
    return false;
}

template <typename T>
bool ioPin::initParam(const T &param)
{
    constexpr bool isPort = std::is_same_v<const gpioPort&, decltype(param)>;
    constexpr bool isPin = std::is_same_v<const gpioPin&, decltype(param)>;
    
    
    if constexpr( isPort || isPin )
    {
        if constexpr(isPort)
            if(!avoidReAllocatingPort(param))
                return false;
        
        if constexpr(isPin)
            if(!avoidReAllocatingPin(param))
                return false;

        setParam(param);
        if constexpr(isPort)
            init(param);
        if(isReady())
        {
            allocatedPins[static_cast<paramType>(_port)] |= 0x1 << static_cast<paramType>(_pin);
            if(_queuedSettings != 0)
                return initQueuedSettings();
        }
    }
    else
    {
        setParam(param);
        settingsHandler(param);
    }

    return true;
}

template <typename T>
bool ioPin::settingsHandler(const T &param)
{
    constexpr bool isMode = std::is_same_v<const gpioMode&, decltype(param)>;
    if(isReady())
    {
        if constexpr(isMode)
            modeHandler(param, true);
        else
            init(param);
    }
    else
    {
        paramIndex ParamIndex = getParamIndex(param);
        _queuedSettings |= (0x1 << ParamIndex);
    }
    return true;
}

template <typename T>
void ioPin::setParam(const T &param)
{
    if constexpr(std::is_same_v<const gpioPort &, decltype(param)>)
        _port = param;
    else if constexpr(std::is_same_v<const gpioPin &, decltype(param)>)
        _pin = param;
    else if constexpr(std::is_same_v<const gpioMode &, decltype(param)>)
        _mode = param;
    else if constexpr(std::is_same_v<const gpioPUPD &, decltype(param)>)
        _pupd = param;
    else if constexpr(std::is_same_v<const gpioOutputSpeed &, decltype(param)>)
        _outputSpeed = param;
    else if constexpr(std::is_same_v<const gpioOutputType &, decltype(param)>)
        _outputType = param;
    else if constexpr(std::is_same_v<const gpioState &, decltype(param)>)
        _state = param;
    else if constexpr(std::is_same_v<const gpioFailSafe &, decltype(param)>)
        _failSafeMode = param;  
    else if constexpr(std::is_same_v<const gpioDebug &, decltype(param)>)
        _debug = param;
}

template <typename T>
constexpr paramIndex ioPin::getParamIndex(const T &param)
{
    if constexpr(std::is_same_v<const gpioPort &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::port);
    else if constexpr(std::is_same_v<const gpioPin &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::pin);
    else if constexpr(std::is_same_v<const gpioMode &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::mode);
    else if constexpr(std::is_same_v<const gpioPUPD &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::pupd);
    else if constexpr(std::is_same_v<const gpioOutputSpeed &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::oSpeed);
    else if constexpr(std::is_same_v<const gpioOutputType &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::oType);
    else if constexpr(std::is_same_v<const gpioState &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::state);
    else if constexpr(std::is_same_v<const gpioFailSafe &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::failSafe);
    else if constexpr(std::is_same_v<const gpioDebug &, decltype(param)>)
        return static_cast<paramIndex>(gpioParameters::debug );
    else
        return 0xFFFFFFFF;
}

template<typename T>
constexpr bool ioPin::assertParam(const T &arg)
{
    if constexpr( std::is_same_v<const gpioPort&, decltype(arg)>         || \
    std::is_same_v<const gpioPin&, decltype(arg)>          || \
    std::is_same_v<const gpioMode&, decltype(arg)>         || \
    std::is_same_v<const gpioPUPD&, decltype(arg)>         || \
    std::is_same_v<const gpioOutputSpeed&, decltype(arg)>  || \
    std::is_same_v<const gpioOutputType&, decltype(arg)>   || \
    std::is_same_v<const gpioState&, decltype(arg)>        || \
    std::is_same_v<const gpioFailSafe&, decltype(arg)>     || \
    std::is_same_v<const gpioDebug&, decltype(arg)>   )
        return true;
    else
        return false;
}








#endif


