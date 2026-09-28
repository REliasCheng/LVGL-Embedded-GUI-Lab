# 页面导航 | Screen Navigation

SmartWatch 工程族包含 `ui_Screen1` 至 `ui_Screen4`。源码没有为每个 screen 提供稳定的产品级命名，因此仓库按真实 object 名和组件职责描述。

## 页面关系

```text
                 swipe right
ui_Screen2  ─────────────────> ui_Screen1
                                   │
                       swipe left  │  swipe right
                                   ↓
                              ui_Screen3

ui_Screen1 ── swipe up / fade ──> ui_Screen4
```

实际 `ui.c` 中：

- Screen1 向左进入 Screen3。
- Screen1 向右进入 Screen2。
- Screen1 向上进入 Screen4。
- Screen2 向左返回 Screen1。
- Screen3 向右返回 Screen1。

## 页面内容

- Screen1：时钟 Label、表针 Image 和状态区域。
- Screen2：Chart 与 Label。
- Screen3：Button、LED 状态 Panel 与 Label。
- Screen4：Arc、duty Label 与 GIF container。

Arc 的 value-changed callback 会更新 Label 并调用 `on_pwm_duty_update()`；嵌入式工程中的该函数没有实际 PWM 实现，因此不能写成已完成硬件 PWM 控制。

## 资源边界

页面源码引用的部分 image/font 资源因授权信息不足没有发布。该文档描述导航和事件结构，不提供运行截图或完整视觉复现。

## 相关工程

- [Bare-metal SmartWatch](../projects/04-baremetal-smartwatch/)
- [FreeRTOS SmartWatch](../projects/05-rtos-smartwatch/)
