#pragma once
#include <base/container/Array.h>
#include <base/RentedPtrFactory.h>
#include <GpioPin.h>
#include <hal.h>

namespace bsp
{
    class GpioPinPB1 final :
        public bsp::GpioPin
    {
    private:
        GpioPinPB1() = default;

        base::Array<std::string, 1> _supported_alternate_functions{"timer3"};

    public:
        static_function GpioPinPB1 &Instance()
        {
            class Getter :
                public bsp::TaskSingletonGetter<GpioPinPB1>
            {
            public:
                std::unique_ptr<GpioPinPB1> Create() override
                {
                    return std::unique_ptr<GpioPinPB1>{new GpioPinPB1{}};
                }
            };

            Getter o;
            return o.Instance();
        }

        GPIO_TypeDef *Port() override;
        uint32_t Pin() override;

        /// @brief 引脚名称
        /// @return
        std::string PinName() const override;

        /// @brief 支持的复用功能。
        /// @note 复用功能是非常复杂的，各个型号单片机都不一样，所以采用字符串。
        /// @note 假设某个单片机的一个引脚的复用功能有：uart1, timer1_compare_output 等。
        /// 这种名称是与具体型号高度相关的，所以本库无法提供一个枚举来列举这些情况。
        /// @return
        base::IEnumerable<std::string> &SupportedAlternateFunctions() override
        {
            return _supported_alternate_functions;
        }

        /// @brief 将引脚打开为复用功能。
        /// @param function_name 复用功能名称。
        /// @param pull_mode 拉模式。
        /// @param driver_mode 驱动模式。
        void OpenAsAlternateFunctionMode(std::string function_name,
                                         bsp::IGpioPinPullMode pull_mode,
                                         bsp::IGpioPinDriver driver_mode) override;
    };
} // namespace bsp
