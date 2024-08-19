#include "GpioPinPE0.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE0::Port()
{
	return GPIOE;
}

uint32_t bsp::GpioPinPE0::Pin()
{
	return GPIO_PIN_0;
}

std::string bsp::GpioPinPE0::PinName() const
{
	return "PE0";
}

void bsp::GpioPinPE0::Open(bsp::IGpioPinOptions const &options)
{
	if (_is_open)
	{
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
	init.Pin = Pin();
	HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPE0::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
