#include "GpioPinPE10.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE10::Initialize(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    if (options.WorkMode() == bsp::IGpioPinWorkMode::AlternateFunction)
    {
        if (options.AlternateFunction() == "fmc")
        {
            init.Alternate = GPIO_AF12_FMC;
        }
        else
        {
            throw std::invalid_argument{"不支持的 AlternateFunction"};
        }
    }

    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

GPIO_TypeDef *bsp::GpioPinPE10::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE10::Pin()
{
    return GPIO_PIN_10;
}

std::string bsp::GpioPinPE10::PinName() const
{
    return "PE10";
}

void bsp::GpioPinPE10::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE10::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
