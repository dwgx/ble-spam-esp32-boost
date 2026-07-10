# BLE Spam ESP32 Boost

Flipper Zero BLE 广播轰炸 + ESP32 双射频增强，适配官方固件 OFW 1.4.3。

A Flipper Zero BLE advertisement spammer with optional ESP32 dual-radio boost via Ghost ESP UART, ported to Official Firmware 1.4.3.

---

## Overview / 概述

**English:**
This is a Flipper Zero external app (`.fap`) that broadcasts BLE advertisement packets to trigger pairing popups, notifications, and device-discovery prompts on nearby phones and computers. It's a fork of Momentum BLE Spam, adapted for Official Firmware 1.4.3, with an added ESP32 boost mode: when connected over GPIO UART to an ESP32 running Ghost ESP firmware, both radios broadcast simultaneously for greater range.

No ESP32? No problem — it works standalone on the Flipper's internal STM32WB BLE radio.

**中文：**
这是一个 Flipper Zero 外部应用（`.fap`），通过广播 BLE 广告包来触发附近手机和电脑的配对弹窗、通知和设备发现提示。基于 Momentum BLE Spam 魔改，适配官方固件 1.4.3，加入了 ESP32 增强模式：通过 GPIO UART 连接运行 Ghost ESP 固件的 ESP32，两个射频同时广播，覆盖范围翻倍。

没有 ESP32 也能用——单 Flipper 内置 STM32WB BLE 射频照样干活。

---

## Features / 功能

- 11 种内置 BLE 轰炸攻击，覆盖 Apple、Google、Samsung、Microsoft 及通用 NameFlood 协议
- 可选 ESP32 双射频增强（Ghost ESP UART），启动时自动检测（标题栏显示 "BLE Spam+ESP"）
- 单机模式下使用 Flipper 内置 STM32WB BLE 射频
- 可配置：随机 MAC 地址、LED 指示灯、键盘锁定

### Range Modes / 射频模式

| Mode / 模式 | Range / 距离 | Radio / 射频 |
|---|---|---|
| Flipper only (无 ESP32) | ~1-3m | 内置 STM32WB BLE |
| ESP32 Boost | ~10-20m | ESP32 BLE (Ghost ESP) |
| Both / 双射频 | ~10-20m | 两个射频同时广播 |

### Attacks / 攻击列表

| # | Attack / 攻击 | Protocol / 协议 | ESP32 Command |
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
| 10 | Vibrate 'em All | LoveSpouse | (无 ESP 对应) |
| 11 | Denial of Pleasure | LoveSpouse | (无 ESP 对应) |

---

## Tech Stack / 技术栈

- **Language / 语言:** C，使用 Flipper Zero Application SDK
- **Target firmware / 目标固件:** Flipper Zero Official Firmware (OFW) 1.4.3
- **Build tool / 构建工具:** [ufbt](https://github.com/flipperdevices/flipperzero-ufbt)（micro Flipper Build Tool）
- **App manifest:** `application.fam`（appid: `ble_spam`，category: Bluetooth，version 7.0）
- **ESP32 boost dependency:** ESP32 运行 [Ghost ESP](https://github.com/Spooks4576/Ghost_ESP) 固件，115200 baud UART

---

## Project Structure / 项目结构

```
.
├── application.fam        # Flipper app manifest
├── ble_spam.c / .h        # 主程序：攻击表、入口、UI 接线
├── esp_boost.c / .h       # ESP32 UART 桥接 Ghost ESP
├── assets/                # 文本 payload 列表 (nameflood, swiftpair)
├── icons/                 # App 和平台图标
├── protocols/             # BLE 广告协议实现
│   ├── continuity.*       # Apple Continuity
│   ├── easysetup.*        # Samsung EasySetup
│   ├── fastpair.*         # Google FastPair
│   ├── lovespouse.*       # LoveSpouse
│   ├── nameflood.*        # Name flood
│   └── swiftpair.*        # Microsoft SwiftPair
├── scenes/                # UI scene manager: main, config, setup
└── LICENSE                # GNU GPL v3.0
```

---

## Getting Started / 快速开始

### Prerequisites / 前置条件

- Flipper Zero，运行 Official Firmware 1.4.3
- [ufbt](https://github.com/flipperdevices/flipperzero-ufbt) 已安装，SDK 版本对应 OFW 1.4.3
- （可选）ESP32 刷好 [Ghost ESP](https://github.com/Spooks4576/Ghost_ESP) 固件

### Build / 构建

```bash
ufbt
# Output: dist/ble_spam.fap
```

<!-- TODO: confirm whether ufbt is run from the repo root or a subdirectory -->

把 `dist/ble_spam.fap` 复制到 Flipper 的 `apps/Bluetooth/` 目录（通过 qFlipper 或 `ufbt launch`）。

### Run / 运行

在 Flipper 蓝牙应用菜单找到 **BLE Spam**，选一个攻击，开干。如果检测到 ESP32，标题栏会显示 "BLE Spam+ESP"。

---

## Hardware Setup / ESP32 硬件接线

Boost 模式完全可选。纯 Flipper 使用不需要额外硬件。

1. 给 ESP32 刷 [Ghost ESP 固件](https://github.com/Spooks4576/Ghost_ESP)
2. 接线到 Flipper GPIO：
   - Flipper TX (pin 13) → ESP32 RX
   - Flipper RX (pin 14) → ESP32 TX
   - Flipper GND (pin 8) → ESP32 GND
   - Flipper 3V3 (pin 9) → ESP32 3V3（或 USB 供电）
3. 启动 app，它会自动获取 USART UART，发送 `info` 命令探测，通道可用就启用 boost，把每个攻击镜像为 `blespam -<vendor>` 命令发给 Ghost ESP

---

## Configuration / 配置

通过 UI config 界面设置：

- **Random MAC** — 每包随机化广播 MAC 地址
- **LED indicator** — LED 活动指示灯开关
- **Lock keyboard** — 轰炸时锁定按键输入

ESP32 桥接使用固定 UART 参数，定义在 `esp_boost.c`：115200 baud，USART GPIO channel。

---

## OFW Compatibility / 官方固件兼容性

这个 fork 修补了几个 Momentum 专属 API 以适配 OFW 1.4.3：

- `FontBatteryPercent` → `FontSecondary`（前者是 Momentum 专属）
- `variable_item_list_get()` → 使用保存的 `VariableItem*` 引用（OFW 没有这个 getter）

---

## Status / 状态

活跃维护。`application.fam` 中版本号 7.0，在上游 Momentum BLE Spam 基础上加了 ESP32 boost 功能和 OFW 1.4.3 适配。

---

## Credits / 致谢

基于 [Momentum BLE Spam v6.6](https://github.com/Next-Flip/Momentum-Apps/tree/dev/ble_spam)。

- App + spam framework: [@Willy-JL](https://github.com/Willy-JL)
- Apple + iOS crash: [@ECTO-1A](https://github.com/ECTO-1A)
- Android + Windows pairs: [@Spooks4576](https://github.com/Spooks4576)
- ESP32 boost + OFW 1.4.3 port: [@dwgx](https://github.com/dwgx)

---

## License / 许可证

GNU General Public License v3.0 — 详见 [LICENSE](LICENSE)。
