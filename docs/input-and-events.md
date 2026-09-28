# 输入与事件 | Input and Events

主线硬件输入使用 CST816T 电容触摸，PC simulator 使用 SDL 输入设备。

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

控制器使用 7-bit 地址 `0x15`。代码同时保留 wire address `0x2A/0x2B` 的注释。读取结果限制在 240 × 280 范围内；没有发现校准矩阵或横竖屏坐标变换。

## PC 输入链路

SDL driver 提供 mouse pointer、keyboard 和 mouse-wheel encoder，使 Widget event 可以在桌面环境中执行。

## 实际事件

代表 UI 使用：

- Gesture：页面切换。
- Clicked：按钮 callback。
- Value Changed：Arc 和 Label 更新。
- Screen Load Start：启动表针和透明度动画。

工程没有建立独立 event bus。部分 Widget callback 直接调用 LED 等硬件函数，UI 与应用逻辑存在直接耦合。

## 相关内容

- [Screen Navigation](screen-navigation.md)
- [Widgets and Layout](widgets-and-layout.md)
- [Display / Touch Bring-up](../projects/02-display-touch-bringup/)
