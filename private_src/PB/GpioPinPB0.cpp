#include "GpioPinPB0.h"

GPIO_TypeDef *bsp::GpioPinPB0::Port()
{
    return GPIOB;
}

uint32_t bsp::GpioPinPB0::Pin()
{
    return GPIO_PIN_0;
}

std::string bsp::GpioPinPB0::PinName() const
{
    return "PB0";
}

void bsp::GpioPinPB0::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPB0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
