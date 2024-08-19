#include "GpioPinPD9.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPD9::Port()
{
	return GPIOD;
}

uint32_t bsp::GpioPinPD9::Pin()
{
	return GPIO_PIN_9;
}

std::string bsp::GpioPinPD9::PinName() const
{
	return "PD9";
}

void bsp::GpioPinPD9::Open(bsp::IGpioPinOptions const &options)
{
	if (_is_open)
	{
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
	init.Pin = Pin();
	HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPD9::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
