#include "GpioPinPA9.h"

void bsp::GpioPinPA9::Init(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    init.Pin = Pin();

    if (options.AlternateFunction() == "usart1")
    {
        init.Alternate = GPIO_AF7_USART1;
    }
    else
    {
        throw std::invalid_argument{"不支持的复用模式"};
    }

    HAL_GPIO_Init(Port(), &init);
}

GPIO_TypeDef *bsp::GpioPinPA9::Port()
{
    return GPIOA;
}

uint32_t bsp::GpioPinPA9::Pin()
{
    return GPIO_PIN_9;
}

std::string bsp::GpioPinPA9::PinName() const
{
    return "PA9";
}

void bsp::GpioPinPA9::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        return;
    }

    _is_open = true;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    Init(static_cast<bsp::GpioPinOptions const &>(options));
}

void bsp::GpioPinPA9::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
