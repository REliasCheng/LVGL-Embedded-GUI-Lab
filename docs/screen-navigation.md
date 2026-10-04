# 页面导航 | Screen Navigation

以下四页面关系是 UI 状态机设计示例，用于说明 Gesture event 与 screen transition 的组织方式；当前默认分支不包含对应 SquareLine 输出或运行 UI。

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

设计关系为：

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

Arc 的 value-changed callback 可以更新 Label 并调用应用层接口；没有固件实现和硬件证据时，不能写成已完成 PWM 控制。

## 资源边界

当前默认分支没有发布 image/font 资源、页面源码、运行截图或完整视觉复现。

## 相关内容

- 输入层：[Input and Events](input-and-events.md)
- 对象层：[Widgets and Layout](widgets-and-layout.md)
