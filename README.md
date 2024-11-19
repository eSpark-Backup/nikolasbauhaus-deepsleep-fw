# ESP32-C3 Deep Sleep Implementation
#### Client Name: Nikolas Bauhaus


## Project Requirements
Implement a wake-on-movement functionality to an existing esp32-based open source project, the open source project that needs to be expanded is shared under docs. Device should sleep after 5 minutes of little-to-no-movement scenario, and wake upon movement. Upon wake up, the charge indicator (red LED on XIAO esp32c3) should flash three times. Components are: 
- Xiao ESP32-C3 for MCU
- BMI270/LSM6DSV16X for IMU.
- Platformio for ESP32

-------------------------------------------------------------------------------------------------

BMI270 IMU driver modified to configure interrupt pin.

D3 is defined as MPI270 IMU interrupt pin which is RTC wakeup capable

D2 is defined as external LED which will blink with desired pattern

-------------------------------------------------------------------------------------------------

## Step 1 : Installation Of PlatformIO IDE.

Install PlatformIO IDE from the extension of VS Code. PlatformIO IDE will automatically install in VS Code and may prompt you to reload or restart vs-code after installation.

#### 1- Launch PlatformIO IDE
Once the installation is complete, you can open PlatformIO IDE from within Visual Studio Code:

#### 2- Open PlatformIO Home:

Press Ctrl+Shift+P (or Cmd+Shift+P on macOS) to open the Command Palette.
Type PlatformIO: Home and select it.
Alternatively, you can also open the PlatformIO Home by clicking the PlatformIO icon (alien head) in the left sidebar of VS Code.

### Set Up Your PlatformIO Project
Once PlatformIO is installed and running, you can set up your project:

#### 1- Open the Project:
In PlatformIO Home, click on Open Project and select `Firmware` folder.
![image](https://github.com/user-attachments/assets/9c639124-fd57-44d6-9b5c-4d8c81e8d68c)

#### 2- Update the board in `platformio.ini` file. 
```ini
[env:esp32c3]
platform = espressif32 @ 6.7.0
platform_packages =
  framework-arduinoespressif32 @ https://github.com/espressif/arduino-esp32.git#3.0.1
  framework-arduinoespressif32-libs @ https://github.com/espressif/arduino-esp32/releases/download/3.0.1/esp32-arduino-libs-3.0.1.zip
build_flags =
  ${env.build_flags}
  -DESP32C3
board = seeed_xiao_esp32c3
upload_speed = 921600
```

After update Platformio automatically start to configure the new board.
![image](https://github.com/user-attachments/assets/37ff8b0a-50f7-470c-b2e5-b00a046590e7)

## Step 2 : Compilation Process.

1- Navigate to the main.cpp File.

After successfully adding your code, open the main.cpp file in your project. Click on tick to compile, it will take some time for compilation. 

![image](https://github.com/user-attachments/assets/c3b77af8-1007-4821-9aee-e3fd9fed27d8)

2- Successfully Compile.

![image](https://github.com/user-attachments/assets/23aedbdc-63df-49e2-a277-64ef02826775)

## Step 5 : Flashing.
Click on arrow to flash.

![image](https://github.com/user-attachments/assets/9f7b07cd-b1ba-4945-a0c9-c869ebddb43d)






 










