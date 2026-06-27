/*
   T-Dongle-S3 TFT status display for SuperWiFiDuck.
   Licensed under the MIT License.
 */

#pragma once

#ifdef LILYGO_T_DONGLE_S3

#include <Arduino.h>

namespace display {
    void begin();
    void update();
    void setStatus(const char* msg);
}

#endif // LILYGO_T_DONGLE_S3
