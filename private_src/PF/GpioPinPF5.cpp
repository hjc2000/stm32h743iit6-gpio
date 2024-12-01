#include "GpioPinPF5.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPF5::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPF5 &bsp::GpioPinPF5::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPF5>
    {
    public:
        std::unique_ptr<GpioPinPF5> Create() override
        {
            return std::unique_ptr<GpioPinPF5>{new GpioPinPF5{}};
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

GPIO_TypeDef *bsp::GpioPinPF5::Port()
{
    return GPIOF;
}

uint32_t bsp::GpioPinPF5::Pin()
{
    return GPIO_PIN_5;
}

std::string bsp::GpioPinPF5::PinName() const
{
    return "PF5";
}

base::IEnumerable<std::string> &bsp::GpioPinPF5::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPF5::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPF5::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOF_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPF5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
