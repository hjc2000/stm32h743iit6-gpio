#include "GpioPinPE14.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE14::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPE14 &bsp::GpioPinPE14::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPE14>
    {
    public:
        std::unique_ptr<GpioPinPE14> Create() override
        {
            return std::unique_ptr<GpioPinPE14>{new GpioPinPE14{}};
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

GPIO_TypeDef *bsp::GpioPinPE14::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE14::Pin()
{
    return GPIO_PIN_14;
}

std::string bsp::GpioPinPE14::PinName() const
{
    return "PE14";
}

void bsp::GpioPinPE14::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE14::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
