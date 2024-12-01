#include "GpioPinPE15.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE15::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPE15 &bsp::GpioPinPE15::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPE15>
    {
    public:
        std::unique_ptr<GpioPinPE15> Create() override
        {
            return std::unique_ptr<GpioPinPE15>{new GpioPinPE15{}};
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

GPIO_TypeDef *bsp::GpioPinPE15::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE15::Pin()
{
    return GPIO_PIN_15;
}

std::string bsp::GpioPinPE15::PinName() const
{
    return "PE15";
}

void bsp::GpioPinPE15::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE15::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
