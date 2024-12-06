#include "GpioPinPG12.h"
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPG12::Port()
{
    return GPIOG;
}

uint32_t bsp::GpioPinPG12::Pin()
{
    return GPIO_PIN_12;
}

std::string bsp::GpioPinPG12::PinName() const
{
    return "PG12";
}

void bsp::GpioPinPG12::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
