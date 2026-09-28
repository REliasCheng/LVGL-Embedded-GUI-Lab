# Bare-metal SmartWatch Reference

## 项目作用

在 GD32F407VE 裸机循环中连接四页面 SmartWatch UI、触摸 Gesture、RTC 时间更新、LED callback 和 LVGL handler。

## 数据流

```text
CST816T → LVGL Event → Screen / Widget Callback
RTC ────────────────→ Label / Image Angle Update
Button Click ───────→ LED Callback / UI State
```

## 页面结构

源码使用 `ui_Screen1` 至 `ui_Screen4`。Screen1 连接时钟显示，Screen2 包含 Chart，Screen3 包含 LED 控制按钮，Screen4 包含 Arc 与 duty label。页面切换由 Gesture event 驱动。

## 公开边界

无法建立再分发依据的表盘、图标及 image/font 生成资源没有迁移；已核对许可的 Unscii ASCII 生成字体保留。该目录用于检查 UI、event 与应用 callback 关系，不作为可独立构建的完整 SmartWatch 发布包。
