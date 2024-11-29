#include "GpioPinOptions.h"
#include <stdexcept>

#pragma region 初始化为各种模式

void bsp::GpioPinOptions::InitAsGpioMode(GPIO_InitTypeDef &o) const
{
    auto init_as_input_mode = [&]()
    {
        switch (TriggerEdge())
        {
        case bsp::IGpioPinTriggerEdge::Disable:
            {
                o.Mode = GPIO_MODE_INPUT;
                break;
            }
        case bsp::IGpioPinTriggerEdge::RisingEdge:
            {
                o.Mode = GPIO_MODE_IT_RISING;
                break;
            }
        case bsp::IGpioPinTriggerEdge::FallingEdge:
            {
                o.Mode = GPIO_MODE_IT_FALLING;
                break;
            }
        case bsp::IGpioPinTriggerEdge::BothEdge:
            {
                o.Mode = GPIO_MODE_IT_RISING_FALLING;
                break;
            }
        default:
            {
                throw std::invalid_argument{"不支持的 TriggerEdge"};
            }
        }
    };

    auto init_as_output_mode = [&]()
    {
        switch (Driver())
        {
        case bsp::IGpioPinDriver::PushPull:
            {
                o.Mode = GPIO_MODE_OUTPUT_PP;
                break;
            }
        case bsp::IGpioPinDriver::OpenDrain:
            {
                o.Mode = GPIO_MODE_OUTPUT_OD;
                break;
            }
        default:
            {
                throw std::invalid_argument{"不支持的 Driver"};
            }
        }
    };

    switch (Direction())
    {
    case bsp::IGpioPinDirection::Input:
        {
            init_as_input_mode();
            break;
        }
    case bsp::IGpioPinDirection::Output:
        {
            init_as_output_mode();
            break;
        }
    default:
        {
            throw std::invalid_argument{"不支持的 Direction"};
        }
    }
}

void bsp::GpioPinOptions::InitAsAlternateFunctionMode(GPIO_InitTypeDef &o) const
{
    switch (Driver())
    {
    case bsp::IGpioPinDriver::PushPull:
        {
            o.Mode = GPIO_MODE_AF_PP;
            break;
        }
    case bsp::IGpioPinDriver::OpenDrain:
        {
            o.Mode = GPIO_MODE_AF_OD;
            break;
        }
    default:
        {
            throw std::invalid_argument{"不支持的 Driver"};
        }
    }
}

void bsp::GpioPinOptions::InitAsEventMode(GPIO_InitTypeDef &o) const
{
    switch (TriggerEdge())
    {
    case bsp::IGpioPinTriggerEdge::RisingEdge:
        {
            o.Mode = GPIO_MODE_EVT_RISING;
            break;
        }
    case bsp::IGpioPinTriggerEdge::FallingEdge:
        {
            o.Mode = GPIO_MODE_EVT_FALLING;
            break;
        }
    case bsp::IGpioPinTriggerEdge::BothEdge:
        {
            o.Mode = GPIO_MODE_EVT_RISING_FALLING;
            break;
        }
    default:
        {
            throw std::invalid_argument{"不支持的 TriggerEdge"};
        }
    }
}

void bsp::GpioPinOptions::InitAsAnalogMode(GPIO_InitTypeDef &o) const
{
    o.Mode = GPIO_MODE_ANALOG;
}

#pragma endregion

bsp::GpioPinOptions::operator GPIO_InitTypeDef() const
{
    GPIO_InitTypeDef o = _hal_gpio_init;
    switch (WorkMode())
    {
    case bsp::IGpioPinWorkMode::Gpio:
        {
            InitAsGpioMode(o);
            break;
        }
    case bsp::IGpioPinWorkMode::AlternateFunction:
        {
            InitAsAlternateFunctionMode(o);
            break;
        }
    case bsp::IGpioPinWorkMode::Event:
        {
            InitAsEventMode(o);
            break;
        }
    case bsp::IGpioPinWorkMode::Analog:
        {
            InitAsAnalogMode(o);
            break;
        }
    default:
        {
            throw std::invalid_argument{"非法 WorkMode"};
        }
    }

    return o;
}

#pragma region IGpioPinOptions

bsp::IGpioPinDirection bsp::GpioPinOptions::Direction() const
{
    return _direction;
}

void bsp::GpioPinOptions::SetDirection(bsp::IGpioPinDirection value)
{
    _direction = value;
}

bsp::IGpioPinWorkMode bsp::GpioPinOptions::WorkMode() const
{
    return _work_mode;
}

void bsp::GpioPinOptions::SetWorkMode(bsp::IGpioPinWorkMode value)
{
    _work_mode = value;
}

bsp::IGpioPinTriggerEdge bsp::GpioPinOptions::TriggerEdge() const
{
    return _trigger_edge;
}

void bsp::GpioPinOptions::SetTriggerEdge(bsp::IGpioPinTriggerEdge value)
{
    _trigger_edge = value;
}

bsp::IGpioPinPullMode bsp::GpioPinOptions::PullMode() const
{
    switch (_hal_gpio_init.Pull)
    {
    default:
    case GPIO_NOPULL:
        {
            return bsp::IGpioPinPullMode::NoPull;
        }
    case GPIO_PULLUP:
        {
            return bsp::IGpioPinPullMode::PullUp;
        }
    case GPIO_PULLDOWN:
        {
            return bsp::IGpioPinPullMode::PullDown;
        }
    }
}

void bsp::GpioPinOptions::SetPullMode(bsp::IGpioPinPullMode value)
{
    switch (value)
    {
    default:
    case bsp::IGpioPinPullMode::NoPull:
        {
            _hal_gpio_init.Pull = GPIO_NOPULL;
            break;
        }
    case bsp::IGpioPinPullMode::PullUp:
        {
            _hal_gpio_init.Pull = GPIO_PULLUP;
            break;
        }
    case bsp::IGpioPinPullMode::PullDown:
        {
            _hal_gpio_init.Pull = GPIO_PULLDOWN;
            break;
        }
    }
}

bsp::IGpioPinDriver bsp::GpioPinOptions::Driver() const
{
    return _driver;
}

void bsp::GpioPinOptions::SetDriver(bsp::IGpioPinDriver value)
{
    _driver = value;
}

int bsp::GpioPinOptions::SpeedLevel() const
{
    switch (_hal_gpio_init.Speed)
    {
    case GPIO_SPEED_FREQ_LOW:
        {
            return 0;
        }
    case GPIO_SPEED_FREQ_MEDIUM:
        {
            return 1;
        }
    case GPIO_SPEED_FREQ_HIGH:
        {
            return 2;
        }
    default:
    case GPIO_SPEED_FREQ_VERY_HIGH:
        {
            return 3;
        }
    }
}

void bsp::GpioPinOptions::SetSpeedLevel(int value)
{
    switch (value)
    {
    case 0:
        {
            _hal_gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
            break;
        }
    case 1:
        {
            _hal_gpio_init.Speed = GPIO_SPEED_FREQ_MEDIUM;
            break;
        }
    case 2:
        {
            _hal_gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
            break;
        }
    default:
    case 3:
        {
            _hal_gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
            break;
        }
    }
}

std::string bsp::GpioPinOptions::AlternateFunction() const
{
    return _af_mode;
}

void bsp::GpioPinOptions::SetAlternateFunction(std::string const &value)
{
    _af_mode = value;
}

#pragma endregion
