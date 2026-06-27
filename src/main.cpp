#include <Arduino.h>

#include "config.h"
#include "debug.h"
#include "duckscript.h"
#include "duckparser.h"
#include "webserver.h"
#include "spiffs.h"
#include "settings.h"
#include "cli.h"
#include "USB.h"
#include "display.h"
#include "led.h"


void setup() {
    debug_init();
    led::begin();
    led::setColor(0, 80, 0); // Boot: green
    duckparser::beginKeyboard();
    USB.begin();
    delay(200);

#ifdef LILYGO_T_DONGLE_S3
    display::begin();
    display::setStatus("Init...");
#endif

    spiffs::begin();
    settings::begin();
    cli::begin();
    webserver::begin();

#ifdef LILYGO_T_DONGLE_S3
    display::setStatus("Ready");
#endif

    duckscript::run(settings::getAutorun());
}

void loop() {
    webserver::update();
    debug_update();

#ifdef LILYGO_T_DONGLE_S3
    display::update();
#endif
}