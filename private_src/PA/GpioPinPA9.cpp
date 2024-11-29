#include "GpioPinPA9.h"

void bsp::GpioPinPA9::Initialize(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    if (options.WorkMode() == bsp::IGpioPinWorkMode::AlternateFunction)
    {
        if (options.AlternateFunction() == "usart1")
        {
            init.Alternate = GPIO_AF7_USART1;
        }
        else
        {
            throw std::invalid_argument{"不支持的复用模式"};
        }
    }

    init.Pin = Pin();
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
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPA9::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
