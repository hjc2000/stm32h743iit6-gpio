#include "GpioPinPH3.h"
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPH3::Port()
{
    return GPIOH;
}

uint32_t bsp::GpioPinPH3::Pin()
{
    return GPIO_PIN_3;
}

std::string bsp::GpioPinPH3::PinName() const
{
    return "PH3";
}

void bsp::GpioPinPH3::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
