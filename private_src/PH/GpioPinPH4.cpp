#include "GpioPinPH4.h"
#include <GpioPinOptions.h>
#include <hal.h>

bsp::GpioPinPH4 &bsp::GpioPinPH4::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPH4>
    {
    public:
        std::unique_ptr<GpioPinPH4> Create() override
        {
            return std::unique_ptr<GpioPinPH4>{new GpioPinPH4{}};
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

GPIO_TypeDef *bsp::GpioPinPH4::Port()
{
    return GPIOH;
}

uint32_t bsp::GpioPinPH4::Pin()
{
    return GPIO_PIN_4;
}

std::string bsp::GpioPinPH4::PinName() const
{
    return "PH4";
}

base::IEnumerable<std::string> &bsp::GpioPinPH4::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPH4::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPH4::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    _is_open = true;

    __HAL_RCC_GPIOH_CLK_ENABLE();
    GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPH4::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
