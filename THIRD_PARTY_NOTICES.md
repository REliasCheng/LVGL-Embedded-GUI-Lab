# Third-Party Notices

`projects/**/course/` 保存筛选后的配套参考工程。迁移文件保持原始字节不变，原有版权头和许可证继续适用。仓库根目录的 MIT License 仅适用于本仓库新增的 Markdown 文档、自有 SVG 与后续明确标注的个人代码。

主要第三方内容包括：

- LVGL 8.3.11 core source，遵循所保留的 LVGL license；
- LVGL PC drivers 与 SDL simulator 相关文件，遵循对应组件保留的许可证；
- GigaDevice GD32F4xx device support、CMSIS、标准外设库、启动文件和 Keil 工程定义，归其原权利人所有；
- FreeRTOS V10.5.1 由 Keil 工程引用 ARM CMSIS-FreeRTOS Pack；仓库保留 `FreeRTOSConfig.h` 和 RTE 组件引用，kernel 与 portable layer 由外部 Pack 提供，未复制到公开快照；
- SquareLine Studio 生成的 UI 结构代码，作为参考工程的一部分保留。
- Unscii 非 `unscii-16-full` 字体生成数据，用于 LVGL 内置 ASCII 字体；上游将该变体声明为 Public Domain 或 CC0，notice 与 CC0 文本见 [`third_party/licenses/unscii/`](third_party/licenses/unscii/)。

无法建立再分发依据的生成字体、图标、表盘背景、商品图片和 SquareLine 设计文件未纳入公开迁移。Montserrat / DejaVu / SimSun 与 Font Awesome 混合生成的字体文件已排除。迁移来源、目标路径和 SHA256 见 [SOURCE_SELECTION_MANIFEST.csv](SOURCE_SELECTION_MANIFEST.csv)，复制后的复核结果见 [MIGRATION_HASH_VERIFICATION.csv](MIGRATION_HASH_VERIFICATION.csv)。
