#pragma once
#include <bsp-interface/di/gpio.h>
#include <hal.h>

namespace bsp
{
    class GpioPin :
        public bsp::IGpioPin
    {
    public:
        virtual ~GpioPin() = default;

        virtual GPIO_TypeDef *Port() = 0;
        virtual uint32_t Pin() = 0;

        bool ReadPin() override;
        void WritePin(bool value) override;
        void TogglePin() override;

        /// @brief 设置中断回调函数。
        /// @warning 只有当前引脚处于关闭状态才能设置。
        /// @param callback
        void RegisterInterruptCallback(std::function<void()> callback) override;

        /// @brief 取消注册此引脚的中断回调函数。
        void UnregisterInterruptCallback() override;
    };
} // namespace bsp
