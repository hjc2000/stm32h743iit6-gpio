#include "GpioPinPE0.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE0::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPE0 &bsp::GpioPinPE0::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPE0>
    {
    public:
        std::unique_ptr<GpioPinPE0> Create() override
        {
            return std::unique_ptr<GpioPinPE0>{new GpioPinPE0{}};
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

GPIO_TypeDef *bsp::GpioPinPE0::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE0::Pin()
{
    return GPIO_PIN_0;
}

std::string bsp::GpioPinPE0::PinName() const
{
    return "PE0";
}

base::IEnumerable<std::string> &bsp::GpioPinPE0::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPE0::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPE0::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
