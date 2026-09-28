# LVGL 移植结构 | LVGL Porting

主线工程使用 LVGL 8.3.11。移植层把 GD32F407VE 的显示、触摸和时间基准转换为 LVGL driver 接口。

```text
Hardware / BSP
  ST7789 · CST816T · Basic Timer
              ↓
LVGL Port Layer
  Display Port · Input Port · Tick
              ↓
LVGL Core
              ↓
Application UI
```

## 初始化顺序

工程中的基本顺序为：

1. 初始化系统时钟、USART、I²C 和板级设备。
2. 调用 `lv_init()` 初始化 LVGL core。
3. 调用 `lv_port_disp_init()` 注册 display driver。
4. 调用 `lv_port_indev_init()` 注册 pointer input。
5. 配置 1 kHz basic timer，为 `lv_tick_inc(1)` 提供时间基准。
6. 在 super loop 或 RTOS task 中周期执行 `lv_timer_handler()`。

## Display Port

Display port 配置两个 `240 × 10` 像素 buffer，并注册 flush callback。`lv_conf.h` 定义 240 × 280、16-bit color 和 byte swap；port 文件中的 320 × 240 fallback 不会成为活动配置。

## Input Port

Input port 注册 LVGL pointer device，读取 CST816T 的 pressed/released 状态和坐标。PC simulator 使用 SDL mouse、keyboard 和 mouse wheel 替代硬件输入。

## Tick 与 Handler

- 裸机：basic timer 调用 `lv_tick_inc(1)`，super loop 调用 `lv_timer_handler()`。
- FreeRTOS：tick hook 调用 `lv_tick_inc(1)`，独立 task 调用 `lv_timer_handler()`。
- PC：`SDL_GetTicks()` 作为 custom tick source。

这些调用位置来自现有工程，不代表所有平台都采用相同调度方式。

## 相关内容

- [Display Pipeline](display-pipeline.md)
- [Input and Events](input-and-events.md)
- [FreeRTOS Integration](rtos-integration.md)
- [LVGL Porting Project](../projects/03-lvgl-porting/)
