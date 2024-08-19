#include "GpioPinPE14.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPE14::Port()
{
	return GPIOE;
}

uint32_t bsp::GpioPinPE14::Pin()
{
	return GPIO_PIN_14;
}

std::string bsp::GpioPinPE14::PinName() const
{
	return "PE14";
}

void bsp::GpioPinPE14::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPE14::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
