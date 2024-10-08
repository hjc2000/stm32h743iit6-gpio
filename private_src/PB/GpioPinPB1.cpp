#include "GpioPinPB1.h"

void bsp::GpioPinPB1::Init(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    if (options.WorkMode() == bsp::IGpioPinWorkMode::AlternateFunction)
    {
        if (options.AlternateFunction() == "timer3")
        {
            init.Alternate = GPIO_AF2_TIM3;
        }
        else
        {
            throw std::invalid_argument{"不支持的复用模式"};
        }
    }

    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

GPIO_TypeDef *bsp::GpioPinPB1::Port()
{
    return GPIOB;
}

uint32_t bsp::GpioPinPB1::Pin()
{
    return GPIO_PIN_1;
}

std::string bsp::GpioPinPB1::PinName() const
{
    return "PB1";
}

void bsp::GpioPinPB1::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    _is_open = true;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    Init(static_cast<bsp::GpioPinOptions const &>(options));
}

void bsp::GpioPinPB1::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
