#include "GpioPinPD8.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPD8::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD8::Pin()
{
    return GPIO_PIN_8;
}

std::string bsp::GpioPinPD8::PinName() const
{
    return "PD8";
}

void bsp::GpioPinPD8::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    _is_open = true;

    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPD8::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
