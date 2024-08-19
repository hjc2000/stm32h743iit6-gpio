#include "GpioPinPE1.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE1::Port()
{
	return GPIOE;
}

uint32_t bsp::GpioPinPE1::Pin()
{
	return GPIO_PIN_1;
}

std::string bsp::GpioPinPE1::PinName() const
{
	return "PE1";
}

void bsp::GpioPinPE1::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPE1::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
