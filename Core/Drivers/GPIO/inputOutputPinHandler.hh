
#ifndef E85EB836_EDFF_4F9C_B124_4919496DAE51
#define E85EB836_EDFF_4F9C_B124_4919496DAE51

#include "GPIO_Types.hh"
#include "type_traits"
#include "STM32F411RE_SYSTEM.h"
#define NDEBUG
#include "gpioMacros.hh"
#include "Macros.hh"

class inputOutputPinHandler
{
public:
    explicit inputOutputPinHandler(const gpioPort *port, const gpioPin *pin, const gpioMode *mode, const gpioPUPD *pupd,
                                   const gpioOutputSpeed *outputSpeed, const gpioOutputType *outputType, const gpioState *state,
                                   const gpiostatusCode *status, const bool *failSafe, const bool *debug);
    ~inputOutputPinHandler();

    template <typename T>
    static bool initHandler(const T &param, inputOutputPinHandler *obj);
    template <typename T>
    bool initHandler(const T &param);
    template <typename T>
    static bool errorHandler(const gpiostatusCode &code, const T &param, inputOutputPinHandler *obj);
    template <typename T>
    static bool setParam(const T &param, inputOutputPinHandler *obj);
    bool isReady();
    bool isAllocated();
    static bool isAllocated(const gpioPort &port, const gpioPin &pin);

protected:
private:
    static bool portSettings(const gpioPort &port, inputOutputPinHandler *obj);
    static bool pinSettings(const gpioPin &pin, inputOutputPinHandler *obj);
    static bool modeSettings(const gpioMode &mode, inputOutputPinHandler *obj, const bool &checkMode = false);
    static bool initQueuedSettings(inputOutputPinHandler *obj);
    static bool isReady(const inputOutputPinHandler *obj);
    static bool isPortSet(const inputOutputPinHandler &obj);
    static bool isPinSet(const inputOutputPinHandler &obj);
    static bool isReallocating(const gpioPort &port, const inputOutputPinHandler *obj);
    static bool isReallocating(const gpioPin &pin, const inputOutputPinHandler *obj);
    static gpioPort getGPIOIndex(const GPIO_TypeDef *);
    static GPIO_TypeDef *getGPIO(const gpioPort &);

    template <typename T>
    static bool generalSettings(const T &param, inputOutputPinHandler *obj);
    template <typename T>
    static bool settingsHandler(const T &param, inputOutputPinHandler *obj);
    template <typename T>
    static void init(const T &param, inputOutputPinHandler *obj);

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
    uint8_t _queuedSettings;
    GPIO_TypeDef *_instance;
    static uint16_t allocatedPins[NUMBER_OF_PORTS];
};

template <typename T>
bool inputOutputPinHandler::initHandler(const T &param, inputOutputPinHandler *obj)
{
    // if wrong param is parsed, then do static assert and not compile
    // #define NDEBUG to disable this
    m_assert(ASSERT_PIN_PARAMS(param), "Not allowed arg passed to initHandler function");

    if constexpr (ASSERT_PIN_PARAMS(param))
    {
        if (*obj->_status != gpiostatusCode::ready && *obj->_status != gpiostatusCode::reset)
        {
            if (*obj->_hardException == true)
                while (1)
                    ;
            return false;
        }
        return settingsHandler(param, obj);
    }
    *obj->_status = gpiostatusCode::wrongParamPassed;
    if (*obj->_hardException == true)
        while (1)
            ;
    return false;
}


template <typename T>
bool inputOutputPinHandler::initHandler(const T &param)
{
    return inputOutputPinHandler::initHandler(param, this);
}

template <typename T>
bool inputOutputPinHandler::settingsHandler(const T &param, inputOutputPinHandler *obj)
{
    if constexpr (std::is_same_v<const gpioHardException &, decltype(param)>)
    {
        if (param == gpioHardException::enable)
            *obj->_hardException = true;
        else
            *obj->_hardException = false;
        return true;
    }
    else if constexpr (std::is_same_v<const gpioDebug &, decltype(param)>)
    {
        if (param == gpioDebug::enable)
            *obj->_debug = true;
        else
            *obj->_debug = false;
        return true;
    }
    else if constexpr (std::is_same_v<const gpioPort &, decltype(param)>)
    {
        return portSettings(param, obj);
    }
    else if constexpr (std::is_same_v<const gpioPin &, decltype(param)>)
    {
        return pinSettings(param, obj);
    }
    else if constexpr (std::is_same_v<const gpioMode &, decltype(param)>)
    {
        return modeSettings(param, obj, true);
    }
    else
    {
        return generalSettings(param, obj);
    }
}

template <typename T>
bool inputOutputPinHandler::generalSettings(const T &param, inputOutputPinHandler *obj)
{
    if(!setParam(param, obj))
        return false;

    if (isReady(obj))
        init(param, obj);
    else
    {
        if constexpr (std::is_same_v<const gpioMode &, decltype(param)>)
            obj->_queuedSettings |= (0x1 << 0);
        else if constexpr (std::is_same_v<const gpioPUPD &, decltype(param)>)
            obj->_queuedSettings |= (0x1 << 1);
        else if constexpr (std::is_same_v<const gpioOutputType &, decltype(param)>)
            obj->_queuedSettings |= (0x1 << 2);
        else if constexpr (std::is_same_v<const gpioOutputSpeed &, decltype(param)>)
            obj->_queuedSettings |= (0x1 << 3);
        else if constexpr (std::is_same_v<const gpioState &, decltype(param)>)
            obj->_queuedSettings |= (0x1 << 4);
    }
    return true;
}

template <typename T>
bool inputOutputPinHandler::errorHandler(const gpiostatusCode &code, const T &param, inputOutputPinHandler *obj)
{
}

template <typename T>
bool inputOutputPinHandler::setParam(const T &param, inputOutputPinHandler *obj)
{
    bool ret{false};
    if constexpr (std::is_same_v<const gpioPort &, decltype(param)>)
    {
        *obj->_port = param;
        ret = true;
    }
    else if constexpr (std::is_same_v<const gpioPin &, decltype(param)>)
    {
        *obj->_pin = param;
        ret = true;
    }
    else if constexpr (std::is_same_v<const gpioMode &, decltype(param)>)
    {
        *obj->_mode = param;
        ret = true;
    }
    else if constexpr (std::is_same_v<const gpioPUPD &, decltype(param)>)
    {
        *obj->_pupd = param;
        ret = true;
    }
    else if constexpr (std::is_same_v<const gpioOutputSpeed &, decltype(param)>)
    {
        *obj->_outputSpeed = param;
        ret = true;
    }
    else if constexpr (std::is_same_v<const gpioOutputType &, decltype(param)>)
    {
        *obj->_outputType = param;
        ret = true;
    }
    else if constexpr (std::is_same_v<const gpioState &, decltype(param)>)
    {
        *obj->_pinState = param;
        ret = true;
    }
    else if constexpr (std::is_same_v<const gpioHardException &, decltype(param)>)
    {
        if (param == gpioHardException::disable)
            *obj->_hardException = false;
        else
            *obj->_hardException = true;

        ret = true;
    }
    else if constexpr (std::is_same_v<const gpioDebug &, decltype(param)>)
    {
        if (param == gpioDebug::disable)
            *obj->_debug = false;
        else
            *obj->_debug = true;

        ret = true;
    }
    return ret;
}

template <typename T>
void inputOutputPinHandler::init(const T &param, inputOutputPinHandler *obj)
{
    if constexpr (std::is_same_v<const gpioPort &, decltype(param)>)
    {
        obj->_instance = getGPIO(*obj->_port);
        RCC->AHB1ENR |= static_cast<uint32_t>(RCC_AHB1ENR_GPIOAEN << static_cast<paramType>(*obj->_port));
    }
    else if constexpr (std::is_same_v<const gpioPin &, decltype(param)>)
    {
    }
    else if constexpr (std::is_same_v<const gpioMode &, decltype(param)>)
    {
        paramType pin = static_cast<paramType>(*obj->_pin);
        paramType Mode = static_cast<paramType>(param);
        obj->_instance->MODER &= ~(uint32_t)(GPIO_MODER_MODE0_Msk << (2U * pin));
        obj->_instance->MODER |= (uint32_t)(Mode << (2U * pin));
    }
    else if constexpr (std::is_same_v<const gpioPUPD &, decltype(param)>)
    {
        paramType pin = static_cast<paramType>(*obj->_pin);
        paramType param = static_cast<paramType>(param);
        obj->_instance->PUPDR &= ~(uint32_t)(GPIO_PUPDR_PUPD0_Msk << (2U * pin));
        obj->_instance->PUPDR |= (uint32_t)(param << (2U * pin));
    }
    else if constexpr (std::is_same_v<const gpioOutputType &, decltype(param)>)
    {
        paramType pin = static_cast<paramType>(*obj->_pin);
        paramType OType = static_cast<paramType>(param);
        obj->_instance->OTYPER &= ~(uint32_t)(GPIO_OTYPER_OT0_Msk << pin);
        obj->_instance->OTYPER |= (uint32_t)(OType << pin);
    }
    else if constexpr (std::is_same_v<const gpioOutputSpeed &, decltype(param)>)
    {
        paramType pin = static_cast<paramType>(*obj->_pin);
        paramType param = static_cast<paramType>(param);
        obj->_instance->OSPEEDR &= ~(uint32_t)(GPIO_OSPEEDR_OSPEED0_Msk << 2U * pin);
        obj->_instance->OSPEEDR |= (uint32_t)(param << (2U * pin));
    }
    else if constexpr (std::is_same_v<const gpioState &, decltype(param)>)
    {
        paramType pin = static_cast<paramType>(*obj->_pin);
        if (param == gpioState::high)
            obj->_instance->ODR |= static_cast<uint32_t>(0x1 << pin);
        else
            obj->_instance->ODR &= ~static_cast<uint32_t>(0x1 << pin);
    }
}

#endif /* E85EB836_EDFF_4F9C_B124_4919496DAE51 */
