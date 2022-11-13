#ifndef E85EB836_EDFF_4F9C_B124_4919496DAE51
#define E85EB836_EDFF_4F9C_B124_4919496DAE51

#include "GPIOTypes.hh"
#include "type_traits"
#include "STM32F411RE_SYSTEM.h"
#define NDEBUG
#include "macros.hh"


class inputOutputPinHandler
{
    public:
        explicit inputOutputPinHandler(const gpioPort *port, const gpioPin *pin, const gpioMode *mode, const gpioPUPD *pupd,\
            const gpioOutputSpeed *outputSpeed, const gpioOutputType *outputType, const gpioState *state,\
            const gpiostatusCode *status, const bool *failSafe, const bool *debug);
        ~inputOutputPinHandler();

        template<typename T>
        void initHandler(const T &param);
        template <typename T>
        void errorHandler(const T &param, inputOutputPinHandler *obj, bool (*callback)(const T &param, inputOutputPinHandler *obj));
        template<typename T>
        static bool setParam(const T &param, inputOutputPinHandler *obj);

    protected:



    private:
        void init();
        template <typename T>
        constexpr static bool assertParam(const T &args);
        gpioPort *_port;
        gpioPin *_pin;
        gpioMode *_mode;
        gpioPUPD *_pupd;
        gpioOutputSpeed *_outputSpeed;
        gpioOutputType *_outputType;
        gpioState *_pinState;
        gpiostatusCode *_status;
        bool *_hardException;
        bool *_debug;

};

template<typename T>
void inputOutputPinHandler::initHandler(const T &param)
{
    //if wrong param is parsed, then do static assert and not compile
    //#define NDEBUG to disable this
    m_assert(ASSERT_PIN_PARAMS(param), "Not allowed arg passed to initHandler function");

    //if NDEBUG is enabled, then is is needed to parse the right params
    try
    {
        if (!ASSERT_PIN_PARAMS(param))
            throw(gpiostatusCode::wrongParamPassed, *this);
    }
    catch(const gpiostatusCode &code)
    {
        *_status = code;
        
    }
    

    if(*_status == gpiostatusCode::ready || *_status == gpiostatusCode::reset)
    {

    }
    else if(*_status == gpiostatusCode::busy)
    {

    }
    else
    {

    }
}
template<typename T>
bool inputOutputPinHandler::setParam(const T &param, inputOutputPinHandler *obj)
{
    if constexpr(std::is_same_v<const gpioPort &, decltype(param)>)
    {
        *obj->_port = param;
        return true;
    }
    else if constexpr(std::is_same_v<const gpioPin &, decltype(param)>)
    {
        *obj->_pin = param;
        return true;
    }
    else if constexpr(std::is_same_v<const gpioMode &, decltype(param)>)
    {
        *obj->_mode = param;
        return true;
    }
    else if constexpr(std::is_same_v<const gpioPUPD &, decltype(param)>)
    {
        *obj->_pupd = param;
        return true;
    }
    else if constexpr(std::is_same_v<const gpioOutputSpeed &, decltype(param)>)
    {
        *obj->_outputSpeed = param;
        return true;
    }
    else if constexpr(std::is_same_v<const gpioOutputType &, decltype(param)>)
    {
        *obj->_outputType = param;
        return true;
    }
    else if constexpr(std::is_same_v<const gpioState &, decltype(param)>)
    {
        *obj->_pinState = param;
        return true;
    }
    else if constexpr(std::is_same_v<const gpioFailSafe &, decltype(param)>)
    {
        if(param == gpioFailSafe::disable)
            *obj->_hardException = false;
        else
            *obj->_hardException = true;  
        return true;
    }
    else if constexpr(std::is_same_v<const gpioDebug &, decltype(param)>)
    {
        if(param == gpioDebug::disable)
            *obj->_debug = false;
        else
            *obj->_debug = true;  
        return true;
    }
    return false;
}



template<typename T>
void inputOutputPinHandler::errorHandler(const T &param, inputOutputPinHandler *obj, bool (*callback)(const T &param, inputOutputPinHandler *obj))
{
    try
    {
        if(obj == nullptr || callback == nullptr)
            throw("gpioErroHandler passed null args");
        if(!callback(param, obj))
            throw(obj);
    }
    catch(const char *msg)
    {
        systemStatus = const_cast<char*>(msg);
        while(1);
    }
    catch(inputOutputPinHandler *obj)
    {
        //gpioExceptionHandler(*obj->_status);
    }
    catch(...)
    {
        while(1);
    }
}




template<typename T>
constexpr bool inputOutputPinHandler::assertParam(const T &arg)
{
    if ( std::is_same_v<const gpioPort&, decltype(arg)>         || \
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

#endif /* E85EB836_EDFF_4F9C_B124_4919496DAE51 */
