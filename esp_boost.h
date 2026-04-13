#pragma once

#include <stdbool.h>
#include <stdint.h>

// ESP32 Boost: optional UART bridge to Ghost ESP firmware
// When ESP32 running Ghost ESP is connected via GPIO UART,
// BLE spam commands are mirrored to ESP32 for dual-radio
// higher-power broadcasting (~10-20m vs ~1-3m internal BLE)

typedef enum {
    EspBoostCmdApple,
    EspBoostCmdSamsung,
    EspBoostCmdGoogle,
    EspBoostCmdWindows,
    EspBoostCmdRandom, // Kitchen Sink / NameFlood / fallback
} EspBoostCmd;

typedef struct EspBoost EspBoost;

// Try to open UART and detect Ghost ESP. Returns NULL if not found.
EspBoost* esp_boost_init(void);

// Free resources and close UART
void esp_boost_free(EspBoost* boost);

// Is ESP32 connected and responding?
bool esp_boost_is_connected(EspBoost* boost);

// Start BLE spam on ESP32 with the given command type
void esp_boost_start(EspBoost* boost, EspBoostCmd cmd);

// Stop BLE spam on ESP32
void esp_boost_stop(EspBoost* boost);
