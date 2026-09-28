# 开发环境 | Development Environment

## 主线平台

- MCU：GD32F407VE。
- Core：ARM Cortex-M4。
- Display：ST7789 / 240 × 280 / SPI0。
- Input：CST816T / I²C0 + EXTI。
- GUI：LVGL 8.3.11。
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

## 构建状态

Phase 2 不修改原始源码来适配当前机器。Keil 和 PC simulator 的构建结果分别记录为实际检测结果；“工程文件存在”和“迁移哈希一致”不表示构建通过。

## 参考平台

Phase 1 还识别到 STM32F103RB、STM32F103ZE 与 ESP-IDF 参考资料。它们没有进入公开主体，以保持 GD32F407VE / LVGL 主线清晰。
