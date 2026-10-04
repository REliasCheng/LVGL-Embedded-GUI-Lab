# 输入与事件 | Input and Events

本文以 CST816T 电容触摸和 SDL 输入设备为参考说明两条输入路径。它们都可在 LVGL indev 层汇合，再由 Event 连接 Widget callback 与页面状态；当前默认分支不包含对应驱动。

![Input event flow](../assets/images/diagram/input-event-flow.svg)

## GD32 触摸链路

```text
CST816T
  I²C0 register data + PB4 EXTI
                ↓
Touch Driver
  state + X/Y coordinate
                ↓
LVGL indev read callback
                ↓
Pointer Device
                ↓
Widget Event / Screen Gesture
```

具体 I²C 地址、坐标范围、校准矩阵与横竖屏变换必须按实际控制器数据手册、显示方向和板级实现确认。

## PC 输入链路

SDL driver 提供 mouse pointer、keyboard 和 mouse-wheel encoder，使 Widget event 可以在桌面环境中执行。

PC SDL 工程提供 GUI input mapping，不模拟 CST816T、I²C0 或 MCU 中断行为。

## 事件设计

UI 可使用：

- Gesture：页面切换。
- Clicked：按钮 callback。
- Value Changed：Arc 和 Label 更新。
- Screen Load Start：启动表针和透明度动画。

实现时应明确 Widget callback 是否直接调用硬件函数，或通过应用事件层解耦 UI 与设备逻辑。

## 相关内容

- [Widgets and Layout](widgets-and-layout.md)
- 下一层：[Screen Navigation](screen-navigation.md)
