# ESP32-C3 Deep Sleep Implementation
#### Client Name: Nikolas Bauhaus


## Project Requirements
Implement a wake-on-movement functionality to an existing esp32-based open source project, the open source project that needs to be expanded is shared under docs. Device should sleep after 5 minutes of little-to-no-movement scenario, and wake upon movement. Upon wake up, the charge indicator (red LED on XIAO esp32c3) should flash three times. Components are: 
- Xiao ESP32-C3 for MCU
- BMI270 breakout board for IMU.
- LSM6DSV16X based custom schematic for IMU. [Schematic PDF](https://github.com/eSpark-Consultants/nikolasbauhaus-deepsleep-fw/blob/main/docs/Schematic/ESP32-C3-MINI-1U_LSM6DSV16XTR_Board_v1.pdf) pushed to docs.
- Platformio for ESP32

 
## Step 1 : Install the ESP-IDF(v5.2.1) Extension for VS Code

#### 1- Open Visual Studio Code (VS Code):

Launch VS Code on your computer.

#### 2- Go to the Extensions View:

Press Ctrl+Shift+X (Cmd+Shift+X on macOS) to open the Extensions view, or click on the Extensions icon located in the left sidebar of VS Code.

#### 3- Search for ESP-IDF:

In the Extensions search bar, type ESP-IDF.

#### 4- Install the ESP-IDF Extension:

Find ESP-IDF by Espressif Systems and click Install.

## Step 2 : Install ESP-IDF Tools.

#### 1- Open the Command Palette:

Press Ctrl+Shift+P (Cmd+Shift+P on macOS) to open the Command Palette.

#### 2- Run ESP-IDF: Configure ESP-IDF:

1- Type ESP-IDF: Configure ESP-IDF extension and select it from the list.

2- This command will guide you through the process of downloading and installing the required tools.

![image](https://github.com/user-attachments/assets/2a091adc-d428-4892-8b4e-72ad1948321a)

#### 3- Select the Installation Path:

When prompted, select a directory where the ESP-IDF tools will be installed (e.g., C:\esp-idf or a directory of your choice).

#### 4- Install Dependencies:

The extension will ask to install Python dependencies and other necessary tools.
Follow the prompts to install Python packages, Git, CMake, Ninja, and other dependencies required for ESP-IDF development

#### 5- Verify the Installation:

Once the installation is complete, you can verify that everything is set up correctly by opening a new terminal in VS Code and typing

`idf.py --version`

## Step 3 : Installation Of PlatformIO IDE(v3.3.3).

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

## Step 4 : Compilation Process.

1- Navigate to the main.cpp File.

After successfully adding your code, open the main.cpp file in your project. Click on tick to compile, it will take some time for compilation. 

![image](https://github.com/user-attachments/assets/c3b77af8-1007-4821-9aee-e3fd9fed27d8)

2- Successfully Compile.

![image](https://github.com/user-attachments/assets/23aedbdc-63df-49e2-a277-64ef02826775)

## Step 5 : Flashing.
Click on arrow to flash.

![image](https://github.com/user-attachments/assets/9f7b07cd-b1ba-4945-a0c9-c869ebddb43d)






 










