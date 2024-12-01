#include "GpioPinPF15.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPF15::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPF15 &bsp::GpioPinPF15::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPF15>
    {
    public:
        std::unique_ptr<GpioPinPF15> Create() override
        {
            return std::unique_ptr<GpioPinPF15>{new GpioPinPF15{}};
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

GPIO_TypeDef *bsp::GpioPinPF15::Port()
{
    return GPIOF;
}

uint32_t bsp::GpioPinPF15::Pin()
{
    return GPIO_PIN_15;
}

std::string bsp::GpioPinPF15::PinName() const
{
    return "PF15";
}

base::IEnumerable<std::string> &bsp::GpioPinPF15::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPF15::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPF15::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOF_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPF15::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
