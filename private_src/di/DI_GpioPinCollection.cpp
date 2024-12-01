#include <base/container/Dictionary.h>
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>
#include <GpioPinOptions.h>

#pragma region PA
#include <PA/GpioPinPA0.h>
#include <PA/GpioPinPA1.h>
#include <PA/GpioPinPA10.h>
#include <PA/GpioPinPA9.h>
#pragma endregion

#pragma region PB
#include <PB/GpioPinPB0.h>
#include <PB/GpioPinPB1.h>
#include <PB/GpioPinPB5.h>
#pragma endregion

#pragma region PC
#include <PC/GpioPinPC0.h>
#include <PC/GpioPinPC1.h>
#include <PC/GpioPinPC2.h>
#include <PC/GpioPinPC3.h>
#include <PC/GpioPinPC5.h>
#pragma endregion

#pragma region PD
#include <PD/GpioPinPD0.h>
#include <PD/GpioPinPD1.h>
#include <PD/GpioPinPD10.h>
#include <PD/GpioPinPD11.h>
#include <PD/GpioPinPD14.h>
#include <PD/GpioPinPD15.h>
#include <PD/GpioPinPD4.h>
#include <PD/GpioPinPD5.h>
#include <PD/GpioPinPD8.h>
#include <PD/GpioPinPD9.h>
#pragma endregion

#pragma region PE
#include <PE/GpioPinPE0.h>
#include <PE/GpioPinPE1.h>
#include <PE/GpioPinPE10.h>
#include <PE/GpioPinPE11.h>
#include <PE/GpioPinPE12.h>
#include <PE/GpioPinPE13.h>
#include <PE/GpioPinPE14.h>
#include <PE/GpioPinPE15.h>
#include <PE/GpioPinPE2.h>
#include <PE/GpioPinPE3.h>
#include <PE/GpioPinPE4.h>
#include <PE/GpioPinPE5.h>
#include <PE/GpioPinPE7.h>
#include <PE/GpioPinPE8.h>
#include <PE/GpioPinPE9.h>
#pragma endregion

#pragma region PF
#include <PF/GpioPinPF0.h>
#include <PF/GpioPinPF1.h>
#pragma endregion

#pragma region PG
#include <PG/GpioPinPG0.h>
#include <PG/GpioPinPG12.h>
#pragma endregion

#pragma region PH
#include <PH/GpioPinPH2.h>
#include <PH/GpioPinPH3.h>
#pragma endregion

namespace
{
    class Initializer
    {
    private:
        void AddPin(bsp::IGpioPin &pin)
        {
            _dic.Add(pin.PinName(), &pin);
        }

    public:
        Initializer()
        {
#pragma region PA
            AddPin(bsp::GpioPinPA0::Instance());
            AddPin(bsp::GpioPinPA9::Instance());
            AddPin(bsp::GpioPinPA10::Instance());
#pragma endregion

#pragma region PB
            AddPin(bsp::GpioPinPB0::Instance());
            AddPin(bsp::GpioPinPB1::Instance());
            AddPin(bsp::GpioPinPB5::Instance());
#pragma endregion

#pragma region PC
            AddPin(bsp::GpioPinPC0::Instance());
            AddPin(bsp::GpioPinPC1::Instance());
            AddPin(bsp::GpioPinPC2::Instance());
            AddPin(bsp::GpioPinPC3::Instance());
            AddPin(bsp::GpioPinPC5::Instance());
#pragma endregion

#pragma region PD
            AddPin(bsp::GpioPinPD0::Instance());
            AddPin(bsp::GpioPinPD1::Instance());
            AddPin(bsp::GpioPinPD4::Instance());
            AddPin(bsp::GpioPinPD5::Instance());
            AddPin(bsp::GpioPinPD8::Instance());
            AddPin(bsp::GpioPinPD9::Instance());
            AddPin(bsp::GpioPinPD10::Instance());
            AddPin(bsp::GpioPinPD11::Instance());
            AddPin(bsp::GpioPinPD14::Instance());
            AddPin(bsp::GpioPinPD15::Instance());
#pragma endregion

#pragma region PE
            AddPin(bsp::GpioPinPE0::Instance());
            AddPin(bsp::GpioPinPE1::Instance());
            AddPin(bsp::GpioPinPE2::Instance());
            AddPin(bsp::GpioPinPE3::Instance());
            AddPin(bsp::GpioPinPE4::Instance());
            AddPin(bsp::GpioPinPE5::Instance());
            AddPin(bsp::GpioPinPE7::Instance());
            AddPin(bsp::GpioPinPE8::Instance());
            AddPin(bsp::GpioPinPE9::Instance());
            AddPin(bsp::GpioPinPE10::Instance());
            AddPin(bsp::GpioPinPE11::Instance());
            AddPin(bsp::GpioPinPE12::Instance());
            AddPin(bsp::GpioPinPE13::Instance());
            AddPin(bsp::GpioPinPE14::Instance());
            AddPin(bsp::GpioPinPE15::Instance());
#pragma endregion

#pragma region PF
            AddPin(bsp::GpioPinPF0::Instance());
            AddPin(bsp::GpioPinPF1::Instance());
#pragma endregion

#pragma region PG
            AddPin(bsp::GpioPinPG0::Instance());
            AddPin(bsp::GpioPinPG12::Instance());
#pragma endregion

#pragma region PH
            AddPin(bsp::GpioPinPH2::Instance());
            AddPin(bsp::GpioPinPH3::Instance());
#pragma endregion
        }

        base::Dictionary<std::string, bsp::IGpioPin *> _dic{};
    };

#pragma region Getter

    class Getter :
        public base::SingletonGetter<Initializer>
    {
    public:
        std::unique_ptr<Initializer> Create() override
        {
            return std::unique_ptr<Initializer>{new Initializer{}};
        }

        void Lock() override
        {
            DI_InterruptSwitch().DisableGlobalInterrupt();
        }

        void Unlock() override
        {
            DI_InterruptSwitch().EnableGlobalInterrupt();
        }
    };

#pragma endregion
} // namespace

base::IDictionary<std::string, bsp::IGpioPin *> const &DI_GpioPinCollection()
{
    Getter g;
    return g.Instance()._dic;
}
