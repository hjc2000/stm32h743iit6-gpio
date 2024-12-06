#include "GpioPinPB0.h"

GPIO_TypeDef *bsp::GpioPinPB0::Port()
{
    return GPIOB;
}

uint32_t bsp::GpioPinPB0::Pin()
{
    return GPIO_PIN_0;
}

std::string bsp::GpioPinPB0::PinName() const
{
    return "PB0";
}

void bsp::GpioPinPB0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
