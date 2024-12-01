#include "GpioPinPE8.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE8::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPE8 &bsp::GpioPinPE8::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPE8>
    {
    public:
        std::unique_ptr<GpioPinPE8> Create() override
        {
            return std::unique_ptr<GpioPinPE8>{new GpioPinPE8{}};
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

GPIO_TypeDef *bsp::GpioPinPE8::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE8::Pin()
{
    return GPIO_PIN_8;
}

std::string bsp::GpioPinPE8::PinName() const
{
    return "PE8";
}

void bsp::GpioPinPE8::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE8::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
