#include "GpioPinPC5.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPC5::Initialize(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

bsp::GpioPinPC5 &bsp::GpioPinPC5::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPC5>
    {
    public:
        std::unique_ptr<GpioPinPC5> Create() override
        {
            return std::unique_ptr<GpioPinPC5>{new GpioPinPC5{}};
        }

        void Lock() override
        {
            DI_InterruptSwitch().DisableGlobalInterrupt();
        }

        void Unlock() override
        {
            DI_InterruptSwitch().EnableGlobalInterrupt();
        }
    };

    Getter o;
    return o.Instance();
}

GPIO_TypeDef *bsp::GpioPinPC5::Port()
{
    return GPIOC;
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

    __HAL_RCC_GPIOB_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPC5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
