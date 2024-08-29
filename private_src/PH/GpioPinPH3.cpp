#include "GpioPinPH3.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPH3::Port()
{
    return GPIOH;
}

uint32_t bsp::GpioPinPH3::Pin()
{
    return GPIO_PIN_3;
}

std::string bsp::GpioPinPH3::PinName() const
{
    return "PH3";
}

void bsp::GpioPinPH3::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    _is_open = true;

    __HAL_RCC_GPIOH_CLK_ENABLE();
    GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPH3::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
