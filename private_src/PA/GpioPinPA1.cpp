#include "GpioPinPA1.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPA1::Port()
{
    return GPIOA;
}

uint32_t bsp::GpioPinPA1::Pin()
{
    return GPIO_PIN_1;
}

std::string bsp::GpioPinPA1::PinName() const
{
    return "PA1";
}

void bsp::GpioPinPA1::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    _is_open = true;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPA1::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
