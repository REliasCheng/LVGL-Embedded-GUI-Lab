# 开发环境 | Development Environment

本文档记录公开工程实际使用的版本、平台与构建边界，不把工程文件存在等同于构建通过。

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

## 构建状态

- PC SDL：CMake 配置阶段因本机无法找到 SDL2 package 而停止，尚未进入源码编译。
- Keil：当前环境未发现 `UV4.exe`，5 个工程未执行自动构建。
- Hardware：未执行板端运行、触摸交互或显示刷新验证。

原始工程未为当前机器修改。“工程文件完整”和“迁移哈希一致”不表示编译或板端运行通过。

## 参考平台

Phase 1 还识别到 STM32F103RB、STM32F103ZE 与 ESP-IDF 参考资料。它们没有进入公开主体，以保持 GD32F407VE / LVGL 主线清晰。

## 工程入口

- [PC SDL Simulator](../projects/01-pc-simulator/)
- [GD32 LVGL Porting](../projects/03-lvgl-porting/)
- [FreeRTOS SmartWatch](../projects/05-rtos-smartwatch/)
- 上一层：[FreeRTOS Integration](rtos-integration.md)
