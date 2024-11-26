/*
    SlimeVR Code is placed under the MIT license
    Copyright (c) 2021 Eiren Rain

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
// ================================================
// See docs for configuration options and examples:
// https://docs.slimevr.dev/firmware/configuring-project.html#2-configuring-definesh
// ================================================

// Set parameters of IMU and board used
#define IMU IMU_LSM6DSV
#define SECOND_IMU IMU
#define BOARD BOARD_XIAO_ESP32C3
#define IMU_ROTATION DEG_270
#define SECOND_IMU_ROTATION DEG_270

#define PRIMARY_IMU_OPTIONAL false
#define SECONDARY_IMU_OPTIONAL true


#define SECOND_TO_MILLIS(x)   (x*1000)
#define MINUTE_TO_SECOND(x)   (x*60)
#define MINUTE_TO_MILLIS(x)   (MINUTE_TO_SECOND(x)*1000)

// #define DEEP_SLEEP_THRESHOLD   SECOND_TO_MILLIS(5)    // if threashold time is defined in secs
#define DEEP_SLEEP_THRESHOLD   MINUTE_TO_MILLIS(5)    // if threashold time is defined in mins

// LED blinking pattern on wakeup from deep sleep
//                            timeon,              timeoff,             no of repetitions)
#define LED_PATTERN           SECOND_TO_MILLIS(1), SECOND_TO_MILLIS(1), 3

// #if (IMU == IMU_BMI270)
// Enable or disable any motion detection feature
#define ANY_MOTION_DETECT   1
// Defines number of consecutive data points for which the threshold condition must be respected, for interrupt assertion.
// It is expressed in 50Hz samples (20ms). Range is 0-163secs
#define MOTION_DURATION     0x05    // default 0x5  (100ms)         (max 13-bit value)
// Enable/Disable any motion detection on axis. 1 is enable, 0 is disable
#define SELECT_X_AXIS   1
#define SELECT_Y_AXIS   1
#define SELECT_Z_AXIS   1
// Slope threshold value for any motion detection. Range is 0-1g
#define SLOPE_THRESHOLD     0xAA    // default 0xAA  (83mg)         (max 11-bit value)
// Enabling bits for output into the status register bits.
// 0x00    disable   Output of feature not assigned to any interrupt bits 0..7 of INT_STATUS_0 and INT1/2_MAP_FEAT
// 0x01    BIT_0     Output assigned to bit-0
// 0x02    BIT_1     Output assigned to bit-1
// 0x03    BIT_2     Output assigned to bit-2
// 0x04    BIT_3     Output assigned to bit-3
// 0x05    BIT_4     Output assigned to bit-4
// 0x06    BIT_5     Output assigned to bit-5
// 0x07    BIT_6     Output assigned to bit-6
// 0x08    BIT_7     Output assigned to bit-7
#define OUTPUT_CONFIG       0x07    // default 0x07  (BIT_6)        (max 4-bit value)
// #endif   // (IMU == IMU_BMI270)

#define MAX_IMU_COUNT 1

// Axis mapping example
/*
#include "sensors/axisremap.h"
#define BMI160_QMC_REMAP AXIS_REMAP_BUILD(AXIS_REMAP_USE_Y, AXIS_REMAP_USE_XN, AXIS_REMAP_USE_Z, \
                                       AXIS_REMAP_USE_YN, AXIS_REMAP_USE_X, AXIS_REMAP_USE_Z)

IMU_DESC_ENTRY(IMU_BMP160, PRIMARY_IMU_ADDRESS_ONE, IMU_ROTATION, PIN_IMU_SCL, PIN_IMU_SDA, PRIMARY_IMU_OPTIONAL, BMI160_QMC_REMAP) \
*/

#ifndef IMU_DESC_LIST
#define IMU_DESC_LIST \
        IMU_DESC_ENTRY(IMU,        PRIMARY_IMU_ADDRESS_ONE,   IMU_ROTATION,        PIN_IMU_SCL, PIN_IMU_SDA, PRIMARY_IMU_OPTIONAL,   PIN_IMU_INT) \
        IMU_DESC_ENTRY(SECOND_IMU, SECONDARY_IMU_ADDRESS_TWO, SECOND_IMU_ROTATION, PIN_IMU_SCL, PIN_IMU_SDA, SECONDARY_IMU_OPTIONAL, PIN_IMU_INT_2)
#endif

// Battery monitoring options (comment to disable):
//   BAT_EXTERNAL for ADC pin,
//   BAT_INTERNAL for internal - can detect only low battery,
//   BAT_MCP3021 for external ADC connected over I2C
#define BATTERY_MONITOR BAT_EXTERNAL

// BAT_EXTERNAL definition override
// D1 Mini boards with ESP8266 have internal resistors. For these boards you only have to adjust BATTERY_SHIELD_RESISTANCE.
// For other boards you can now adjust the other resistor values.
// The diagram looks like this:
//   (Battery)--- [BATTERY_SHIELD_RESISTANCE] ---(INPUT_BOARD)---  [BATTERY_SHIELD_R2] ---(ESP32_INPUT)--- [BATTERY_SHIELD_R1] --- (GND)
// #define BATTERY_SHIELD_RESISTANCE 180 //130k BatteryShield, 180k SlimeVR or fill in external resistor value in kOhm
// #define BATTERY_SHIELD_R1 100 // Board voltage divider resistor Ain to GND in kOhm
// #define BATTERY_SHIELD_R2 220 // Board voltage divider resistor Ain to INPUT_BOARD in kOhm

// LED configuration:
// Configuration Priority 1 = Highest:
// 1. LED_PIN
// 2. LED_BUILTIN
//
//   LED_PIN
//     - Number or Symbol (D1,..) of the Output
//     - To turn off the LED, set LED_PIN to LED_OFF
//   LED_INVERTED
//     - false for output 3.3V on high
//     - true for pull down to GND on high

// Board-specific configurations
#if BOARD == BOARD_SLIMEVR
  #define PIN_IMU_SDA 14
  #define PIN_IMU_SCL 12
  #define PIN_IMU_INT 16
  #define PIN_IMU_INT_2 13
  #define PIN_BATTERY_LEVEL 17
  #define LED_PIN 2
  #define LED_INVERTED true
  #ifndef BATTERY_SHIELD_RESISTANCE
    #define BATTERY_SHIELD_RESISTANCE 0
  #endif
  #ifndef BATTERY_SHIELD_R1
    #define BATTERY_SHIELD_R1 10
  #endif
  #ifndef BATTERY_SHIELD_R2
    #define BATTERY_SHIELD_R2 40.2
  #endif
#elif BOARD == BOARD_SLIMEVR_LEGACY || BOARD == BOARD_SLIMEVR_DEV
  #define PIN_IMU_SDA 4
  #define PIN_IMU_SCL 5
  #define PIN_IMU_INT 10
  #define PIN_IMU_INT_2 13
  #define PIN_BATTERY_LEVEL 17
  #define LED_PIN 2
  #define LED_INVERTED true
  #ifndef BATTERY_SHIELD_RESISTANCE
    #define BATTERY_SHIELD_RESISTANCE 0
  #endif
  #ifndef BATTERY_SHIELD_R1
    #define BATTERY_SHIELD_R1 10
  #endif
  #ifndef BATTERY_SHIELD_R2
    #define BATTERY_SHIELD_R2 40.2
  #endif
#elif BOARD == BOARD_NODEMCU || BOARD == BOARD_WEMOSD1MINI
  #define PIN_IMU_SDA D2
  #define PIN_IMU_SCL D1
  #define PIN_IMU_INT D5
  #define PIN_IMU_INT_2 D6
  #define PIN_BATTERY_LEVEL A0
//  #define LED_PIN 2
//  #define LED_INVERTED true
  #ifndef BATTERY_SHIELD_RESISTANCE
    #define BATTERY_SHIELD_RESISTANCE 180
  #endif
  #ifndef BATTERY_SHIELD_R1
    #define BATTERY_SHIELD_R1 100
  #endif
  #ifndef BATTERY_SHIELD_R2
    #define BATTERY_SHIELD_R2 220
  #endif
#elif BOARD == BOARD_ESP01
  #define PIN_IMU_SDA 2
  #define PIN_IMU_SCL 0
  #define PIN_IMU_INT 255
  #define PIN_IMU_INT_2 255
  #define PIN_BATTERY_LEVEL 255
  #define LED_PIN LED_OFF
  #define LED_INVERTED false
#elif BOARD == BOARD_TTGO_TBASE
  #define PIN_IMU_SDA 5
  #define PIN_IMU_SCL 4
  #define PIN_IMU_INT 14
  #define PIN_IMU_INT_2 13
  #define PIN_BATTERY_LEVEL A0
//  #define LED_PIN 2
//  #define LED_INVERTED false
#elif BOARD == BOARD_CUSTOM
  // Define pins by the examples above
#elif BOARD == BOARD_WROOM32
  #define PIN_IMU_SDA 21
  #define PIN_IMU_SCL 22
  #define PIN_IMU_INT 23
  #define PIN_IMU_INT_2 25
  #define PIN_BATTERY_LEVEL 36
//  #define LED_PIN 2
//  #define LED_INVERTED false
#elif BOARD == BOARD_LOLIN_C3_MINI
  #define PIN_IMU_SDA 5
  #define PIN_IMU_SCL 4
  #define PIN_IMU_INT 6
  #define PIN_IMU_INT_2 8
  #define PIN_BATTERY_LEVEL 3
  #define LED_PIN 7
//  #define LED_INVERTED false
#elif BOARD == BOARD_BEETLE32C3
  #define PIN_IMU_SDA 8
  #define PIN_IMU_SCL 9
  #define PIN_IMU_INT 6
  #define PIN_IMU_INT_2 7
  #define PIN_BATTERY_LEVEL 3
  #define LED_PIN 10
  #define LED_INVERTED false
#elif BOARD == BOARD_ES32C3DEVKITM1
  #define PIN_IMU_SDA 5
  #define PIN_IMU_SCL 4
  #define PIN_IMU_INT 6
  #define PIN_IMU_INT_2 7
  #define PIN_BATTERY_LEVEL 3
  #define LED_PIN LED_OFF  // RGB LED Protocol would need to be implementetet did not brother for the test, because the board ideal for tracker ifself
//  #define LED_INVERTED false
#elif BOARD == BOARD_WEMOSWROOM02
  #define PIN_IMU_SDA 2
  #define PIN_IMU_SCL 14
  #define PIN_IMU_INT 0
  #define PIN_IMU_INT_2 4
  #define PIN_BATTERY_LEVEL A0
  #define LED_PIN 16
  #define LED_INVERTED true
#elif BOARD == BOARD_XIAO_ESP32C3
  #define PIN_IMU_SDA 3 //
  #define PIN_IMU_SCL 2 //
  #define PIN_IMU_INT 4 //     // only RTC pins can be used to wakeup from deep sleep
  #define PIN_IMU_INT_2 10 // D10
  #define LED_PIN 6 // D2
  #define LED_INVERTED false
  #define PIN_BATTERY_LEVEL 5 // 
  #ifndef BATTERY_SHIELD_RESISTANCE
    #define BATTERY_SHIELD_RESISTANCE 0
  #endif
  #ifndef BATTERY_SHIELD_R1
    #define BATTERY_SHIELD_R1 100
  #endif
  #ifndef BATTERY_SHIELD_R2
    #define BATTERY_SHIELD_R2 100
  #endif
#endif
