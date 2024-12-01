#include "GpioPinPF12.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPF12::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPF12 &bsp::GpioPinPF12::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPF12>
    {
    public:
        std::unique_ptr<GpioPinPF12> Create() override
        {
            return std::unique_ptr<GpioPinPF12>{new GpioPinPF12{}};
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

GPIO_TypeDef *bsp::GpioPinPF12::Port()
{
    return GPIOF;
}

uint32_t bsp::GpioPinPF12::Pin()
{
    return GPIO_PIN_12;
}

std::string bsp::GpioPinPF12::PinName() const
{
    return "PF12";
}

base::IEnumerable<std::string> &bsp::GpioPinPF12::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPF12::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPF12::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOF_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPF12::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
