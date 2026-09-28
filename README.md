# LVGL 嵌入式 GUI 实验室
## LVGL Embedded GUI Lab

基于 LVGL V8.3.11 与 GD32F407VE / ARM Cortex-M4，围绕显示移植、触摸输入、渲染缓冲、事件系统和多页面 GUI 组织的嵌入式图形开发仓库。

![LVGL system stack](assets/images/architecture/lvgl-system-stack.svg)

**GD32F407VE / Cortex-M4** · **LVGL V8.3.11** · **ST7789 240 × 280** · **CST816T** · **5 mainline + 1 reference**

## 👋 项目简介 | Overview

仓库从 PC SDL GUI simulation 进入 GD32 显示与触摸 bring-up，再连接 LVGL port、Widget/Event、多页面 UI 和 FreeRTOS 工程组织。核心不是罗列 Widget API，而是说明 GUI 从输入、对象系统到物理显示的完整数据路径。

```text
PC SDL Simulator
        ↓
Display / Touch Bring-up
        ↓
LVGL Porting
        ↓
Widget / Event / Screen Navigation
        ↓
Bare-metal / CMSIS Pack / FreeRTOS Integration
```

## ⚙ 技术范围 | Technical Scope

### 🖥 Display Pipeline

LVGL Renderer · Draw Buffer · Flush Callback · SPI0 · ST7789 · RGB565

### 👆 Input & Events

CST816T · LVGL Pointer Device · Event Callback · Widget Interaction

### 🎨 UI System

Widget · Style · Layout · Screen · Navigation

### 🧠 Porting & Runtime

Display/Input Port · Tick · `lv_timer_handler()` · Bare-metal · FreeRTOS Integration

### 💻 PC Simulation

SDL Display · Mouse · Keyboard · Mouse-wheel Encoder

## 🖥 显示链路 | Display Pipeline

![Display pipeline](assets/images/diagram/display-pipeline.svg)

LVGL 先把失效区域渲染到两个 `240 × 10` 像素的局部 draw buffer，再由 flush callback 调用 ST7789 驱动，经 SPI0 同步写入 240 × 280 LCD。当前主线是 polling / synchronous flush，不包含 GD32 DMA、DMA2D、LTDC 或 GPU acceleration。

详细说明：[Display Pipeline](docs/display-pipeline.md) · [Rendering and Buffer](docs/rendering-and-buffer.md)

## 👆 输入与事件 | Input & Events

![Input event flow](assets/images/diagram/input-event-flow.svg)

CST816T 驱动提供触摸状态与坐标，LVGL input read callback 将其转换为 pointer device 数据；Event 再连接 Widget callback 与页面状态。PC simulator 以 SDL mouse、keyboard 和 mouse-wheel encoder 提供同一 LVGL input abstraction。

详细说明：[Input and Events](docs/input-and-events.md)

## ⌚ SmartWatch 工程族 | Project Family

同一套四页面 SmartWatch UI 以不同运行环境和工程组织方式保留，不描述为一个连续升级完成的产品：

```text
PC SDL Simulator        desktop GUI execution and input mapping
Bare-metal GD32         super loop, timer tick and hardware callbacks
CMSIS Pack Reference    RTE / Pack project organization
FreeRTOS Integration    GUI update task, handler task and tick hook
```

页面代码使用 `ui_Screen1` 至 `ui_Screen4`。部分 callback 直接访问 LED 等硬件接口，仓库按现有结构记录，不引入源码中不存在的 MVC/MVVM 分层。FreeRTOS 变体未发现 GUI mutex，因此不描述为 thread-safe LVGL integration。

## 🚀 核心工程 | Featured Projects

### [💻 PC SDL Simulator](projects/01-pc-simulator/)

通过 SDL display/input 在桌面环境运行 LVGL UI 逻辑与事件处理，不模拟 MCU 硬件。

`SDL` / `LVGL` / `Mouse` / `Keyboard`

### [🖥 Display & Touch Bring-up](projects/02-display-touch-bringup/)

连接 GD32F407VE、ST7789 显示和 CST816T 触摸的底层驱动链路。

`SPI0` / `ST7789` / `CST816T`

### [🧩 LVGL Porting](projects/03-lvgl-porting/)

通过 Display、Input、Tick 与 Handler 接口连接 LVGL Core 和 MCU BSP。

`Porting` / `Draw Buffer` / `Flush Callback` / `Tick`

### [⌚ Bare-metal SmartWatch](projects/04-baremetal-smartwatch/)

在裸机运行环境中组织四页面 UI、Widget event、RTC 更新和硬件 callback。

`Screen` / `Event` / `Widget`

### [⚙ FreeRTOS SmartWatch](projects/05-rtos-smartwatch/)

记录 FreeRTOS V10.5.1 工程中的 GUI update task、handler task 与 tick hook。

`FreeRTOS` / `GUI Task` / `LVGL`

### [📦 CMSIS Pack Reference](projects/reference/cmsis-pack-smartwatch/)

保留同一 GUI 在 CMSIS Pack / RTE 工程组织中的参考实现。

`CMSIS Pack` / `RTE` / `Reference`

## 📂 工程结构 | Repository Structure

```text
assets/images/       自有架构与数据流 SVG
docs/                移植、显示、输入、UI 与 RTOS 机制说明
projects/            5 个主线工程和 1 个参考工程
  */course/          保持原始字节的白名单工程快照
SOURCE_SELECTION_MANIFEST.csv
MIGRATION_HASH_VERIFICATION.csv
```

## 🛠 开发环境 | Development Environment

- LVGL V8.3.11
- GD32F407VE / ARM Cortex-M4
- Keil MDK-ARM / GigaDevice GD32F4xx DFP
- GD32 Standard Peripheral Library
- GCC / CMake / SDL2
- SquareLine Studio 1.4.1 generated UI structure
- FreeRTOS V10.5.1（单一 GD32 变体）

PC SDL 工程在 CMake 配置阶段因本机缺少可发现的 SDL2 package 而停止，尚未进入源码编译。当前环境未发现 `UV4.exe`，5 个 Keil 工程未执行自动构建。工程文件完整和迁移哈希一致不等同于编译或板端运行通过。

## 📖 技术文档 | Documentation

- [LVGL Porting](docs/lvgl-porting.md)
- [Display Pipeline](docs/display-pipeline.md)
- [Rendering and Buffer](docs/rendering-and-buffer.md)
- [Input and Events](docs/input-and-events.md)
- [Widgets and Layout](docs/widgets-and-layout.md)
- [Screen Navigation](docs/screen-navigation.md)
- [Fonts and Images](docs/fonts-and-images.md)
- [FreeRTOS Integration](docs/rtos-integration.md)
- [Development Environment](docs/development-environment.md)

## 🔗 技术边界 | Repository Boundaries

- [ARM Cortex-M Development Lab](https://github.com/REliasCheng/ARM-Cortex-M-Development-Lab)：MCU 外设、中断和固件层。
- [FreeRTOS Embedded Lab](https://github.com/REliasCheng/FreeRTOS-Embedded-Lab)：任务调度、IPC、同步和 ISR-to-Task。
- 本仓库：Display、Input、Rendering、Widget、Event、Screen 与 MCU GUI integration；不描述为 Embedded Linux GUI。

## 📜 来源与许可 | License

仓库新增文档和自有 SVG 使用根目录 [MIT License](LICENSE)。参考工程及第三方组件继续适用其原有声明，具体边界见 [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md)。公开快照仅保留已核对许可的 Unscii ASCII 生成字体；无法建立再分发依据的其他生成字体、图标、表盘背景和商品图片未纳入仓库。
