#include "GpioPinPB1.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPB1::Port()
{
    return GPIOB;
}

uint32_t bsp::GpioPinPB1::Pin()
{
    return GPIO_PIN_1;
}

std::string bsp::GpioPinPB1::PinName() const
{
    return "PB1";
}

void bsp::GpioPinPB1::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        return;
    }

    _is_open = true;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPB1::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
