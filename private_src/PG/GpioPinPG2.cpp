#include "GpioPinPG2.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPG2::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPG2 &bsp::GpioPinPG2::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPG2>
    {
    public:
        std::unique_ptr<GpioPinPG2> Create() override
        {
            return std::unique_ptr<GpioPinPG2>{new GpioPinPG2{}};
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

GPIO_TypeDef *bsp::GpioPinPG2::Port()
{
    return GPIOG;
}

uint32_t bsp::GpioPinPG2::Pin()
{
    return GPIO_PIN_2;
}

std::string bsp::GpioPinPG2::PinName() const
{
    return "PG2";
}

void bsp::GpioPinPG2::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOG_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPG2::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
