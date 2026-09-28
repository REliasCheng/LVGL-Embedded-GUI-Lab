# FreeRTOS SmartWatch Reference

## 项目作用

记录 GD32F407VE + FreeRTOS V10.5.1 工程中 LVGL tick、GUI update task 与 handler task 的组织方式。

## 执行关系

```text
FreeRTOS Tick Hook → lv_tick_inc(1)
task_lvgl          → UI / RTC / Widget Update
task_timer_handler → lv_timer_handler()
```

**Keywords:** `FreeRTOS` / `GUI Task` / `Tick Hook` / `LVGL`

## 并发边界

工程中两个任务均可能进入 LVGL API，未发现统一 GUI mutex 或单 GUI task 消息入口。该工程说明 RTOS 承载方式，不代表已实现 thread-safe LVGL integration。

## 公开边界

未知授权视觉资源与构建产物未迁移；本阶段未执行 Keil 自动构建或板端验证。

相关文档：[FreeRTOS Integration](../../docs/rtos-integration.md) · [Development Environment](../../docs/development-environment.md)
