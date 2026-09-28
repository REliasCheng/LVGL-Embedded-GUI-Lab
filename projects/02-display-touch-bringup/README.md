# GD32 Display / Touch Bring-up

## 项目作用

建立 GD32F407VE 到 ST7789 显示控制器和 CST816T 触摸控制器的底层连接，为 LVGL display/input port 提供 BSP 基础。

## 硬件关系

```text
GD32F407VE ── SPI0 ──> ST7789 ──> 240×280 LCD
GD32F407VE <─ I²C0 / EXTI ─ CST816T Touch
```

## 关键接口

- `ST7789_Init()` / `ST7789_Test()`：显示初始化与工程内测试入口。
- `CST816T_Init()`：触摸控制器初始化。
- I²C0 与 EXTI：触摸寄存器访问和事件输入。

## 验证状态

原始源码与 Keil 工程定义按白名单保留，构建产物已排除。本阶段未执行 Keil 自动构建或板端复测。
