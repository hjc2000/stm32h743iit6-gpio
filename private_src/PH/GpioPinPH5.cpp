#include "GpioPinPH5.h"
#include <GpioPinOptions.h>
#include <hal.h>

bsp::GpioPinPH5 &bsp::GpioPinPH5::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPH5>
    {
    public:
        std::unique_ptr<GpioPinPH5> Create() override
        {
            return std::unique_ptr<GpioPinPH5>{new GpioPinPH5{}};
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

GPIO_TypeDef *bsp::GpioPinPH5::Port()
{
    return GPIOH;
}

uint32_t bsp::GpioPinPH5::Pin()
{
    return GPIO_PIN_5;
}

std::string bsp::GpioPinPH5::PinName() const
{
    return "PH5";
}

base::IEnumerable<std::string> &bsp::GpioPinPH5::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPH5::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPH5::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPH5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
