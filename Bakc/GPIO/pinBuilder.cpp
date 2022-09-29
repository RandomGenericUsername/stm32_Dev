#include "pinBuilder.hh"

pinBuilder::pinBuilder()
{

}

pinBuilder::pinBuilder(const ioPinParams *params, const IsParamSet *isParamSet, const gpioStatus *status)
{
    setPtr(params);
    setPtr(isParamSet);
    setPtr(status);
}
pinBuilder::~pinBuilder()
{


}

bool pinBuilder::readIDR()
{
    if(assertPortAndPin(*this))
    {
        if(_instance->IDR & (0x1UL << static_cast<unsigned int>(_settings->pin)))
        {
            _settings->state = pinState::high;
            return true;
        } 
        else
        {
            _settings->state = pinState::low;
            return false;
        }
    }
    *_status = gpioStatus::error;
    return false;
}

bool pinBuilder::writeODR(const pinState &state)
{
    if(assertPortAndPin(*this))
    {
        if(state == pinState::high) _instance->ODR |= 0x1UL << static_cast<unsigned int>(_settings->pin);
        else _instance->ODR &= ~(0x1UL << static_cast<unsigned int>(_settings->pin));
        return true;
    }
    return false;
}

void pinBuilder::setInstance()
{
}

void pinBuilder::enablePeripheralClock(bool enable)
{
    if(enable) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN << static_cast<unsigned int>(_settings->port);
    else RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOAEN_Msk << static_cast<unsigned int>(_settings->port));
}

void pinBuilder::init(const gpioPort &port)
{
    _instance = getGPIO(port);
    enablePeripheralClock();
}

void pinBuilder::init(const gpioPin &pin)
{

}

void pinBuilder::init(const gpioMode &mode)
{
    this->_instance->MODER &= ~(uint32_t)(GPIO_MODER_MODE0_Msk << (static_cast<int>(_settings->pin) * 2U ));
    this->_instance->MODER |= (uint32_t)(static_cast<unsigned int>(mode) << (static_cast<int>(_settings->pin) * 2U ));
}
void pinBuilder::init(const gpioOutputType &oType)
{
    this->_instance->OTYPER &= ~(uint32_t)(GPIO_OTYPER_OT0_Msk << (static_cast<int>(_settings->pin)));
    this->_instance->OTYPER |= (uint32_t)(static_cast<unsigned int>(oType) << (static_cast<int>(_settings->pin)));
}

void pinBuilder::init(const gpioOutputSpeed &oSpeed)
{
    this->_instance->OSPEEDR &= ~(uint32_t)(GPIO_OSPEEDR_OSPEED0_Msk << (static_cast<int>(_settings->pin) * 2U));
    this->_instance->OSPEEDR |= (uint32_t)(static_cast<unsigned int>(oSpeed) << (static_cast<int>(_settings->pin) * 2U));
}

void pinBuilder::init(const gpioPUPD &pupd)
{
    this->_instance->PUPDR &= ~(uint32_t)(GPIO_PUPDR_PUPD0_Msk << (static_cast<int>(_settings->pin) * 2U));
    this->_instance->PUPDR |= (uint32_t)(static_cast<unsigned int>(pupd) << (static_cast<int>(_settings->pin) * 2U));
}

void pinBuilder::init(const pinState &state)
{
    if(state == pinState::high) this->_instance->ODR |= static_cast<uint32_t>(0x1 << static_cast<int>(_settings->pin));
    else this->_instance->ODR &= ~static_cast<uint32_t>(0x1 << static_cast<int>(_settings->pin));
}

uint8_t pinBuilder::getParamIndex(const gpioPort &port) { return portParam; }
uint8_t pinBuilder::getParamIndex(const gpioPin &pin) {return pinParam; }
uint8_t pinBuilder::getParamIndex(const gpioMode &mode) {return modeParam; }
uint8_t pinBuilder::getParamIndex(const gpioOutputType &oType) {return oTypeParam; }
uint8_t pinBuilder::getParamIndex(const gpioOutputSpeed &oSpeed) { return oSpeedParam; }
uint8_t pinBuilder::getParamIndex(const gpioPUPD &pudp) { return pupdParam; }
uint8_t pinBuilder::getParamIndex(const pinState &state) { return stateParam; }

bool pinBuilder::assertPortAndPin(const pinBuilder &pinObj)
{
    if(pinObj._settings->port != gpioPort::null && pinObj._settings->pin != gpioPin::null)
    {
        return true;
    }
    return false;
}
bool pinBuilder::assertPortAndPin()
{
    return assertPortAndPin(*this);
}

bool pinBuilder::isPinSet(const GPIO_TypeDef *port, const gpioPin &pin)
{
    isPinSet(getGPIOIndex(port), pin);
}

bool pinBuilder::isPinSet(const gpioPort &port, const gpioPin &pin)
{
    if(pin != gpioPin::null && port != gpioPort::null)
    {
        if((initializedPins[static_cast<unsigned int>(port)] & (0x1UL << static_cast<unsigned int>(pin))))
        {
            return true;
        }
        else return false;
    }
    return false;
}



bool pinBuilder::setPtr(const ioPinParams *ptr)
{
    _settings = const_cast<ioPinParams*>(ptr);
    if(_settings == ptr) return true;
    else return false;
}
bool pinBuilder::setPtr(const gpioStatus *ptr)
{
    _status = const_cast<gpioStatus*>(ptr);
    return true;
}

bool pinBuilder::setPtr(const IsParamSet *isParamSet)
{
    _isParamSet = const_cast<IsParamSet*>(isParamSet);
    return true;
}

void pinBuilder::initQueuedSettings()
{
    uint8_t paramType;
    for(uint8_t i = 0; i < _maxPendingParams; i++)
    {
        paramType = i + 2;
        if((0x1 << paramType) & *_isParamSet)
        {
            if(paramType == modeParam) init(static_cast<gpioMode>(_pendingParamsValues[i]));
            else if(paramType == pupdParam) init(static_cast<gpioPUPD>(_pendingParamsValues[i]));
            else if(paramType == oTypeParam) init(static_cast<gpioOutputType>(_pendingParamsValues[i]));
            else if(paramType == oSpeedParam) init(static_cast<gpioOutputSpeed>(_pendingParamsValues[i]));
            else if(paramType == stateParam) init(static_cast<pinState>(_pendingParamsValues[i]));
        }
    }
    _numberOfPendingParams = 0;
    return;
}

bool pinBuilder::builder()
{
    if(!isPinSet(_settings->port, _settings->pin))
    {
        if(_settings->port != gpioPort::null)
        {
            setInstance();
            enablePeripheralClock();
            if(_settings->pin != gpioPin::null)
            {
                init(_settings->mode);
                init(_settings->pupd);
                if(_settings->mode == gpioMode::output)
                {
                    init(_settings->oType);
                    init(_settings->oSpeed);
                }
                initializedPins[static_cast<unsigned int>(_settings->port)] |= 0x1UL << static_cast<unsigned int>(_settings->pin);
                *_status = gpioStatus::ready;
                return true;
            }
            *_status = gpioStatus::reset;
            return false;
        }
        *_status = gpioStatus::reset;
        return false;
    }
    *_status = gpioStatus::error;
    return false;
}