El eje z apunta al campo magnetico y eje y apunta al piso. Asi el heading funciona bien con el codigo propuesto.

**Espressif ESP32 Dev Module**

Se utiliza Platform IO con .ini:

; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

lib_deps =
    adafruit/Adafruit LSM303DLHC
