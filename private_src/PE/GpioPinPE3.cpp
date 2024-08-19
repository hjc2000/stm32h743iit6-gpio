#include "GpioPinPE3.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE3::Port()
{
	return GPIOE;
}

uint32_t bsp::GpioPinPE3::Pin()
{
	return GPIO_PIN_3;
}

std::string bsp::GpioPinPE3::PinName() const
{
	return "PE3";
}

void bsp::GpioPinPE3::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPE3::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
