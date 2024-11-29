#include "GpioPinPC5.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPC5::Port()
{
    return GPIOB;
}

uint32_t bsp::GpioPinPC5::Pin()
{
    return GPIO_PIN_5;
}

std::string bsp::GpioPinPC5::PinName() const
{
    return "PC5";
}

void bsp::GpioPinPC5::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    _is_open = true;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPC5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
