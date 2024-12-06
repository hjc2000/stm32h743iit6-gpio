#include "GpioPinPD5.h"
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPD5::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD5::Pin()
{
    return GPIO_PIN_5;
}

std::string bsp::GpioPinPD5::PinName() const
{
    return "PD5";
}

void bsp::GpioPinPD5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
