/*
    SlimeVR Code is placed under the MIT license
    Copyright (c) 2024 Gorbit99 & SlimeVR Contributors

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#pragma once

#include <cstdint>
#include <array>
#include <algorithm>

#include "lsm6ds-common.h"
#include "lsm6dsvfw.h"

namespace SlimeVR::Sensors::SoftFusion::Drivers
{

#define BV(x, y)        (x & 0x01) << y
#define BV2(x, y)       (x & 0x03) << y

#define INT2_on_INT1(x)         (BV(x, 4))
#define DRDY_MASK(x)            (BV(x, 3))
#define INT2_DRDY_TEMP(x)       (BV(x, 2))
#define DRDY_PULSED(x)          (BV(x, 1))
#define INT2_IN_LH(x)           (BV(x, 0))

#define INT_SLEEP_CHANGE(x)        (BV(x, 7))
#define INT_SINGLE_TAP(x)          (BV(x, 6))
#define INT_WU(x)                  (BV(x, 5))
#define INT_FF(x)                  (BV(x, 4))
#define INT_DOUBLE_TAP(x)          (BV(x, 3))
#define INT_6D(x)                  (BV(x, 2))
#define INT_EMB_FUNC(x)            (BV(x, 1))
#define INT1_SHUB(x)               (BV(x, 0))
#define INT2_TIMESTAMP(x)          (BV(x, 0))

#define INTERRUPTS_ENABLE(x)       (BV(x, 7))
#define TIMESTAMP_EN(x)            (BV(x, 6))
#define DIS_RST_LIR_ALL_INT(x)     (BV(x, 3))
#define INACT_EN_(x)               (BV2(x, 0))


// Driver uses acceleration range at 8g
// and gyroscope range at 1000dps
// Gyroscope ODR = 480Hz, accel ODR = 120Hz

template <typename I2CImpl>
struct LSM6DSV : LSM6DSOutputHandler<I2CImpl>
{
    static constexpr uint8_t Address = 0x6a;
    static constexpr auto Name = "LSM6DSV";
    static constexpr auto Type = ImuID::LSM6DSV;

    static constexpr float GyrFreq = 480;
    static constexpr float AccFreq = 120;
    static constexpr float MagFreq = 120;

    static constexpr float GyrTs=1.0/GyrFreq;
    static constexpr float AccTs=1.0/AccFreq;
    static constexpr float MagTs=1.0/MagFreq;

    static constexpr float GyroSensitivity = 1000 / 35.0f;
    static constexpr float AccelSensitivity = 1000 / 0.244f;

    using LSM6DSOutputHandler<I2CImpl>::i2c;

    struct Regs {
        struct WhoAmI {
            static constexpr uint8_t reg = 0x0f;
            static constexpr uint8_t value = 0x70;
        };
        static constexpr uint8_t OutTemp = 0x20;
        struct FUNCCFGACCESS {
            static constexpr uint8_t reg = 0x01;
            static constexpr uint8_t value = (0x00); // default = 0x00
        };
        struct HAODRCFG {
            static constexpr uint8_t reg = 0x62;
            static constexpr uint8_t value = (0b00); //1st ODR table
        };
        struct Ctrl1XLODR {
            static constexpr uint8_t reg = 0x10;
            // static constexpr uint8_t value = (0b0010110); //120Hz, HAODR
            static constexpr uint8_t value = 0x50; //120Hz, HAODR
        };
        struct Ctrl2GODR {
            static constexpr uint8_t reg = 0x11;
            static constexpr uint8_t value = (0b0011000); //480Hz, HAODR
        };
        struct Ctrl3C {
            static constexpr uint8_t reg = 0x12;
            static constexpr uint8_t valueSwReset = 1;
            static constexpr uint8_t value = (1 << 6) | (1 << 2); //BDU = 1, IF_INC = 1
        };
        struct Int1Ctrl {
            static constexpr uint8_t reg = 0x0D;
            static constexpr uint8_t value = 0; //default = 0x00
        };
        struct Int2Ctrl {
            static constexpr uint8_t reg = 0x0E;
            static constexpr uint8_t value = (1 << 7); //INT2_EMB_FUNC_ENDOP = 1
        };
        struct Ctrl4C {
            static constexpr uint8_t reg = 0x13;
            static constexpr uint8_t value = INT2_on_INT1(1) | DRDY_MASK(0) | INT2_DRDY_TEMP(0) | DRDY_PULSED(1) | INT2_IN_LH(0); //INT2_on_INT1 = 1, DRDY_MASK = disabled, DRDY_PULSED = pulsed, INT2_IN_LH = Active_low
        };
        struct MD1CFG {
            static constexpr uint8_t reg = 0x5E;
            static constexpr uint8_t value = ( INT_SLEEP_CHANGE(0) | INT_SINGLE_TAP(0) | INT_WU(1)
                                             | INT_FF(0) | INT_DOUBLE_TAP(0) | INT_6D(0) | INT_EMB_FUNC(0)
                                             | INT1_SHUB(0) );
        };
        struct MD2CFG {
            static constexpr uint8_t reg = 0x5F;
            static constexpr uint8_t value = ( INT_SLEEP_CHANGE(0) | INT_SINGLE_TAP(0) | INT_WU(0)
                                             | INT_FF(0) | INT_DOUBLE_TAP(0) | INT_6D(0) | INT_EMB_FUNC(1)
                                             | INT2_TIMESTAMP(0) );
        };
        struct FUNCENABLE {
            static constexpr uint8_t reg = 0x50;
            static constexpr uint8_t value = INTERRUPTS_ENABLE(1) | TIMESTAMP_EN(0) | DIS_RST_LIR_ALL_INT(0) | INACT_EN_(0);
        };
        struct WAKEUPDUR {
            static constexpr uint8_t reg = 0x5C;
            static constexpr uint8_t value = 0x02;
        };
        struct WAKEUPTHR {
            static constexpr uint8_t reg = 0x5B;
            static constexpr uint8_t value = 0x02;
        };
        struct Ctrl10C {
            static constexpr uint8_t reg = 0x19;
            static constexpr uint8_t value = 0;//(1 << 6); //EMB_FUNC_DEBUG = enabled
        };
        struct AllIntSrc {
            static constexpr uint8_t reg = 0x1D;
            static constexpr uint8_t value = (1 << 7); //EMB_FUNC_IA = enabled
        };
        struct WakeUpSrc {
            static constexpr uint8_t reg = 0x45;
            static constexpr uint8_t value = 0; //Read-only register
        };
        struct Ctrl6GFS {
            static constexpr uint8_t reg = 0x15;
            static constexpr uint8_t value = (0b0011); //1000dps
        };
        struct Ctrl8XLFS {
            static constexpr uint8_t reg = 0x17;
            // static constexpr uint8_t value = (0b10); //8g
            static constexpr uint8_t value = (0b00); //8g
        };
        struct FifoCtrl3BDR {
            static constexpr uint8_t reg = 0x09;
            static constexpr uint8_t value = (0b1000) | (0b1000 << 4); //gyro and accel batched at 480Hz
        };
        struct FifoCtrl4Mode {
            static constexpr uint8_t reg = 0x0a;
            static constexpr uint8_t value = (0b110); //continuous mode
        };

        static constexpr uint8_t FifoStatus = 0x1b;
        static constexpr uint8_t FifoData = 0x78;
    };

    LSM6DSV(I2CImpl i2c, SlimeVR::Logging::Logger &logger)
        : LSM6DSOutputHandler<I2CImpl>(i2c, logger) {
    }

    void initializeEmbeddedFunctionInterrupt()
    {
        ucf_line_t* programPointer = (ucf_line_t *)SlimeVR::Sensors::SoftFusion::Drivers::lsm6dsv16x_activity_recognition_fw;
        int32_t programLength = sizeof(lsm6dsv16x_activity_recognition_fw) / sizeof(ucf_line_t);

        for (int32_t LineCounter = 0; LineCounter < programLength; LineCounter++)
        {
            if(!i2c.writeReg(programPointer[LineCounter].address, programPointer[LineCounter].data))
            {
                while(1)
                {
                    /* drive addressable led here for error indication */
                    neopixelWrite(LED_PIN, 255, 0, 0);
                    delay(200);
                    neopixelWrite(LED_PIN, 0, 0, 0);
                    delay(200);
                }
            }
        }
        // indicate, write successfull
        neopixelWrite(LED_PIN, 0, 0, 255);
        delay(200);
        neopixelWrite(LED_PIN, 0, 0, 0);

        i2c.writeReg(Regs::FUNCCFGACCESS::reg, Regs::FUNCCFGACCESS::value);
        i2c.writeReg(Regs::Ctrl4C::reg, Regs::Ctrl4C::value);
    }

    bool initialize()
    {
        // perform initialization step
        i2c.writeReg(Regs::Ctrl3C::reg, Regs::Ctrl3C::valueSwReset);
        delay(20);
        i2c.writeReg(Regs::HAODRCFG::reg, Regs::HAODRCFG::value);
        i2c.writeReg(Regs::Ctrl1XLODR::reg, Regs::Ctrl1XLODR::value);
        i2c.writeReg(Regs::Ctrl2GODR::reg, Regs::Ctrl2GODR::value);
        i2c.writeReg(Regs::Ctrl3C::reg, Regs::Ctrl3C::value);
        i2c.writeReg(Regs::Ctrl6GFS::reg, Regs::Ctrl6GFS::value);
        i2c.writeReg(Regs::Ctrl8XLFS::reg, Regs::Ctrl8XLFS::value);
        i2c.writeReg(Regs::FifoCtrl3BDR::reg, Regs::FifoCtrl3BDR::value);
        i2c.writeReg(Regs::FifoCtrl4Mode::reg, Regs::FifoCtrl4Mode::value);

        // initializeEmbeddedFunctionInterrupt();
        
        i2c.writeReg(Regs::WAKEUPDUR::reg, Regs::WAKEUPDUR::value);
        i2c.writeReg(Regs::WAKEUPTHR::reg, Regs::WAKEUPTHR::value);
        i2c.writeReg(Regs::FUNCENABLE::reg, Regs::FUNCENABLE::value);
        i2c.writeReg(Regs::MD1CFG::reg, Regs::MD1CFG::value);
        return true;
    }

    float getDirectTemp() const
    {
        return LSM6DSOutputHandler<I2CImpl>::template getDirectTemp<Regs>();
    }

    template <typename AccelCall, typename GyroCall>
    void bulkRead(AccelCall &&processAccelSample, GyroCall &&processGyroSample) {
        LSM6DSOutputHandler<I2CImpl>::template bulkRead<AccelCall, GyroCall, Regs>(processAccelSample, processGyroSample, GyrTs, AccTs);
    }

};

} // namespace