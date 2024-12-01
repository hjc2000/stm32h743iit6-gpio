#include "GpioPinPD14.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPD14::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPD14 &bsp::GpioPinPD14::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPD14>
    {
    public:
        std::unique_ptr<GpioPinPD14> Create() override
        {
            return std::unique_ptr<GpioPinPD14>{new GpioPinPD14{}};
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

GPIO_TypeDef *bsp::GpioPinPD14::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD14::Pin()
{
    return GPIO_PIN_14;
}

std::string bsp::GpioPinPD14::PinName() const
{
    return "PD14";
}

base::IEnumerable<std::string> &bsp::GpioPinPD14::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPD14::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPD14::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPD14::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
