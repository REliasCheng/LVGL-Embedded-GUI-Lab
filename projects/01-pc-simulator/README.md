# PC SDL Simulator

## 项目作用

使用 GCC/CMake 与 SDL2 提供 LVGL display、mouse、keyboard 和 mouse-wheel encoder，使 UI object、event 与 screen navigation 可以脱离 MCU 外设进行代码级调试。

## 软件关系

```text
Application UI
      ↓
LVGL 8.3.11
      ↓
SDL Display / Input
      ↓
Desktop
```

## 关键接口

- `SDL_GetTicks()`：custom tick source。
- `lv_timer_handler()`：在 simulator loop 中周期执行。
- `lv_disp_draw_buf_init()`：配置 SDL 显示缓冲。

## 公开边界

`course/` 保留 simulator、LVGL core、已核对许可的 Unscii ASCII 生成字体和可审查的 UI 结构；`build/`、二进制依赖及无法建立再分发依据的视觉/字体资源未迁移，因此该快照不作为独立可构建发行包。
