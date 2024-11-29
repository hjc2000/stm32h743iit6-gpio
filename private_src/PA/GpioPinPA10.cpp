#include "GpioPinPA10.h"

void bsp::GpioPinPA10::Initialize(bsp::GpioPinOptions const &options)
{
    GPIO_InitTypeDef init = options;
    if (options.WorkMode() == bsp::IGpioPinWorkMode::AlternateFunction)
    {
        if (options.AlternateFunction() == "usart1")
        {
            init.Alternate = GPIO_AF7_USART1;
        }
        else
        {
            throw std::invalid_argument{"不支持的 AlternateFunction"};
        }
    }

    init.Pin = Pin();
    HAL_GPIO_Init(Port(), &init);
}

bsp::GpioPinPA10 &bsp::GpioPinPA10::Instance()
{
    class Getter :
        public base::SingletonGetter<GpioPinPA10>
    {
    public:
        std::unique_ptr<GpioPinPA10> Create() override
        {
            return std::unique_ptr<GpioPinPA10>{new GpioPinPA10{}};
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

GPIO_TypeDef *bsp::GpioPinPA10::Port()
{
    return GPIOA;
}

uint32_t bsp::GpioPinPA10::Pin()
{
    return GPIO_PIN_10;
}

std::string bsp::GpioPinPA10::PinName() const
{
    return "PA10";
}

void bsp::GpioPinPA10::Open(bsp::IGpioPinOptions const &options)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭"};
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    Initialize(static_cast<bsp::GpioPinOptions const &>(options));
    _is_open = true;
}

void bsp::GpioPinPA10::Close()
{
    if (!_is_open)
    {
        return;
    }

    _is_open = false;
}
