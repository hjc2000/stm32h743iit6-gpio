#include "GpioPinPD9.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPD9::Initialize(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

bsp::GpioPinPD9 &bsp::GpioPinPD9::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPD9>
    {
    public:
        std::unique_ptr<GpioPinPD9> Create() override
        {
            return std::unique_ptr<GpioPinPD9>{new GpioPinPD9{}};
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

GPIO_TypeDef *bsp::GpioPinPD9::Port()
{
    return GPIOD;
}

uint32_t bsp::GpioPinPD9::Pin()
{
    return GPIO_PIN_9;
}

std::string bsp::GpioPinPD9::PinName() const
{
    return "PD9";
}

base::IEnumerable<std::string> &bsp::GpioPinPD9::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPD9::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPD9::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPD9::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
