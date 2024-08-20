#pragma once
#include <bsp-interface/gpio/IGpioPinOptions.h>
#include <hal.h>

namespace bsp
{
    class GpioPinOptions final :
        public bsp::IGpioPinOptions
    {
    private:
        GPIO_InitTypeDef _hal_gpio_init;
        bsp::IGpioPinDirection _direction{};
        bsp::IGpioPinWorkMode _work_mode{};
        bsp::IGpioPinTriggerEdge _trigger_edge{};
        bsp::IGpioPinDriver _driver{};
        std::string _af_mode;

#pragma region 初始化为各种模式
        /// @brief 初始化为通用输入输出模式。
        /// @param o
        void InitAsGpioMode(GPIO_InitTypeDef &o) const;

        /// @brief 初始化为复用功能。
        /// @param o
        void InitAsAlternateFunctionMode(GPIO_InitTypeDef &o) const;

        /// @brief 初始化为事件功能。
        /// @param o
        void InitAsEventMode(GPIO_InitTypeDef &o) const;

        /// @brief 初始化为模拟功能。
        /// @param o
        void InitAsAnalogMode(GPIO_InitTypeDef &o) const;
#pragma endregion

    public:
        operator GPIO_InitTypeDef() const;

#pragma region IGpioPinOptions
        /// @brief 方向。
        /// @return
        bsp::IGpioPinDirection Direction() const override;
        void SetDirection(bsp::IGpioPinDirection value) override;

        /// @brief 引脚工作模式。
        /// @return
        bsp::IGpioPinWorkMode WorkMode() const override;
        void SetWorkMode(bsp::IGpioPinWorkMode value) override;

        /// @brief 触发边沿。
        /// @return
        bsp::IGpioPinTriggerEdge TriggerEdge() const override;
        void SetTriggerEdge(bsp::IGpioPinTriggerEdge value) override;

        /// @brief 引脚上下拉模式。
        /// @return
        bsp::IGpioPinPullMode PullMode() const override;
        void SetPullMode(bsp::IGpioPinPullMode value) override;

        /// @brief 引脚驱动模式。
        /// @note 引脚方向为输出时才有效。
        /// @return
        bsp::IGpioPinDriver Driver() const override;
        void SetDriver(bsp::IGpioPinDriver value) override;

        /// @brief 引脚速度等级。等级越高速度越快。
        /// @note 有的平台引脚支持设置速度等级。不支持的平台忽略就好。
        /// @return
        int SpeedLevel() const override;
        void SetSpeedLevel(int value) override;

        /// @brief 复用功能。
        /// @return
        std::string AlternateFunction() const override;

        /// @brief 设置复用功能。
        /// @note 复用功能是非常复杂的，各个型号单片机都不一样，所以采用字符串。
        /// @note 假设某个单片机的一个引脚的复用功能有：uart1, timer1_compare_output 等。
        /// 这种名称是与具体型号高度相关的，所以本库无法提供一个枚举来列举这些情况。
        /// @param value
        void SetAlternateFunction(std::string value) override;
#pragma endregion
    };
} // namespace bsp
