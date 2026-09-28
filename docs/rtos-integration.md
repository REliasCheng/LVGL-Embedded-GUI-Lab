# FreeRTOS 集成 | RTOS Integration

一个 GD32F407VE 变体将 SmartWatch UI 放入 FreeRTOS V10.5.1 工程。该内容记录 GUI update task、handler task 和 tick hook 的实际分工，不构成线程安全验证。

## 当前执行结构

```text
FreeRTOS
  ├── Tick Hook ───────────→ lv_tick_inc(1)
  ├── task_lvgl ───────────→ UI init / RTC / Widget update
  └── task_timer_handler ──→ lv_timer_handler()
                                  ↓
                         Display / Input processing
```

工程使用 `xTaskCreate()` 创建 GUI update task 与 handler task，并通过 `vTaskDelay()` 控制执行周期。

## 线程安全边界

`task_lvgl` 更新 Label、Image 等 object，另一个 task 调用 `lv_timer_handler()`。源码中未发现统一 GUI mutex、单 GUI task message queue 或其他全局锁。

因此当前结构只能描述为“LVGL 运行在 FreeRTOS 工程中”。不能描述为：

- thread-safe LVGL integration；
- RTOS-safe UI architecture；
- verified concurrent GUI access。

文档不在现有结构上推断同步保证，也不修改原始工程来补充锁。

## 内存边界

LVGL 使用自身 internal allocator；FreeRTOS 使用独立 `heap_4`。两者不是同一个 heap，也没有运行时内存测量记录。

## 相关内容

- [FreeRTOS SmartWatch](../projects/05-rtos-smartwatch/)
- [FreeRTOS Embedded Lab](https://github.com/REliasCheng/FreeRTOS-Embedded-Lab)
- 相关机制：[LVGL Porting](lvgl-porting.md)
