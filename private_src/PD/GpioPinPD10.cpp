#include "GpioPinPD10.h"
#include <hal.h>

bsp::GpioPinPD10 &bsp::GpioPinPD10::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPD10>
    {
    public:
        std::unique_ptr<GpioPinPD10> Create() override
        {
            return std::unique_ptr<GpioPinPD10>{new GpioPinPD10{}};
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

GPIO_TypeDef *bsp::GpioPinPD10::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD10::Pin()
{
    return GPIO_PIN_10;
}

std::string bsp::GpioPinPD10::PinName() const
{
    return "PD10";
}

base::IEnumerable<std::string> &bsp::GpioPinPD10::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

void bsp::GpioPinPD10::OpenAsAlternateFunctionMode(std::string function_name, bsp::IGpioPinPullMode pull_mode, bsp::IGpioPinDriver driver_mode)
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
    _is_open = true;
}
