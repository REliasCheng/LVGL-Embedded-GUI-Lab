# CMSIS Pack SmartWatch Reference

## 定位

该工程保留同一 SmartWatch UI 在 CMSIS Pack / RTE 工程组织方式下的接口关系，作为 GD32 主线的结构参考，不与裸机和 FreeRTOS 主线平级展示。

## 关键差异

- LVGL configuration 和 port template 位于 RTE 目录。
- Display/Input 仍连接 ST7789 与 CST816T。
- UI 行为与 bare-metal SmartWatch 高度重复。

未知授权视觉资源、SquareLine 设计文件和构建输出未迁移；该快照不作为完整视觉资源包。
