#include "GpioPinPD15.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPD15::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPD15 &bsp::GpioPinPD15::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPD15>
    {
    public:
        std::unique_ptr<GpioPinPD15> Create() override
        {
            return std::unique_ptr<GpioPinPD15>{new GpioPinPD15{}};
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

GPIO_TypeDef *bsp::GpioPinPD15::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD15::Pin()
{
    return GPIO_PIN_15;
}

std::string bsp::GpioPinPD15::PinName() const
{
    return "PD15";
}

base::IEnumerable<std::string> &bsp::GpioPinPD15::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPD15::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPD15::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPD15::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
