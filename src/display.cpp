/*
   T-Dongle-S3 TFT status display for SuperWiFiDuck.
   Uses LovyanGFX, matching the configuration from USBArmyKnife.
   Licensed under the MIT License.
 */

#include "display.h"
#include "config.h"

#ifdef LILYGO_T_DONGLE_S3

#include <LovyanGFX.hpp>
#include <WiFi.h>
#include "settings.h"
#include "duckscript.h"
#include "led.h"

class LGFX_Panel : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7735S _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    LGFX_Panel(void)
    {
        {
            auto cfg = _bus_instance.config();
            cfg.spi_mode = 0;
            cfg.freq_write = 27000000;
            cfg.freq_read = 16000000;
            cfg.pin_sclk = DISPLAY_SCLK;
            cfg.pin_mosi = DISPLAY_MOSI;
            cfg.pin_miso = DISPLAY_MISO;
            cfg.pin_dc = DISPLAY_DC;
            cfg.spi_host = SPI3_HOST;
            cfg.spi_3wire = true;
            cfg.use_lock = false;
            cfg.dma_channel = SPI_DMA_CH_AUTO;
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs = DISPLAY_CS;
            cfg.pin_rst = DISPLAY_RST;
            cfg.pin_busy = DISPLAY_BUSY;
            cfg.panel_width = DISPLAY_HEIGHT;
            cfg.panel_height = DISPLAY_WIDTH;
            cfg.offset_rotation = 1;
            cfg.readable = true;
            cfg.invert = true;
            cfg.rgb_order = false;
            cfg.dlen_16bit = false;
            cfg.bus_shared = true;
            cfg.offset_x = 26;
            cfg.offset_y = 1;
            cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits = 1;
            cfg.memory_width = 132;
            cfg.memory_height = 160;
            _panel_instance.config(cfg);
        }
        {
            auto cfg = _light_instance.config();
            cfg.pin_bl = DISPLAY_LEDA;
            cfg.invert = true;
            cfg.freq = 12000;
            cfg.pwm_channel = 7;
            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }
        setPanel(&_panel_instance);
    }
};

static LGFX_Panel lcd;

namespace display {
    static const int foregroundColor = TFT_WHITE;
    static const int backgroundColor = TFT_BLACK;

    static unsigned long lastUpdate = 0;
    static char statusMsg[32] = "";

    void begin() {
        lcd.init();
        lcd.setBrightness(128);
        lcd.clear(backgroundColor);
        lcd.setTextColor(foregroundColor, backgroundColor);
        lcd.setTextSize(1.0f);
        lcd.setCursor(0, 0);
        lcd.println("WiFiDuck " VERSION);
        lcd.println("T-Dongle-S3");
        lcd.println("Starting...");
        lcd.display();
    }

    void setStatus(const char* msg) {
        strncpy(statusMsg, msg, sizeof(statusMsg) - 1);
        statusMsg[sizeof(statusMsg) - 1] = '\0';
        lastUpdate = 0; // Force refresh
    }

    static void updateLED() {
        const char* mode = settings::getMODE();
        if (duckscript::isRunning()) {
            led::setColor(120, 0, 120); // Purple while running script
        } else if (strcmp(mode, "STA") == 0) {
            if (WiFi.status() == WL_CONNECTED) {
                led::setColor(0, 80, 0); // Green when connected
            } else {
                led::setColor(0, 0, 80); // Blue while connecting
            }
        } else {
            led::setColor(0, 80, 0); // Green in AP mode
        }
    }

    void update() {
        unsigned long now = millis();
        if (now - lastUpdate < 1000) return;
        lastUpdate = now;

        lcd.clear(backgroundColor);
        lcd.setTextColor(foregroundColor, backgroundColor);
        lcd.setTextSize(1.0f);
        lcd.setCursor(0, 0);

        lcd.print("WiFiDuck ");
        lcd.println(VERSION);

        const char* mode = settings::getMODE();
        lcd.print("Mode: ");
        lcd.println(mode);

        lcd.print("SSID: ");
        lcd.println(settings::getSSID());

        lcd.print("IP: ");
        if (strcmp(mode, "STA") == 0 && WiFi.status() == WL_CONNECTED) {
            lcd.println(WiFi.localIP().toString().c_str());
        } else {
            lcd.println(WiFi.softAPIP().toString().c_str());
        }

        lcd.print("Script: ");
        if (duckscript::isRunning()) {
            lcd.print(duckscript::currentScript().c_str());
        } else {
            lcd.print("idle");
        }

        if (statusMsg[0] != '\0') {
            lcd.setCursor(0, lcd.height() - 8);
            lcd.print(statusMsg);
        }

        lcd.display();
        updateLED();
    }
}

#endif // LILYGO_T_DONGLE_S3
