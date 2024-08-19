#include "GpioPinPE12.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE12::Port()
{
	return GPIOE;
}

uint32_t bsp::GpioPinPE12::Pin()
{
	return GPIO_PIN_12;
}

std::string bsp::GpioPinPE12::PinName() const
{
	return "PE12";
}

void bsp::GpioPinPE12::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPE12::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
