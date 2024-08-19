#include <GpioPinOptions.h>
#include <bsp-interface/di.h>

std::shared_ptr<bsp::IGpioPinOptions> DICreate_GpioPinOptions()
{
	return std::shared_ptr<bsp::IGpioPinOptions>{new bsp::GpioPinOptions{}};
}
