#include "GpioPinPF13.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPF13::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPF13 &bsp::GpioPinPF13::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPF13>
    {
    public:
        std::unique_ptr<GpioPinPF13> Create() override
        {
            return std::unique_ptr<GpioPinPF13>{new GpioPinPF13{}};
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

GPIO_TypeDef *bsp::GpioPinPF13::Port()
{
    return GPIOF;
}

uint32_t bsp::GpioPinPF13::Pin()
{
    return GPIO_PIN_13;
}

std::string bsp::GpioPinPF13::PinName() const
{
    return "PF13";
}

base::IEnumerable<std::string> &bsp::GpioPinPF13::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPF13::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPF13::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOF_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPF13::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
