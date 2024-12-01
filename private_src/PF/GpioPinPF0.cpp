#include "GpioPinPF0.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPF0::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPF0 &bsp::GpioPinPF0::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPF0>
    {
    public:
        std::unique_ptr<GpioPinPF0> Create() override
        {
            return std::unique_ptr<GpioPinPF0>{new GpioPinPF0{}};
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

GPIO_TypeDef *bsp::GpioPinPF0::Port()
{
    return GPIOF;
}

uint32_t bsp::GpioPinPF0::Pin()
{
    return GPIO_PIN_0;
}

std::string bsp::GpioPinPF0::PinName() const
{
    return "PF0";
}

void bsp::GpioPinPF0::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOF_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPF0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
