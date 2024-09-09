# ESP32 CAR OTA

This project is an ESP32-based web-controlled car with Over-The-Air (OTA) update capabilities using `AsyncElegantOTA`. The car can be controlled via a web interface to move forward, backward, left, and right by pressing the corresponding buttons.

## Features

- **OTA (Over-the-Air) Updates**: Allows for seamless software updates via a web interface.
- **ESP32 Web Control**: The car is controlled by a web page hosted by the ESP32 itself.
- **Motor Control**: Four GPIO pins are used to control two motors for moving the car forward, backward, and turning.

## Components

- **ESP32 Dev Module**
- **DC Motors** (Motor A, Motor B)
- **Motor Driver (L298N or similar)**
- **WiFi Network**
- **Power Supply**

## Pin Configuration

- **Motor A**: Connected to pins `13` and `12`
- **Motor B**: Connected to pins `4` and `27`

## Web Interface

The car is controlled through a web interface, which consists of buttons to move the car in four directions: forward, backward, left, and right. These buttons send HTTP GET requests to the ESP32, triggering the movement of the car.

### HTML Interface
The web interface includes four main buttons:
- **Up Arrow (Forward)**
- **Down Arrow (Backward)**
- **Left Arrow (Left Turn)**
- **Right Arrow (Right Turn)**

## Code Breakdown

1. **OTA Setup**: OTA update functionality is provided by the `AsyncElegantOTA` library, allowing for firmware updates via a browser.
2. **Web Server**: Uses the `ESPAsyncWebServer` to host the control interface and respond to user interactions.
3. **Motor Control**: Functions to control the motors (`front()`, `back()`, `left()`, `right()`, and `stopwl()`).

## Getting Started

1. **Connect the ESP32 to your WiFi network** by setting your SSID and password in the `setup()` function:
    ```cpp
    const char* ssid = "yourWifiName";
    const char* password = "yourWifiPassword";
    ```

2. **Upload the code** to your ESP32 using the Arduino IDE or PlatformIO.
3. **Access the web interface** by visiting the IP address printed on the serial monitor after the ESP32 connects to WiFi.
4. **Control the car** by pressing the buttons on the web interface.

## OTA Update

1. **Open the web interface** and click on the OTA update link.
2. **Select the new firmware file** and upload it to update the car's software without needing a USB connection.
