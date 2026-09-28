# 字体与图片 | Fonts and Images

## 资源链

```text
TTF / OTF                  PNG / JPG / GIF
    ↓ converter                 ↓ converter / builder
LVGL Font C/BIN            LVGL Image Descriptor
    ↓                           ↓
Widget Text                 Image / GIF Widget
```

资料中存在 TTF 字体、转换后的字体 C 文件、image C array、图标、表盘背景和 GIF。部分资源由 SquareLine Studio 生成代码引用。

## 公开迁移规则

- 有明确许可证且工程确实需要的上游代码可保留；当前仅保留经官方来源核对的 Unscii ASCII 生成字体。
- 授权信息不明确的字体、图标、表盘背景和商品图片不迁移。
- 从授权不明素材转换出的 `ui_img_*`、`ui_font_*` 和同类资源数组也不迁移。
- 不使用课程封面、商品图或上游 demo screenshot 代替本地运行证据。

因此 SmartWatch 工程公开目录保留 screen、event 和 callback 结构，但不是包含全部视觉资源的独立构建包。

LVGL 内置 Montserrat / DejaVu / SimSun 与 Font Awesome 混合生成文件未进入公开快照；公开仓库保留的 Unscii notice 位于 [`third_party/licenses/unscii/`](../third_party/licenses/unscii/)。

## 后续补充条件

真实补充 UI 图片前，需要同时满足：来源可追溯、许可允许公开、截图来自可复现工程。当前仓库没有发布 UI screenshot。
