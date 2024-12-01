#include "GpioPinPF2.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPF2::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPF2 &bsp::GpioPinPF2::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPF2>
    {
    public:
        std::unique_ptr<GpioPinPF2> Create() override
        {
            return std::unique_ptr<GpioPinPF2>{new GpioPinPF2{}};
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

GPIO_TypeDef *bsp::GpioPinPF2::Port()
{
    return GPIOF;
}

uint32_t bsp::GpioPinPF2::Pin()
{
    return GPIO_PIN_2;
}

std::string bsp::GpioPinPF2::PinName() const
{
    return "PF2";
}

base::IEnumerable<std::string> &bsp::GpioPinPF2::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPF2::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPF2::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOF_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPF2::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
