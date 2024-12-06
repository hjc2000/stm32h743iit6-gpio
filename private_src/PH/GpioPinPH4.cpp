#include "GpioPinPH4.h"
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

void bsp::GpioPinPH4::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
