#include "GpioPinPD4.h"
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPD4::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD4::Pin()
{
    return GPIO_PIN_4;
}

std::string bsp::GpioPinPD4::PinName() const
{
    return "PD4";
}

void bsp::GpioPinPD4::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
