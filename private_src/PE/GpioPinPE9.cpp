#include "GpioPinPE9.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE9::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE9::Pin()
{
    return GPIO_PIN_9;
}

std::string bsp::GpioPinPE9::PinName() const
{
    return "PE9";
}

void bsp::GpioPinPE9::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    _is_open = true;

    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPE9::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
