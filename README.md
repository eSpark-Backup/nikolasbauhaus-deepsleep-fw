# ESP32-C3 Deep Sleep Implementation
#### Client Name: Nikolas Bauhaus


## Project Requirements
Implement a wake-on-movement functionality to an existing esp32-based open source project, the open source project that needs to be expanded is shared under docs. Device should sleep after 5 minutes of little-to-no-movement scenario, and wake upon movement. Upon wake up, the charge indicator (red LED on XIAO esp32c3) should flash three times. Components are: 
- Xiao ESP32-C3 for MCU
- BMI270/LSM6DSV16X for IMU.

 
### Installation Of ESP-IDF
Install ESP-IDF from the extension of VS Code and configure.

### Installation Of PlatformIO IDE.
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
In PlatformIO Home, click on Open Project `SlimeVR-Tracker-ESP-main`.
![image](https://github.com/user-attachments/assets/4d2d811d-372e-4124-b3c3-b1266c4f46b7)

#### 2- Update the board in `platformio.ini` file. 
```ini
[env:seeed_xiao_esp32c3]
platform = espressif32
board = seeed_xiao_esp32c3
upload_speed = 921600
```
After update Platformio automatically start to configure the new board.  
![image](https://github.com/user-attachments/assets/e0036caa-d62b-4b1e-8e27-ebeeb5eb51ec)

### Compilation Process.

1- Navigate to the main.cpp File.

After successfully adding your code, open the main.cpp file in your project

![image](https://github.com/user-attachments/assets/c3b77af8-1007-4821-9aee-e3fd9fed27d8)

2- Configure the Build:

A pop-up screen will appear. Click on the  ` Configure CMake Options Visibility ` option to proceed compilation.

![image](https://github.com/user-attachments/assets/8afc44cc-2824-4448-a7a5-bfeb5d01a479)

3- Successfully Compile.

![image](https://github.com/user-attachments/assets/23aedbdc-63df-49e2-a277-64ef02826775)










