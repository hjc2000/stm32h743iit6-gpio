#include "GpioPinPA9.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPA9::Port()
{
	return GPIOA;
}

uint32_t bsp::GpioPinPA9::Pin()
{
	return GPIO_PIN_9;
}

std::string bsp::GpioPinPA9::PinName() const
{
	return "PA9";
}

void bsp::GpioPinPA9::Open(bsp::IGpioPinOptions const &options)
{
	if (_is_open)
	{
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<bsp::GpioPinOptions const &>(options);
	init.Pin = Pin();
	HAL_GPIO_Init(Port(), &init);
}

void bsp::GpioPinPA9::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
