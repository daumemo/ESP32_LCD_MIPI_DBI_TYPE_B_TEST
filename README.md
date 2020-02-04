# ESP32_LCD_MIPI_DBI_TYPE_B_TEST
Firmware code useful for interconnecting ESP32 (or any Arduino board) to an LCD through MIPI DBI Type B interface.
The code was used to test a connection between ESP32 (running Arduino) and R61529 based LCD.

There are two files: Arduino-basic.cpp and ESP32-specific.cpp

Arduino-basic.cpp should work on any Arduino based MCU, but it is quite slow.
ESP32-specific uses ESP32 register to write data directly to the IO register. This code should work only on ESP32, but it is faster solution.

More information, how and where I have used these code snippets here:
