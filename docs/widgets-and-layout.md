# Widget 与布局 | Widgets and Layout

文档记录一组代表性的 Object、Widget、Style 与 Layout 关系，不扩展为 LVGL Widget API 列表，也不表示当前仓库包含对应 UI 实现。

## Representative Widgets

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

坐标式页面、Flex 和 Grid 是不同布局策略；不能只因配置支持 Flex/Grid 就把一个坐标式页面描述成完整 Flex/Grid layout system。

这一区分对应“库能力”与“具体 UI 实现”的边界。

## Style

Style 可以设置颜色、透明度、border、radius、padding 和字体。没有对应实现时，不声明 theme switching 或 dark-mode 管理层存在。

## Event 边界

Widget event 可负责页面切换、文本更新、动画和应用 callback。本文档不引入 MVC、MVVM 或 MVP 等未实现模式。

## 相关内容

- [Input and Events](input-and-events.md)
- [Screen Navigation](screen-navigation.md)
