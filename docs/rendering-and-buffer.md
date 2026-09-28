# 渲染与缓冲 | Rendering and Buffer

主线显示端口采用局部双缓冲，而不是 full-frame framebuffer。

## Buffer 结构

```text
Buffer A: 240 × 10 pixels
Buffer B: 240 × 10 pixels
Color:    16 bit / 2 bytes per pixel
Total:    9,600 bytes
```

两个 buffer 通过 `lv_disp_draw_buf_init()` 注册。LVGL 可以在一个 buffer 被 flush 时准备另一个 buffer，但当前驱动的 flush 本身是同步轮询写入；这不等同于异步 DMA rendering。

## Refresh 流程

1. Widget 属性或 event 使 object area invalidated。
2. LVGL renderer 将当前区域绘制到 draw buffer。
3. Display driver 接收 `lv_area_t` 和像素指针。
4. ST7789 driver 设置显示窗口并写入像素。
5. 写入完成后调用 `lv_disp_flush_ready()`。

## 内存关系

- LVGL internal allocator：主线模板约 48 KB，CMSIS/FreeRTOS 配置约 64 KB。
- Draw buffers：约 9.6 KB。
- FreeRTOS 变体另有独立 RTOS heap。

工程未提供 FPS、render time、CPU usage 或运行时 memory monitor 数据，因此文档只描述静态配置和调用关系。

## 相关内容

- [Display Pipeline](display-pipeline.md)
- [LVGL Porting](lvgl-porting.md)
