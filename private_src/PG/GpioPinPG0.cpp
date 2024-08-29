#include "GpioPinPG0.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPG0::Port()
{
    return GPIOG;
}

uint32_t bsp::GpioPinPG0::Pin()
{
    return GPIO_PIN_0;
}

std::string bsp::GpioPinPG0::PinName() const
{
    return "PG0";
}

void bsp::GpioPinPG0::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    _is_open = true;

    __HAL_RCC_GPIOG_CLK_ENABLE();
    GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPG0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
