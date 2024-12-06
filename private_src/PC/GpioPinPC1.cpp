#include "GpioPinPC1.h"
#include <hal.h>

bsp::GpioPinPC1 &bsp::GpioPinPC1::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPC1>
    {
    public:
        std::unique_ptr<GpioPinPC1> Create() override
        {
            return std::unique_ptr<GpioPinPC1>{new GpioPinPC1{}};
        }

        void Lock() override
        {
            DI_DisableGlobalInterrupt();
        }

        void Unlock() override
        {
            DI_EnableGlobalInterrupt();
        }
    };

    Getter o;
    return o.Instance();
}

GPIO_TypeDef *bsp::GpioPinPC1::Port()
{
    return GPIOC;
}

uint32_t bsp::GpioPinPC1::Pin()
{
    return GPIO_PIN_1;
}

std::string bsp::GpioPinPC1::PinName() const
{
    return "PC1";
}
