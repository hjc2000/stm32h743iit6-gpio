#pragma once
#include <array>
#include <base/container/StdContainerEnumerable.h>
#include <base/RentedPtrFactory.h>
#include <GpioPin.h>

namespace bsp
{
    class GpioPinPE8 final :
        public bsp::GpioPin
    {
    private:
        GpioPinPE8() = default;

        bool _is_open = false;

        std::array<std::string, 1> _supported_alternate_functions{"gpio"};
        base::StdContainerEnumerable<std::string, std::array<std::string, 1>>
            _supported_alternate_functions_enumerable{
                base::RentedPtrFactory::Create(&_supported_alternate_functions),
            };

    public:
        static GpioPinPE8 &Instance()
        {
            static GpioPinPE8 o;
            return o;
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
            return _supported_alternate_functions_enumerable;
        }

        /// @brief 指示此引脚是否已经打开。
        /// @return
        bool IsOpen() override
        {
            return _is_open;
        }

        void Open(bsp::IGpioPinOptions const &options) override;
        void Close() override;
    };
} // namespace bsp
