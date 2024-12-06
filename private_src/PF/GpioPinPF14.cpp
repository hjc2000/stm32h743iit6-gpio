#include "GpioPinPF14.h"
#include <hal.h>

bsp::GpioPinPF14 &bsp::GpioPinPF14::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPF14>
    {
    public:
        std::unique_ptr<GpioPinPF14> Create() override
        {
            return std::unique_ptr<GpioPinPF14>{new GpioPinPF14{}};
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

GPIO_TypeDef *bsp::GpioPinPF14::Port()
{
    return GPIOF;
}

uint32_t bsp::GpioPinPF14::Pin()
{
    return GPIO_PIN_14;
}

std::string bsp::GpioPinPF14::PinName() const
{
    return "PF14";
}

base::IEnumerable<std::string> &bsp::GpioPinPF14::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPF14::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPF14::OpenAsAlternateFunctionMode(std::string function_name, bsp::IGpioPinPullMode pull_mode, bsp::IGpioPinDriver driver_mode)
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

void bsp::GpioPinPF14::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
