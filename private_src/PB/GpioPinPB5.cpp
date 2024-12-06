#include "GpioPinPB5.h"
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPB5::Port()
{
    return GPIOB;
}

uint32_t bsp::GpioPinPB5::Pin()
{
    return GPIO_PIN_5;
}

std::string bsp::GpioPinPB5::PinName() const
{
    return "PB5";
}

void bsp::GpioPinPB5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
