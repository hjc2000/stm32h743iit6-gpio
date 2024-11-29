#include "GpioPinPD0.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPD0::Initialize(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

bsp::GpioPinPD0 &bsp::GpioPinPD0::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPD0>
    {
    public:
        std::unique_ptr<GpioPinPD0> Create() override
        {
            return std::unique_ptr<GpioPinPD0>{new GpioPinPD0{}};
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

GPIO_TypeDef *bsp::GpioPinPD0::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD0::Pin()
{
    return GPIO_PIN_0;
}

std::string bsp::GpioPinPD0::PinName() const
{
    return "PD0";
}

base::IEnumerable<std::string> &bsp::GpioPinPD0::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPD0::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPD0::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPD0::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
