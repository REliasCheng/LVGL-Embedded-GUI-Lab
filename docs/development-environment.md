# Development Environment

## Current host runtime

- LVGL v9.6.0 at commit `80ca777e37a2b176770726a02e07a6fb79ef0b39`, pinned as a Git submodule.
- CMake 3.20+, C/C++ compiler, Ninja recommended.
- SDL2 development package and `pkg-config` for the interactive window. `DASHBOARD_ENABLE_SDL=ON` enables the SDL display and mouse; the default OFF setting builds headless tests without SDL2.
- Logical GUI resolution 240 × 280; SDL zoom is 2× for desktop visibility.
- `ctest` runs model, normal, fault, interaction and, when SDL is enabled, a bounded SDL window smoke. Linux CI executes the SDL smoke with Xvfb.
- The headless backend is real LVGL software rendering through a checked XRGB8888 flush callback, not a model-only mock.

Build and scenario commands are in the [README](../README.md). A fresh clone needs `git submodule update --init --recursive`; once the pinned source is available, CMake can build offline.

## Historical target reference

The original architecture notes elsewhere in `docs/` refer to LVGL v8.3.11, GD32F407VE, ST7789 240 × 280 SPI0, CST816T I²C0/EXTI, Keil MDK, SquareLine Studio 1.4.1 and a FreeRTOS GUI task. Those are historical design references and must be ported to the actual v9 API before use. The local `.spj` and unknown-rights visual assets remain excluded.

The host SDL display, pointer and single-thread loop are replaceable boundaries for later ST7789, CST816T and FreeRTOS GUI task adapters. No target build, display flush, touch mapping, GUI mutex, DMA completion or board runtime has been verified in this repository.
