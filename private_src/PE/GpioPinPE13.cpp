#include "GpioPinPE13.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE13::Port()
{
	return GPIOE;
}

uint32_t bsp::GpioPinPE13::Pin()
{
	return GPIO_PIN_13;
}

std::string bsp::GpioPinPE13::PinName() const
{
	return "PE13";
}

void bsp::GpioPinPE13::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPE13::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
