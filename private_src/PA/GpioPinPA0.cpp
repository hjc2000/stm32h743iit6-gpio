#include "GpioPinPA0.h"
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPA0::Port()
{
    return GPIOA;
}

uint32_t bsp::GpioPinPA0::Pin()
{
    return GPIO_PIN_0;
}

std::string bsp::GpioPinPA0::PinName() const
{
    return "PA0";
}

void bsp::GpioPinPA0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
