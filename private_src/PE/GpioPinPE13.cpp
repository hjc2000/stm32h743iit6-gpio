#include "GpioPinPE13.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE13::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPE13 &bsp::GpioPinPE13::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPE13>
    {
    public:
        std::unique_ptr<GpioPinPE13> Create() override
        {
            return std::unique_ptr<GpioPinPE13>{new GpioPinPE13{}};
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

GPIO_TypeDef *bsp::GpioPinPE13::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE13::Pin()
{
    return GPIO_PIN_13;
}

std::string bsp::GpioPinPE13::PinName() const
{
    return "PE13";
}

void bsp::GpioPinPE13::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE13::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
