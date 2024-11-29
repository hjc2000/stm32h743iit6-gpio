#include "GpioPinPC0.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPC0::Initialize(bsp::GpioPinOptions const &options)
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

void bsp::GpioPinPC0::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOC_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPC0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
