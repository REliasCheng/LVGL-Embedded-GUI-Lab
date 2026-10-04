# 显示链路 | Display Pipeline

本文以 GD32F407VE、SPI 与 ST7789 为参考说明显示链路。LVGL renderer、flush callback 和物理传输分别承担区域渲染、刷新提交与 LCD 写入；当前默认分支没有提供对应驱动实现。

![Display pipeline](../assets/images/diagram/display-pipeline.svg)

## 参考配置

- MCU：GD32F407VE / ARM Cortex-M4。
- Display interface：SPI0 polling transfer。
- Controller：ST7789。
- Resolution：240 × 280。
- Color：16-bit RGB565 with byte swap。

## Flush 路径

```text
Invalidated Object Area
          ↓
LVGL Renderer
          ↓
Current Draw Buffer
          ↓
Display Flush Callback
          ↓
ST7789_Fill(area, color_p)
          ↓
SPI0 / LCD
          ↓
lv_disp_flush_ready()
```

`flush_cb` 不是 renderer。它接收 LVGL 已渲染的区域和像素指针；同步传输可在写入完成后调用 `lv_disp_flush_ready()`，异步传输则应在完成回调中通知。当前仓库不声明 DMA、DMA2D、LTDC 或 GPU acceleration 已实现。

## 硬件边界

底层实现需要初始化显示控制器、设置写入区域并保证像素格式一致。本仓库不把通用 SPI 外设配置扩展成实现声明。底层外设基础可参考 [ARM Cortex-M Development Lab](https://github.com/REliasCheng/ARM-Cortex-M-Development-Lab)。

## 相关内容

- [Rendering and Buffer](rendering-and-buffer.md)
- 下一层：[Input and Events](input-and-events.md)
