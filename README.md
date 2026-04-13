# BLE Spam + ESP32 Boost

Flipper Zero BLE Spam app with optional **dual-radio ESP32 boost** via Ghost ESP UART.

Based on [Momentum BLE Spam v6.6](https://github.com/Next-Flip/Momentum-Apps/tree/dev/ble_spam) by @Willy-JL, @ECTO-1A, @Spooks4576. Ported to **Official Firmware (OFW) 1.4.3** with ESP32 enhancement by @dwgx.

## What's New

**ESP32 Boost Mode**: When an ESP32 running [Ghost ESP](https://github.com/Spooks4576/Ghost_ESP) firmware is connected via GPIO UART, the app automatically mirrors BLE spam commands to the ESP32 for higher-power dual-radio broadcasting.

| Mode | Range | Radio |
|---|---|---|
| Flipper only (no ESP32) | ~1-3m | Internal STM32WB BLE |
| ESP32 Boost | ~10-20m | ESP32 BLE (via Ghost ESP) |
| Both (dual-radio) | ~10-20m | Both radios simultaneously |

The app auto-detects ESP32 on startup. If connected, the title bar shows **"BLE Spam+ESP"**. If not connected, it works exactly like the original app.

## Attacks

| # | Attack | Protocol | ESP32 Mapping |
|---|---|---|---|
| 1 | The Kitchen Sink | All | `blespam -random` |
| 2 | BT Settings Flood | NameFlood | `blespam -random` |
| 3 | iOS 17 Lockup Crash | Apple Continuity | `blespam -apple` |
| 4 | Apple Action Modal | Apple Continuity | `blespam -apple` |
| 5 | Apple Device Popup | Apple Continuity | `blespam -apple` |
| 6 | Android Device Connect | Google FastPair | `blespam -google` |
| 7 | Samsung Buds Popup | Samsung EasySetup | `blespam -samsung` |
| 8 | Samsung Watch Pair | Samsung EasySetup | `blespam -samsung` |
| 9 | Windows Device Found | SwiftPair | `blespam -ms` |
| 10 | Vibrate 'em All | LoveSpouse | (no ESP equivalent) |
| 11 | Denial of Pleasure | LoveSpouse | (no ESP equivalent) |

## Hardware Setup

### Flipper Only (default)
Just install and run. No extra hardware needed.

### With ESP32 Boost
1. Flash [Ghost ESP firmware](https://github.com/Spooks4576/Ghost_ESP) to your ESP32
2. Connect ESP32 to Flipper GPIO:
   - Flipper TX (pin 13) -> ESP32 RX
   - Flipper RX (pin 14) -> ESP32 TX
   - Flipper GND (pin 8) -> ESP32 GND
   - Flipper 3V3 (pin 9) -> ESP32 3V3 (or USB power)
3. Launch BLE Spam - title shows "BLE Spam+ESP" if detected

## Building

Requires [ufbt](https://github.com/flipperdevices/flipperzero-ufbt) with OFW 1.4.3 SDK:

```bash
cd ble_spam
ufbt
# Output: dist/ble_spam.fap
```

## OFW Compatibility Fixes

This fork includes patches for Official Firmware compatibility:
- `FontBatteryPercent` -> `FontSecondary` (Momentum-only font)
- `variable_item_list_get()` -> stored `VariableItem*` reference (API not in OFW)

## Credits

- App + Spam framework: [@Willy-JL](https://github.com/Willy-JL)
- Apple + iOS Crash: [@ECTO-1A](https://github.com/ECTO-1A)
- Android + Windows: [@Spooks4576](https://github.com/Spooks4576)
- ESP32 Boost + OFW port: [@dwgx](https://github.com/dwgx)

## License

Same as upstream (see [LICENSE](LICENSE)).
