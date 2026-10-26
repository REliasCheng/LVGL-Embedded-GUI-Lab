# Provenance and scope

| Material reviewed | Classification | Use in this host runtime |
| --- | --- | --- |
| Existing repository architecture text and SVG diagrams | USER_ORIGINAL | Preserved as historical design documentation. |
| Official LVGL v9.6.0 source | LICENSED_REUSABLE | Git submodule at the pinned official commit; MIT terms remain with upstream. |
| SDL2 system package | LICENSED_REUSABLE | Build-time/runtime host dependency under its zlib license; no files vendored. |
| Historic LVGL v8.3.11 application and GD32 display/touch sketches | REFERENCE_ONLY | Used to understand intended boundaries; no source copied. v9 API was checked against the pinned headers. |
| SquareLine project, course GUI, bitmap fonts, icons and images with incomplete rights chain | RIGHTS_UNVERIFIED | Excluded. The dashboard layout and C sources are new, and only built-in LVGL widgets/font are used. |
| Historic tool output and compile records | BUILD_EVIDENCE_ONLY | They do not establish this v9 host build or any target/hardware result. |

The target board references are GD32F407VE, ST7789 240 × 280 SPI display, CST816T touch, and FreeRTOS. Current replacements are host SDL display, host pointer, and single-thread tick/handler loop. Target adapters must provide their own flush and asynchronous completion lifetime, input coordinate mapping, GUI task ownership, memory and stack sizing, and board evidence. Host validation cannot establish those results.
