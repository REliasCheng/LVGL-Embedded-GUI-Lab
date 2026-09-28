# Widget 与布局 | Widgets and Layout

文档只记录代表工程中出现的组件，不列出 LVGL 全部 Widget API。

## 实际 Widget

- Arc
- Button
- Button Matrix
- Chart
- GIF
- Image
- Keyboard
- Label
- Tabview
- Textarea
- Base Object / Container

## Object 关系

```text
Screen
  ├── Container / Panel
  │     ├── Label
  │     └── Image
  ├── Chart
  ├── Button
  └── Arc
```

SmartWatch 主线主要使用 SquareLine 生成的坐标和容器关系。LVGL 配置启用了 Flex/Grid，PC 示例中存在直接使用；不能据此把四页面 SmartWatch 描述成完整 Flex/Grid layout system。

## Style

生成代码设置颜色、透明度、border、radius、padding 和字体。工程使用 default theme，但没有独立的 theme switching 或 dark-mode 管理层。

## Event 边界

Widget event 负责页面切换、文本更新、动画和硬件 callback。当前结构没有 MVC、MVVM 或 MVP 分层，文档不引入源码中不存在的模式名称。

## 相关内容

- [Input and Events](input-and-events.md)
- [Screen Navigation](screen-navigation.md)
