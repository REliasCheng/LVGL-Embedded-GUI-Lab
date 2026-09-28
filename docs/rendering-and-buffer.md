# 渲染与缓冲 | Rendering and Buffer

主线显示端口把两个像素数组同时注册为局部 draw buffer，因此属于 partial double buffering，而不是 full-frame framebuffer。

## Buffer 结构

```text
Buffer A: 240 × 10 pixels
Buffer B: 240 × 10 pixels
Color:    16 bit / 2 bytes per pixel
Total:    9,600 bytes
```

两个 buffer 作为 `buf1` 和 `buf2` 传给 `lv_disp_draw_buf_init()`。LVGL 可以在一个 buffer 被 flush 时准备另一个 buffer，但当前 flush 是同步轮询写入；两个数组本身不表示 DMA 或异步显示传输。

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
- 工程入口：[LVGL Porting Template](../projects/03-lvgl-porting/)
