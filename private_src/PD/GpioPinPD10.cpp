#include "GpioPinPD10.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPD10::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD10::Pin()
{
    return GPIO_PIN_10;
}

std::string bsp::GpioPinPD10::PinName() const
{
    return "PD10";
}

void bsp::GpioPinPD10::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPD10::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
