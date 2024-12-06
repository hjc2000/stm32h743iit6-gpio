#include "GpioPinPE4.h"
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE4::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE4::Pin()
{
    return GPIO_PIN_4;
}

void bsp::GpioPinPE4::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
