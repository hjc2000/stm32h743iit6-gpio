#include "GpioPinPE1.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE1::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPE1 &bsp::GpioPinPE1::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPE1>
    {
    public:
        std::unique_ptr<GpioPinPE1> Create() override
        {
            return std::unique_ptr<GpioPinPE1>{new GpioPinPE1{}};
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

GPIO_TypeDef *bsp::GpioPinPE1::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE1::Pin()
{
    return GPIO_PIN_1;
}

std::string bsp::GpioPinPE1::PinName() const
{
    return "PE1";
}

base::IEnumerable<std::string> &bsp::GpioPinPE1::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPE1::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPE1::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE1::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
