# 字体与图片 | Fonts and Images

## 资源链

```text
TTF / OTF                  PNG / JPG / GIF
    ↓ converter                 ↓ converter / builder
LVGL Font C/BIN            LVGL Image Descriptor
    ↓                           ↓
Widget Text                 Image / GIF Widget
```

字体、图片、图标和 GIF 可被转换为 LVGL 资源数组，但转换行为不会产生原素材的再分发权。

## 公开迁移规则

- 只有许可证明确、用途相容且工程确实需要的上游资源才可纳入。
- 授权信息不明确的字体、图标、表盘背景和商品图片不迁移。
- 从授权不明素材转换出的 `ui_img_*`、`ui_font_*` 和同类资源数组也不迁移。
- 不使用课程封面、商品图或上游 demo screenshot 代替本地运行证据。

当前默认分支不包含字体、图标、表盘、UI 截图、SquareLine 工程或转换后的资源数组。

## 相关内容

- [Screen Navigation](screen-navigation.md)

## 公开证据边界

当前仓库没有发布 UI screenshot。后续补充前需同时满足来源可追溯、许可允许公开、截图来自可复现工程。
