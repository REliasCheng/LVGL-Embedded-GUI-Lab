# 开发环境 | Development Environment

本文档记录架构参考版本、平台与构建边界。当前默认分支不包含 LVGL、厂商库、SquareLine 输出或可构建工程。

## 主线平台

- MCU：GD32F407VE。
- Core：ARM Cortex-M4。
- Display：ST7789 / 240 × 280 / SPI0。
- Input：CST816T / I²C0 + EXTI。
- GUI：LVGL V8.3.11。
- Toolchain：Keil MDK-ARM、GigaDevice GD32F4xx DFP、GD32 Standard Peripheral Library。

## UI 与 PC 工具

- SquareLine Studio 1.4.1：生成 SmartWatch screen/event 结构。
- GCC / CMake / SDL2：PC LVGL simulator。

原始 `.spj` 包含本机绝对路径，且引用的部分视觉资源授权不明，因此未进入公开仓库。

## RTOS 变体

- FreeRTOS V10.5.1。
- GD32F407VE / Cortex-M4。
- tick hook、GUI update task 与 handler task。

未发现 GUI mutex，详见 [FreeRTOS Integration](rtos-integration.md)。

## 验证状态

- PC SDL：未提供可构建 simulator 或运行结果。
- Keil：未提供可构建 MCU 工程。
- Hardware：未提供板端运行、触摸交互或显示刷新证据。

架构说明、版本名称和文件清单都不能替代编译或板端运行证据。

## 参考平台

Phase 1 还识别到 STM32F103RB、STM32F103ZE 与 ESP-IDF 参考资料。它们没有进入公开主体，以保持 GD32F407VE / LVGL 主线清晰。

## 相关内容

- [FreeRTOS Integration](rtos-integration.md)
- [LVGL Porting](lvgl-porting.md)
