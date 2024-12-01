#include "GpioPinPE11.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE11::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPE11 &bsp::GpioPinPE11::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPE11>
    {
    public:
        std::unique_ptr<GpioPinPE11> Create() override
        {
            return std::unique_ptr<GpioPinPE11>{new GpioPinPE11{}};
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

GPIO_TypeDef *bsp::GpioPinPE11::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE11::Pin()
{
    return GPIO_PIN_11;
}

std::string bsp::GpioPinPE11::PinName() const
{
    return "PE11";
}

void bsp::GpioPinPE11::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE11::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
