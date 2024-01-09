# M5Stack Core2 - LVGL + MQTT + IMU MPU6886

The M5Stack Core2 - LVGL + MQTT + IMU MPU6886 example is a project that showcases the capabilities of the M5Stack Core2 development board, the LVGL graphics library and the [IMU MPU6886](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/MPU-6886-000193%2Bv1.1_GHIC_en.pdf). 

# Quickstart
## Requirements:
 - [Visual Studio Code](https://code.visualstudio.com/)
 - [PlatformIO](https://platformio.org/)

## Steps
 - Clone repository
```
git clone https://github.com/alptbz/core2imu
```
 - Open repository with PlatformIO
 - Wait for PlatformIO to initialize everything. This can take a while.
 - rename `src/config.cpp.template` to `src/config.cpp`
 - Define WLAN SSID, WLAN credentials, and MQTT Broker connection information in config.cpp
 - Adjust serial port in `platform.ini` if necessary
 - Ctrl + Shift + P: `PlatformIO: Upload and Monitor`

# Links
 - Used LVGL Example: https://github.com/mhaberler/m5core2-lvgl-demo
 - LVGL 7.x Docs: https://docs.lvgl.io/7.11/
 - Original chinese source: https://macsbug.wordpress.com/2021/06/18/how-to-run-lvgl-on-m5stack-esp32/
 - FastLED Example: https://github.com/m5stack/M5-ProductExampleCodes/blob/master/Base/M5GO_BOTTOM2/M5GO_BOTTOM2.ino
 - Image convert: https://lvgl.io/tools/imageconverter

# More examples
 - https://github.com/alptbz/core2guitofexample/
 - https://github.com/alptbz/core2numpad/


## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a> and [GNU GENERAL PUBLIC LICENSE version 3](https://www.gnu.org/licenses/gpl-3.0.en.html). If there are any contradictions between the two licenses, the Attribution-NonCommercial-ShareAlike 4.0 International license governs. 
