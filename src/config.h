/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#define VERSION "1.2.0"

/*! ===== DEBUG Settings ===== */
// #define ENABLE_DEBUG
// #define DEBUG_PORT Serial
// #define DEBUG_BAUD 115200

/*! ===== Communication Settings ===== */
// #define ENABLE_SERIAL
#define SERIAL_PORT Serial
#define SERIAL_BAUD 9600

#define BUFFER_SIZE 256
#define PACKET_SIZE 32

#define MSG_CONNECTED "LED 0 0 25\n"
#define MSG_STARTED "LED 0 25 0\n"

/*! ======EEPROM Settings ===== */
#define EEPROM_SIZE       4095
#define EEPROM_BOOT_ADDR  3210
#define BOOT_MAGIC_NUM    1234567890

/*! ===== WiFi Settings ===== */
/*
  Mode can be "STA" or "AP"
  STA is for connecting to an existing access point
  AP is for creating a new access point
*/
#define MODE "AP"

#define WIFI_SSID "wifiduck" // wifi name for AP or STA
#define WIFI_PASSWORD "wifiduck" // wifi password for AP or STA

#define WIFI_CHANNEL "1" // wifi channel for AP

#define HOSTNAME "wifiduck" // hostname
#define URL "wifi.duck" // url to access web interface


/*! ===== LED Settings ===== */
// --- LED Configuration ---

// Tell the code to use the NeoPixel (WS2812) driver
#define NEOPIXEL

// Set the GPIO pin where the WS2812 LED is connected
#define LED_PIN 21

// Set the number of NeoPixels. For the ESP32-S3-Zero, this is 1.
#define NEOPIXEL_NUM 1

#ifdef LILYGO_T_DONGLE_S3
    // LilyGo T-Dongle-S3 uses an APA102 (DotStar) RGB LED on GPIO 39/40
    // and a 0.96" 80x160 ST7735S TFT display on GPIO 1-5/38.
    #undef NEOPIXEL
    #define DOTSTAR
    #ifndef DOTSTAR_NUM
        #define DOTSTAR_NUM 1
    #endif
    #ifndef DOTSTAR_DI
        #define DOTSTAR_DI 40
    #endif
    #ifndef DOTSTAR_CI
        #define DOTSTAR_CI 39
    #endif
    #ifndef DISPLAY_RST
        #define DISPLAY_RST 1
    #endif
    #ifndef DISPLAY_DC
        #define DISPLAY_DC 2
    #endif
    #ifndef DISPLAY_MOSI
        #define DISPLAY_MOSI 3
    #endif
    #ifndef DISPLAY_CS
        #define DISPLAY_CS 4
    #endif
    #ifndef DISPLAY_SCLK
        #define DISPLAY_SCLK 5
    #endif
    #ifndef DISPLAY_LEDA
        #define DISPLAY_LEDA 38
    #endif
    #ifndef DISPLAY_MISO
        #define DISPLAY_MISO -1
    #endif
    #ifndef DISPLAY_BUSY
        #define DISPLAY_BUSY -1
    #endif
    #ifndef DISPLAY_WIDTH
        #define DISPLAY_WIDTH 160
    #endif
    #ifndef DISPLAY_HEIGHT
        #define DISPLAY_HEIGHT 80
    #endif
    #ifndef TFT_WIDTH
        #define TFT_WIDTH 80
    #endif
    #ifndef TFT_HEIGHT
        #define TFT_HEIGHT 160
    #endif
#endif


/*! ===== DEBUG Settings ===== */
#define ENABLE_DEBUG
#define DEBUG_PORT Serial
#define DEBUG_BAUD 115200


