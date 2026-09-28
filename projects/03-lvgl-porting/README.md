# GD32 LVGL Porting Template

## 项目作用

将 LVGL 8.3.11 接入 GD32F407VE 的显示、触摸和 1 ms tick，形成 MCU GUI 的最小移植结构。

## 软件关系

```text
LVGL Core
   ├── lv_port_disp → ST7789 / SPI0
   ├── lv_port_indev → CST816T / I²C0
   └── lv_tick_inc ← Basic Timer
```

## 关键配置

- 240 × 280、16-bit color、byte swap enabled。
- 两个 `240 × 10` 像素 draw buffer。
- `LV_MEM_CUSTOM = 0`，内部 heap 约 48 KB。
- `lv_timer_handler()` 在 super loop 中执行。

上游 LVGL `demos/` 与 `examples/` 未复制，仅保留 core source 和工程所需接口。

公开快照保留已核对许可的 Unscii ASCII 生成字体，排除无法建立再分发依据的其他生成字体；该工程不作为包含全部 LVGL 内置字体的独立构建发行包。
