# PC SDL Simulator

## 项目作用

使用 GCC/CMake 与 SDL2 提供 LVGL display、mouse、keyboard 和 mouse-wheel encoder，使 UI object、event 与 screen navigation 可以在桌面环境运行。该工程是 GUI simulator，不是 MCU hardware emulator。

## 软件关系

```text
Application UI
      ↓
LVGL V8.3.11
      ↓
SDL Display / Input
      ↓
Desktop
```

## 关键接口

- `SDL_GetTicks()`：custom tick source。
- `lv_timer_handler()`：在 simulator loop 中周期执行。
- `lv_disp_draw_buf_init()`：配置 SDL 显示缓冲。

**Keywords:** `SDL` / `LVGL` / `Mouse` / `Keyboard` / `Encoder`

## 构建状态

当前机器的 CMake 配置阶段因无法找到 SDL2 package 而停止，尚未进入源码编译。该结果反映本地依赖缺失，不等同于源码编译失败。

## 公开边界

`course/` 保留 simulator、LVGL core、已核对许可的 Unscii ASCII 生成字体和可审查的 UI 结构；`build/`、二进制依赖及无法建立再分发依据的视觉/字体资源未迁移，因此该快照不作为独立可构建发行包。

相关文档：[Development Environment](../../docs/development-environment.md) · [Input and Events](../../docs/input-and-events.md)
