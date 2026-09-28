
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" \
                            issue*/
#include <SDL2/SDL.h>
#include <stdio.h>

#include "lv_drivers/sdl/sdl.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/lvgl.h"
#include "smart_watch.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void demo_obj() {
  // 1. 获取act显示层
  lv_obj_t* screen = lv_scr_act();
  // 2. 在act创建一个对象
  lv_obj_t* obj = lv_obj_create(screen);
  // 3. 设置背景颜色
  lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_PINK), 0);
  // 4. 设备宽100高120
  lv_obj_set_width(obj, 100);
  lv_obj_set_height(obj, 120);
  // 5. 设置位置
  // lv_obj_set_pos(obj, 30, 10);
  // 6. 设置对齐方式
  lv_obj_align(obj, LV_ALIGN_CENTER, 10, 30);
  // 7. 设置透明度
  lv_obj_set_style_bg_opa(obj, LV_OPA_20, 0);
  // 8. 圆角半径
  lv_obj_set_style_radius(obj, 20, 0);
}

// 自定义样式
void demo_style() {
  // 1. 获取act显示层
  lv_obj_t* screen = lv_scr_act();
  // 2. 在act创建一个对象
  lv_obj_t* obj = lv_obj_create(screen);
  // 3. 创建一个可以复用的样式
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_size(&style, 100);
  lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_PURPLE));

  // 将样式添加给对象
  lv_obj_add_style(obj, &style, 0);
  lv_obj_center(obj);
}

// 创建一个label
void demo_label() {
  // 1. 获取act显示层
  lv_obj_t* screen = lv_scr_act();
  // 2. 创建一个label
  lv_obj_t* label = lv_label_create(screen);
  // 3. 设置label的文字
  lv_label_set_text(label, "Hello World ");
  // 4. 设置label的位置
  lv_obj_align(label, LV_ALIGN_TOP_RIGHT, 0, 30);
  // 读取label的文字
  const char* text = lv_label_get_text(label);
  printf("label text: %s\n", text);
}

// 显示中文
void demo_chinese() {
  LV_FONT_DECLARE(alimama30);

  // 1. 获取act显示层
  lv_obj_t* screen = lv_scr_act();
  // 2. 创建一个label
  lv_obj_t* label = lv_label_create(screen);
  // 3. 设置label的文字
  lv_label_set_text(label, "我在黑马学习嵌入式/集成电路");
  lv_obj_set_width(label, 150);
  // 循环滚动
  lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  // lv_obj_set_height(label, 25);

  // 设置字体
  static lv_style_t style;
  lv_style_init(&style);
  // 设置字体
  lv_style_set_text_font(&style, &alimama30);
  // 颜色设置为红色
  lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_RED));
  // 将样式添加给对象
  lv_obj_add_style(label, &style, 0);
}

void btn_event_cb(lv_event_t* e) {
  printf("btn_event_cb\n");

  // 获取事件源对象
  // lv_obj_t *obj = lv_event_get_target(e);
  // printf("obj: %p\n", obj);
  // 获取userdata
  void* user_data = lv_event_get_user_data(e);
  printf("user_data: %d\n", user_data);
}

void demo_button() {
  // 1. 获取act显示层
  lv_obj_t* screen = lv_scr_act();
  // 2. 创建按钮
  lv_obj_t* btn = lv_btn_create(screen);
  // 3. 设置尺寸
  lv_obj_set_size(btn, 100, 50);

  // 4. 在按钮上创建文本并居中显示
  lv_obj_t* label = lv_label_create(btn);
  lv_label_set_text(label, "Button1");
  lv_obj_center(label);
  // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  // 给按钮添加事件
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, (void*)111);
  printf("btn: %p\n", btn);

  // 创建Button2
  lv_obj_t* btn2 = lv_btn_create(screen);
  lv_obj_set_size(btn2, 100, 50);
  lv_obj_set_pos(btn2, 0, 70);
  lv_obj_t* label2 = lv_label_create(btn2);
  lv_label_set_text(label2, "Button2");
  lv_obj_center(label2);
  // 添加事件
  lv_obj_add_event_cb(btn2, btn_event_cb, LV_EVENT_CLICKED, (void*)222);
  printf("btn2: %p\n", btn2);
}

// 事件回调
void event_handler(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_VALUE_CHANGED) {
    printf("toggled btn\n");
  }
}

void demo_button_checkable() {
  // 1. 获取act显示层
  lv_obj_t* screen = lv_scr_act();
  // 2. 创建按钮
  lv_obj_t* btn = lv_btn_create(screen);
  // 3. 设置尺寸
  lv_obj_set_size(btn, 100, 50);

  // 4. 在按钮上创建文本并居中显示
  lv_obj_t* label = lv_label_create(btn);
  lv_label_set_text(label, "Toggle");
  // lv_obj_center(label);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  // 5. 设置按钮可选中
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);

  // 默认选中
  lv_obj_add_state(btn, LV_STATE_CHECKED);

  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_VALUE_CHANGED, NULL);
}

// image图片
void demo_img() {
  // 转换链接：https://lvgl.io/tools/imageconverter
  LV_IMG_DECLARE(img_avatar);
  // 1. 获取act显示层
  lv_obj_t* screen = lv_scr_act();
  // 2. 创建图片
  lv_obj_t* img = lv_img_create(screen);
  // 3. 设置图片源
  lv_img_set_src(img, &img_avatar);
}

// gif动画
void demo_gif() {
  // 转换链接：https://lvgl.io/tools/imageconverter
  LV_IMG_DECLARE(astronaut_ezgif);
  // 1. 获取act显示层
  lv_obj_t* screen = lv_scr_act();
  // 2. 创建图片gif
  lv_obj_t* img = lv_gif_create(screen);
  // 设置 gif 图片源
  lv_gif_set_src(img, &astronaut_ezgif);
}

void event_handler2(lv_event_t* e) {
  int code = lv_event_get_code(e);
  lv_obj_t* target = lv_event_get_target(e);

  if (code == LV_EVENT_VALUE_CHANGED) {
    uint16_t selected_btn_index = lv_btnmatrix_get_selected_btn(target);
    const char* text = lv_btnmatrix_get_btn_text(target, selected_btn_index);
    printf("target: %p ,selceted:%d ,text:%s\n", target, selected_btn_index,
           text);
    printf("clicked\n");
  }
}

void demo_button_matrix() {
  static const char* map[] = {"0", "1", "2", "3",  "4",    "\n",    "5", "6",
                              "7", "8", "9", "\n", "back", "Enter", ""};

  // 创建矩阵按钮
  lv_obj_t* btnm = lv_btnmatrix_create(lv_scr_act());
  // 设置矩阵按钮的显示
  lv_btnmatrix_set_map(btnm, map);
  lv_obj_set_width(btnm, 220);
  lv_obj_align(btnm, LV_ALIGN_CENTER, 0, 0);
  // 设置按钮宽度
  // lv_btnmatrix_set_btn_width(btnm,1,3);
  lv_obj_add_event_cb(btnm, event_handler2, LV_EVENT_ALL, NULL);
}
void ta_event_cb(lv_event_t* e) {
  // 事件码： 用于区分是什么事件（Focused)
  lv_event_code_t code = lv_event_get_code(e);
  // 组件：触发事件组件
  lv_obj_t* target = lv_event_get_target(e);
  // user data
  lv_obj_t* kb = lv_event_get_user_data(e);
  if (code == LV_EVENT_FOCUSED) {  // 有组件得到焦点了
    printf("Focused: %d\n", kb);

    // 将键盘和textarea关联
    lv_keyboard_set_textarea(kb, target);
  }
}

void demo_keyboard() {
  /*创建键盘*/
  lv_obj_t* kb = lv_keyboard_create(lv_scr_act());

  /*创建文本域*/
  lv_obj_t* ta = lv_textarea_create(lv_scr_act());
  // top left
  lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, 10);
  // callback
  lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_FOCUSED, kb);
  // 设置文本域为单行
  lv_textarea_set_one_line(ta, true);
  lv_textarea_set_password_mode(ta, true);
  // 设置大小140
  lv_obj_set_width(ta, 120);
  // lv_obj_set_size(ta, 140, 80);

  lv_obj_t* ta2 = lv_textarea_create(lv_scr_act());
  // top right
  lv_obj_align(ta2, LV_ALIGN_TOP_RIGHT, -10, 10);
  // event callback
  lv_obj_add_event_cb(ta2, ta_event_cb, LV_EVENT_FOCUSED, kb);
  lv_obj_set_width(ta2, 120);

  // 将键盘和textarea关联
  lv_keyboard_set_textarea(kb, ta);
}

void demo_flex() {
  // 1. 创建obj
  lv_obj_t* flex_layout = lv_obj_create(lv_scr_act());
  // 2. 指定布局方式
  // lv_obj_set_flex_flow(flex_layout, LV_FLEX_FLOW_ROW); // 水平排列
  // lv_obj_set_flex_flow(flex_layout, LV_FLEX_FLOW_ROW_WRAP); // 水平排列,
  // 自动换行 lv_obj_set_flex_flow(flex_layout, LV_FLEX_FLOW_COLUMN); //
  // 垂直排列
  lv_obj_set_flex_flow(flex_layout,
                       LV_FLEX_FLOW_COLUMN_WRAP);  // 垂直排列, 自动换行
  // 3. 设置宽高
  lv_obj_set_size(flex_layout, 300, 300);

  // 添加10个按钮
  for (int i = 0; i < 16; i++) {
    // 在布局中创建按钮
    lv_obj_t* btn = lv_btn_create(flex_layout);
    // 设置宽高
    lv_obj_set_size(btn, LV_SIZE_CONTENT, 40);
    // 创建文本
    lv_obj_t* label = lv_label_create(btn);
    // 设置文本内容
    // lv_label_set_text(label, "Button1");
    lv_label_set_text_fmt(label, "Button: %d", i);

    lv_obj_center(label);
  }
}

// 网格布局
void demo_grid() {
  static lv_coord_t col_dsc[] = {70, 70, 70, LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {50, 50, 50, LV_GRID_TEMPLATE_LAST};

  /*Create a container with grid*/
  lv_obj_t* cont = lv_obj_create(lv_scr_act());
  // 设置网格列描述
  lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
  // 设置网格行描述
  lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
  // 设置网格的宽度和高度
  lv_obj_set_size(cont, 300, 220);
  lv_obj_center(cont);
  // 设置布局方式: 网格
  lv_obj_set_layout(cont, LV_LAYOUT_GRID);

  lv_obj_t* label;
  lv_obj_t* obj;

  uint32_t i;
  for (i = 0; i < 9; i++) { // 0,1,2,3,4,5,6,7,8
    uint8_t col = i % 3;  // 0,1,2, 0,1,2, 0,1,2
    uint8_t row = i / 3;  // 0,0,0, 1,1,1, 2,2,2

    if(col == 2 && row == 1) continue;

    obj = lv_btn_create(cont);

    /*Stretch the cell horizontally and vertically too
     *Set span to 1 to make the cell 1 column/row sized*/
    if(col == 0 && row == 1){
      lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 1, // col_span
                                LV_GRID_ALIGN_STRETCH, row, 2);  // row_span
    } else if (col == 1 && row == 1){
      lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 2, // col_span
                                LV_GRID_ALIGN_STRETCH, row, 1);  // row_span
    } else {
      lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 1, // col_span
                                LV_GRID_ALIGN_STRETCH, row, 1);  // row_span
    }
    label = lv_label_create(obj);
    lv_label_set_text_fmt(label, "c%d, r%d", col, row);
    lv_obj_center(label);
  }
}

lv_obj_t* page1;
lv_obj_t* page2;

void page_event_cb(lv_event_t* e){
  // 获取事件源对象
  // lv_obj_t* page = lv_event_get_target(e);
  // if (page == page1){
  //   // 将page2加载到显示层
  //   lv_disp_load_scr(page2);
  // }else if(page == page2){
  //   // 将page1加载到显示层
  //   lv_disp_load_scr(page1);
  // }

  // 从user_data中获取目标对象
  lv_disp_load_scr(lv_event_get_user_data(e));
}

void create_page1(void){
  // 1. 创建obj
  page1 = lv_obj_create(NULL);
  // 2. 设置背景色
  lv_obj_set_style_bg_color(page1, lv_palette_main(LV_PALETTE_PINK), 0);
  // 创建page1文字居中
  lv_obj_t* label = lv_label_create(page1);
  lv_label_set_text(label, "Page1");
  lv_obj_center(label);
}

void create_page2(void){
  // 1. 创建obj
  page2 = lv_obj_create(NULL);
  // 2. 设置背景色
  lv_obj_set_style_bg_color(page2, lv_palette_main(LV_PALETTE_PURPLE), 0);
  // 创建page1文字居中
  lv_obj_t* label = lv_label_create(page2);
  lv_label_set_text(label, "Page2");
  lv_obj_center(label);
}
// 页面及跳转
void demo_page( void ){
  create_page1();
  create_page2();

  // 给page1添加点击事件
  lv_obj_add_event_cb(page1, page_event_cb, LV_EVENT_CLICKED, page2);
  // 给page2添加点击事件
  lv_obj_add_event_cb(page2, page_event_cb, LV_EVENT_CLICKED, page1);

  // 将page1加载到显示层
  lv_disp_load_scr(page1);
}
void init_tab(lv_obj_t* tab, char* name){
  // 随机生成一个颜色
  // lv_color_t color = lv_color_hex(rand() % 0xffffff);

  // page
  lv_obj_t* page = lv_obj_create(tab);
  // 设置背景色
  lv_obj_set_style_bg_color(page, lv_palette_main(LV_PALETTE_BLUE), 0);
  // 设置宽高(百分比)
  lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));

  // label
  lv_obj_t* label = lv_label_create(page);
  lv_label_set_text(label, name);
  lv_obj_center(label);
}

// 标签、选项卡tabview
void demo_tabview( void ){
      /*Create a Tab view object*/
    lv_obj_t * tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 50);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Tab 3");

    init_tab(tab1, "Label Tab 1");
    init_tab(tab2, "Label Tab 2");
    init_tab(tab3, "Label Tab 3");
}

void demo_chart(){
  lv_obj_t* chart = lv_chart_create(lv_scr_act());
  // 设置宽高300x250
  lv_obj_set_size(chart, 300, 250);
  // 设置表格类型
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
  // 设置居中显示
  lv_obj_align(chart, LV_ALIGN_CENTER, 0, 0);

  lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 40);
  lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 10, 1, true, 30);
    
  // 刷新表格尺寸
  lv_obj_refresh_ext_draw_size(chart);

  // 添加数据序列
   lv_chart_series_t * ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
   // 设置Y轴刻度范围
   lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 3, 100);
   // 随机生成30个[10, 90]的数值, 并添加到chart的ser1
   for(int i = 0; i < 30; i++){
      lv_chart_set_next_value(chart, ser1, lv_rand(10, 90));
   }
    // 设置x缩放
  //  lv_chart_set_zoom_x(chart, 500);
   // 刷新表格
   lv_chart_refresh(chart);
}

void anim_property_cb(void * var, int32_t value) {
  printf("anim_property_cb: %d\n", value);
  // 设置颜色
  lv_obj_set_style_bg_color(var, lv_color_hsv_to_rgb(13, 96, value), 0);
  // 修改位置 x -> [0, 100]
  // lv_obj_set_x(var, value);
  // 尺寸变化
  // lv_obj_set_size(var, value, value);
}

void demo_anim(){

  // 创建obj
  lv_obj_t* obj = lv_obj_create(lv_scr_act());
  // 设置颜色
  lv_obj_set_style_bg_color(obj, lv_color_hsv_to_rgb(13, 96, 80), 0);

  // 创建动画
  lv_anim_t a;
  lv_anim_init(&a);
  // 设置动画播放的对象
  lv_anim_set_var(&a, obj);
  // 设置动画时间
  lv_anim_set_time(&a, 2000);

  // 设置反向动画
  lv_anim_set_playback_delay(&a, 500);
  // 反向动画播放时间，通常和正向相同
  lv_anim_set_playback_time(&a, 2000);

  // 设置动画播放重复次数
  lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); // INFINITE无限

  // 设置动画变化值 0 -> 100
  lv_anim_set_values(&a, 10, 100);
  // 设置动画变化函数（执行回调)
  lv_anim_set_exec_cb(&a, anim_property_cb);
  // 开启动画
  lv_anim_start(&a);
}

int main(int argc, char** argv) {
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();

  //  lv_example_switch_1();
  //  lv_example_calendar_1();
  //  lv_example_btnmatrix_2();
  //  lv_example_checkbox_1();
  //  lv_example_colorwheel_1();
  //  lv_example_chart_6();
  //  lv_example_table_2();
  //  lv_example_scroll_2();
  //  lv_example_textarea_1();
  //  lv_example_msgbox_1();
  //  lv_example_dropdown_2();
  //  lv_example_btn_1();
  //  lv_example_scroll_1();
  //  lv_example_tabview_1();
  //  lv_example_tabview_1();
  //  lv_example_flex_3();
  //  lv_example_label_1();

  // lv_demo_widgets();
  // lv_demo_music();
  // lv_demo_benchmark();
  // lv_demo_stress();
  // ------------------------------------------------------------1
  // lv_obj_t* btn = lv_btn_create(lv_scr_act());
  // // 设置按钮位置
  // lv_obj_set_pos(btn, 10, 30);
  // // 设置按钮大小
  // lv_obj_set_size(btn, 100, 50);

  // demo_obj();
  // demo_style();
  // demo_label();
  // demo_chinese();
  // demo_button();
  // demo_button_checkable();
  // demo_img();
  // demo_gif();
  // demo_button_matrix();
  // lv_example_textarea_1();
  // demo_keyboard();
  // ------------------------------------------------------------2
  // demo_flex();
  // demo_grid();
  // demo_page();
  // demo_tabview();
  // demo_chart();
  // demo_anim();
  // lv_example_list_1();

  smart_watch_init();

  uint32_t cnt = 0;
  while (1) {
    // 1000ms更新一下时间
    if(cnt++ >= 200){
      cnt = 0;
      smart_watch_update();
    }

    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_timer_handler();
    usleep(5 * 1000); // 5ms
  }

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static void hal_init(void) {
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a
   * display*/
  sdl_init();

  /*Create a display buffer*/
  static lv_disp_draw_buf_t disp_buf1;
  static lv_color_t buf1_1[SDL_HOR_RES * 100];
  lv_disp_draw_buf_init(&disp_buf1, buf1_1, NULL, SDL_HOR_RES * 100);

  /*Create a display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf1;
  disp_drv.flush_cb = sdl_display_flush;
  disp_drv.hor_res = SDL_HOR_RES;
  disp_drv.ver_res = SDL_VER_RES;

  lv_disp_t* disp = lv_disp_drv_register(&disp_drv);

  lv_theme_t* th = lv_theme_default_init(
      disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
      LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
  lv_disp_set_theme(disp, th);

  lv_group_t* g = lv_group_create();
  lv_group_set_default(g);

  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  static lv_indev_drv_t indev_drv_1;
  lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
  indev_drv_1.type = LV_INDEV_TYPE_POINTER;

  /*This function will be called periodically (by the library) to get the mouse
   * position and state*/
  indev_drv_1.read_cb = sdl_mouse_read;
  lv_indev_t* mouse_indev = lv_indev_drv_register(&indev_drv_1);

  static lv_indev_drv_t indev_drv_2;
  lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
  indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv_2.read_cb = sdl_keyboard_read;
  lv_indev_t* kb_indev = lv_indev_drv_register(&indev_drv_2);
  lv_indev_set_group(kb_indev, g);

  static lv_indev_drv_t indev_drv_3;
  lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
  indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
  indev_drv_3.read_cb = sdl_mousewheel_read;
  lv_indev_t* enc_indev = lv_indev_drv_register(&indev_drv_3);
  lv_indev_set_group(enc_indev, g);

  /*Set a cursor for the mouse*/
  LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t* cursor_obj =
      lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj, &mouse_cursor_icon); /*Set the image source*/
  lv_indev_set_cursor(mouse_indev,
                      cursor_obj); /*Connect the image  object to the driver*/
}
