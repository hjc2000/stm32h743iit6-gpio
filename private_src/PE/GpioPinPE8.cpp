#include "GpioPinPE8.h"
#include <GpioPinOptions.h>
#include <hal.h>

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
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
	init.Pin = Pin();
	HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPE8::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
