#include "GpioPinPE7.h"
#include <GpioPinOptions.h>
#include <hal.h>

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

void bsp::GpioPinPE7::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPE7::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
