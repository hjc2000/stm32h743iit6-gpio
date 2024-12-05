#include "GpioPinPG5.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPG5::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPG5 &bsp::GpioPinPG5::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPG5>
    {
    public:
        std::unique_ptr<GpioPinPG5> Create() override
        {
            return std::unique_ptr<GpioPinPG5>{new GpioPinPG5{}};
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

GPIO_TypeDef *bsp::GpioPinPG5::Port()
{
    return GPIOG;
}

uint32_t bsp::GpioPinPG5::Pin()
{
    return GPIO_PIN_5;
}

std::string bsp::GpioPinPG5::PinName() const
{
    return "PG5";
}

void bsp::GpioPinPG5::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOG_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPG5::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}