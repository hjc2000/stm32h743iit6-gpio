#include "GpioPinPD5.h"
#include <GpioPinOptions.h>
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

void bsp::GpioPinPD5::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPD5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
