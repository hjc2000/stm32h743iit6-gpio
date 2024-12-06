#include "GpioPinPG1.h"
#include <hal.h>

bsp::GpioPinPG1 &bsp::GpioPinPG1::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPG1>
    {
    public:
        std::unique_ptr<GpioPinPG1> Create() override
        {
            return std::unique_ptr<GpioPinPG1>{new GpioPinPG1{}};
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

GPIO_TypeDef *bsp::GpioPinPG1::Port()
{
    return GPIOG;
}

uint32_t bsp::GpioPinPG1::Pin()
{
    return GPIO_PIN_1;
}

std::string bsp::GpioPinPG1::PinName() const
{
    return "PG1";
}

void bsp::GpioPinPG1::OpenAsAlternateFunctionMode(std::string function_name, bsp::IGpioPinPullMode pull_mode, bsp::IGpioPinDriver driver_mode)
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

void bsp::GpioPinPG1::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
