#include "GpioPinPE7.h"
#include <GpioPinOptions.h>
#include <hal.h>

void bsp::GpioPinPE7::Initialize(bsp::GpioPinOptions const &options)
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

bsp::GpioPinPE7 &bsp::GpioPinPE7::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPE7>
    {
    public:
        std::unique_ptr<GpioPinPE7> Create() override
        {
            return std::unique_ptr<GpioPinPE7>{new GpioPinPE7{}};
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

GPIO_TypeDef *bsp::GpioPinPE7::Port()
{
    return GPIOE;
}

uint32_t bsp::GpioPinPE7::Pin()
{
    return GPIO_PIN_7;
}

std::string bsp::GpioPinPE7::PinName() const
{
    return "PE7";
}

base::IEnumerable<std::string> &bsp::GpioPinPE7::SupportedAlternateFunctions()
{
    return _supported_alternate_functions;
}

bool bsp::GpioPinPE7::IsOpen()
{
    return _is_open;
}

void bsp::GpioPinPE7::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOE_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPE7::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
