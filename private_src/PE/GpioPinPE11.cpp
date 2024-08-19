#include "GpioPinPE11.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE11::Port()
{
	return GPIOE;
}

uint32_t bsp::GpioPinPE11::Pin()
{
	return GPIO_PIN_11;
}

std::string bsp::GpioPinPE11::PinName() const
{
	return "PE11";
}

void bsp::GpioPinPE11::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPE11::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
