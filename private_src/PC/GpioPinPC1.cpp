#include "GpioPinPC1.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPC1::Initialize(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

bsp::GpioPinPC1 &bsp::GpioPinPC1::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPC1>
    {
    public:
        std::unique_ptr<GpioPinPC1> Create() override
        {
            return std::unique_ptr<GpioPinPC1>{new GpioPinPC1{}};
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

GPIO_TypeDef *bsp::GpioPinPC1::Port()
{
    return GPIOC;
}

uint32_t bsp::GpioPinPC1::Pin()
{
    return GPIO_PIN_1;
}

std::string bsp::GpioPinPC1::PinName() const
{
    return "PC1";
}

void bsp::GpioPinPC1::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOC_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPC1::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
