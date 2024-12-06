#include "GpioPinPC0.h"
#include <hal.h>

bsp::GpioPinPC0 &bsp::GpioPinPC0::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPC0>
    {
    public:
        std::unique_ptr<GpioPinPC0> Create() override
        {
            return std::unique_ptr<GpioPinPC0>{new GpioPinPC0{}};
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

GPIO_TypeDef *bsp::GpioPinPC0::Port()
{
    return GPIOC;
}

uint32_t bsp::GpioPinPC0::Pin()
{
    return GPIO_PIN_0;
}

std::string bsp::GpioPinPC0::PinName() const
{
    return "PC0";
}

base::IEnumerable<std::string> &bsp::GpioPinPC0::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPC0::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPC0::OpenAsAlternateFunctionMode(std::string function_name, bsp::IGpioPinPullMode pull_mode, bsp::IGpioPinDriver driver_mode)
{
    EnableClock();
    GPIO_InitTypeDef def{};
    if (function_name == "fmc")
    {
        def.Alternate = GPIO_AF12_FMC;
    }
    else
    {
        throw std::invalid_argument{"不支持的 AlternateFunction"};
    }

    switch (pull_mode)
    {
    default:
    case bsp::IGpioPinPullMode::NoPull:
        {
            def.Pull = GPIO_NOPULL;
            break;
        }
    case bsp::IGpioPinPullMode::PullUp:
        {
            def.Pull = GPIO_PULLUP;
            break;
        }
    case bsp::IGpioPinPullMode::PullDown:
        {
            def.Pull = GPIO_PULLDOWN;
            break;
        }
    }

    switch (driver_mode)
    {
    case bsp::IGpioPinDriver::PushPull:
        {
            def.Mode = GPIO_MODE_AF_PP;
            break;
        }
    case bsp::IGpioPinDriver::OpenDrain:
        {
            def.Mode = GPIO_MODE_AF_PP;
            break;
        }
    default:
        {
            throw std::invalid_argument{"不支持的 Driver"};
        }
    }

    def.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    def.Pin = Pin();
    HAL_GPIO_Init(Port(), &def);
}

void bsp::GpioPinPC0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
