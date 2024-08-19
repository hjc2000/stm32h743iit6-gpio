#include "GpioPin.h"

bool bsp::GpioPin::ReadPin()
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(Port(), Pin());
	if (pin_state == GPIO_PinState::GPIO_PIN_SET)
	{
		return true;
	}

	return false;
}

void bsp::GpioPin::WritePin(bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(Port(), Pin(), state);
}

void bsp::GpioPin::TogglePin()
{
	HAL_GPIO_TogglePin(Port(), Pin());
}

void bsp::GpioPin::RegisterInterruptCallback(std::function<void()> callback)
{
	switch (Pin())
	{
	case GPIO_PIN_0:
	{
		DI_ExtiManager().Register(0, callback);
		break;
	}
	case GPIO_PIN_1:
	{
		DI_ExtiManager().Register(1, callback);
		break;
	}
	case GPIO_PIN_2:
	{
		DI_ExtiManager().Register(2, callback);
		break;
	}
	case GPIO_PIN_3:
	{
		DI_ExtiManager().Register(3, callback);
		break;
	}
	case GPIO_PIN_4:
	{
		DI_ExtiManager().Register(4, callback);
		break;
	}
	case GPIO_PIN_5:
	{
		DI_ExtiManager().Register(5, callback);
		break;
	}
	case GPIO_PIN_6:
	{
		DI_ExtiManager().Register(6, callback);
		break;
	}
	case GPIO_PIN_7:
	{
		DI_ExtiManager().Register(7, callback);
		break;
	}
	case GPIO_PIN_8:
	{
		DI_ExtiManager().Register(8, callback);
		break;
	}
	case GPIO_PIN_9:
	{
		DI_ExtiManager().Register(9, callback);
		break;
	}
	case GPIO_PIN_10:
	{
		DI_ExtiManager().Register(10, callback);
		break;
	}
	case GPIO_PIN_11:
	{
		DI_ExtiManager().Register(11, callback);
		break;
	}
	case GPIO_PIN_12:
	{
		DI_ExtiManager().Register(12, callback);
		break;
	}
	case GPIO_PIN_13:
	{
		DI_ExtiManager().Register(13, callback);
		break;
	}
	case GPIO_PIN_14:
	{
		DI_ExtiManager().Register(14, callback);
		break;
	}
	case GPIO_PIN_15:
	{
		DI_ExtiManager().Register(15, callback);
		break;
	}
	default:
	{
		throw std::invalid_argument{"非法引脚"};
	}
	}
}

void bsp::GpioPin::UnregisterInterruptCallback()
{
	switch (Pin())
	{
	case GPIO_PIN_0:
	{
		DI_ExtiManager().Unregister(0);
		break;
	}
	case GPIO_PIN_1:
	{
		DI_ExtiManager().Unregister(1);
		break;
	}
	case GPIO_PIN_2:
	{
		DI_ExtiManager().Unregister(2);
		break;
	}
	case GPIO_PIN_3:
	{
		DI_ExtiManager().Unregister(3);
		break;
	}
	case GPIO_PIN_4:
	{
		DI_ExtiManager().Unregister(4);
		break;
	}
	case GPIO_PIN_5:
	{
		DI_ExtiManager().Unregister(5);
		break;
	}
	case GPIO_PIN_6:
	{
		DI_ExtiManager().Unregister(6);
		break;
	}
	case GPIO_PIN_7:
	{
		DI_ExtiManager().Unregister(7);
		break;
	}
	case GPIO_PIN_8:
	{
		DI_ExtiManager().Unregister(8);
		break;
	}
	case GPIO_PIN_9:
	{
		DI_ExtiManager().Unregister(9);
		break;
	}
	case GPIO_PIN_10:
	{
		DI_ExtiManager().Unregister(10);
		break;
	}
	case GPIO_PIN_11:
	{
		DI_ExtiManager().Unregister(11);
		break;
	}
	case GPIO_PIN_12:
	{
		DI_ExtiManager().Unregister(12);
		break;
	}
	case GPIO_PIN_13:
	{
		DI_ExtiManager().Unregister(13);
		break;
	}
	case GPIO_PIN_14:
	{
		DI_ExtiManager().Unregister(14);
		break;
	}
	case GPIO_PIN_15:
	{
		DI_ExtiManager().Unregister(15);
		break;
	}
	default:
	{
		throw std::invalid_argument{"非法引脚"};
	}
	}
}
