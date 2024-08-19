#include "GpioPinPA10.h"
#include <GpioPinOptions.h>
#include <hal.h>

GPIO_TypeDef *bsp::GpioPinPA10::Port()
{
	return GPIOA;
}

uint32_t bsp::GpioPinPA10::Pin()
{
	return GPIO_PIN_10;
}

std::string bsp::GpioPinPA10::PinName() const
{
	return "PA10";
}

void bsp::GpioPinPA10::Open(bsp::IGpioPinOptions const &options)
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

void bsp::GpioPinPA10::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
