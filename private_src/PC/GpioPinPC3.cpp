#include "GpioPinPC3.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPC3::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPC3 &bsp::GpioPinPC3::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPC3>
    {
    public:
        std::unique_ptr<GpioPinPC3> Create() override
        {
            return std::unique_ptr<GpioPinPC3>{new GpioPinPC3{}};
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

GPIO_TypeDef *bsp::GpioPinPC3::Port()
{
    return GPIOC;
}

uint32_t bsp::GpioPinPC3::Pin()
{
    return GPIO_PIN_3;
}

std::string bsp::GpioPinPC3::PinName() const
{
    return "PC3";
}

base::IEnumerable<std::string> &bsp::GpioPinPC3::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPC3::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPC3::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOC_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPC3::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
