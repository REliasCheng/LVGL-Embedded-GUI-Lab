# LVGL 移植结构 | LVGL Porting

本文以 LVGL V8.3.11 为参考。移植层需要把显示、触摸和时间基准转换为 LVGL v8 driver 接口；当前默认分支不提供可构建实现。

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

典型初始化顺序为：

1. 初始化系统时钟、USART、I²C 和板级设备。
2. 调用 `lv_init()` 初始化 LVGL core。
3. 调用 `lv_port_disp_init()` 注册 display driver。
4. 调用 `lv_port_indev_init()` 注册 pointer input。
5. 配置 1 kHz basic timer，为 `lv_tick_inc(1)` 提供时间基准。
6. 在 super loop 或 RTOS task 中周期执行 `lv_timer_handler()`。

## Display Port

Display port 需要配置 draw buffer 并注册 flush callback。分辨率、色深、byte swap 与 buffer 大小必须按实际显示控制器和内存预算确定。

## Input Port

Input port 注册 LVGL pointer device，读取 CST816T 的 pressed/released 状态和坐标。PC simulator 使用 SDL mouse、keyboard 和 mouse wheel 替代硬件输入。

## Tick 与 Handler

- 裸机：basic timer 调用 `lv_tick_inc(1)`，super loop 调用 `lv_timer_handler()`。
- FreeRTOS：tick hook 调用 `lv_tick_inc(1)`，独立 task 调用 `lv_timer_handler()`。
- PC：`SDL_GetTicks()` 作为 custom tick source。

这些是 LVGL v8 的参考调用关系，不代表所有平台都采用相同调度方式，也不构成 LVGL v9 API 说明。

## 相关内容

- [Display Pipeline](display-pipeline.md)
- [Input and Events](input-and-events.md)
- [FreeRTOS Integration](rtos-integration.md)
- 环境与版本：[Development Environment](development-environment.md)
