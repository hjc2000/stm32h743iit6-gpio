#include "GpioPinPD1.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPD1::Port()
{
	return GPIOD;
}

uint32_t bsp::GpioPinPD1::Pin()
{
	return GPIO_PIN_1;
}

std::string bsp::GpioPinPD1::PinName() const
{
	return "PD1";
}

void bsp::GpioPinPD1::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPD1::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
