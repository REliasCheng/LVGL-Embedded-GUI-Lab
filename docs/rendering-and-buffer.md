# 渲染与缓冲 | Rendering and Buffer

以下示例使用两个局部像素数组表达 partial double buffering，而不是 full-frame framebuffer。它是容量规划示例，不表示当前仓库包含实现。

## Buffer 结构

```text
Buffer A: 240 × 10 pixels
Buffer B: 240 × 10 pixels
Color:    16 bit / 2 bytes per pixel
Total:    9,600 bytes
```

两个 buffer 可作为 `buf1` 和 `buf2` 传给 `lv_disp_draw_buf_init()`。LVGL 可以在一个 buffer 被 flush 时准备另一个 buffer，但两个数组本身不表示 DMA 或异步显示传输。

## Refresh 流程

1. Widget 属性或 event 使 object area invalidated。
2. LVGL renderer 将当前区域绘制到 draw buffer。
3. Display driver 接收 `lv_area_t` 和像素指针。
4. ST7789 driver 设置显示窗口并写入像素。
5. 写入完成后调用 `lv_disp_flush_ready()`。

## 内存关系

- LVGL internal allocator：由 `lv_conf.h` 与实际对象规模决定。
- Draw buffers：约 9.6 KB。
- FreeRTOS 变体另有独立 RTOS heap。

当前仓库未提供 FPS、render time、CPU usage 或运行时 memory monitor 数据，因此文档只描述静态配置和调用关系。

## 相关内容

- [Display Pipeline](display-pipeline.md)
- [LVGL Porting](lvgl-porting.md)
