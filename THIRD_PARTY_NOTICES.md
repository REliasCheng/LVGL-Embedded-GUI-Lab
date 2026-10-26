# Third-Party Notices

## LVGL

- Upstream: https://github.com/lvgl/lvgl
- Version: v9.6.0
- Commit: `80ca777e37a2b176770726a02e07a6fb79ef0b39`
- License: MIT, retained in the downloaded upstream source.
- Integration: `third_party/lvgl` is a Git submodule pinned by Git tree SHA. Upstream files retain their own headers and license.
- Fonts/widgets: only the LVGL built-in default font and widgets are used.

## SDL2

- Upstream: https://github.com/libsdl-org/SDL
- License: zlib license for SDL2.
- Integration: system development package discovered by `pkg-config`; no SDL2 source or binary is committed here.

## Repository-owned work

The dashboard model, UI, host test backend, build configuration and documentation are original work under the repository MIT license. The root license does not relicense LVGL or SDL2.

Historic course GUI code, SquareLine output, unknown-rights bitmap fonts, icons, images, vendor packages and earlier source material are excluded. Earlier Git commits remain reachable because history was not rewritten.
