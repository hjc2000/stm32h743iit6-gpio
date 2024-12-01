#include "GpioPinPD10.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPD10::Initialize(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

bsp::GpioPinPD10 &bsp::GpioPinPD10::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPD10>
    {
    public:
        std::unique_ptr<GpioPinPD10> Create() override
        {
            return std::unique_ptr<GpioPinPD10>{new GpioPinPD10{}};
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

GPIO_TypeDef *bsp::GpioPinPD10::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD10::Pin()
{
    return GPIO_PIN_10;
}

std::string bsp::GpioPinPD10::PinName() const
{
    return "PD10";
}

base::IEnumerable<std::string> &bsp::GpioPinPD10::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPD10::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPD10::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPD10::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
