#include "GpioPinPB5.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPB5::Port()
{
    return GPIOB;
}

uint32_t bsp::GpioPinPB5::Pin()
{
    return GPIO_PIN_5;
}

std::string bsp::GpioPinPB5::PinName() const
{
    return "PB5";
}

void bsp::GpioPinPB5::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPB5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
