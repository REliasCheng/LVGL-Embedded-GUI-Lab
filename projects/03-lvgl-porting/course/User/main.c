#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include "USART.h"
#include "I2C.h"

#include "st7789.h"
#include "cst816t.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "bsp_basic_timer.h"

/***********************
任务：模板工程


************************/
void USART0_on_recv(uint8_t* data, uint32_t len) {
  printf("recv[%d]:%s\n", len, data);
}
// 事件回调
void event_handler(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_VALUE_CHANGED) {
    printf("toggled btn\n");
  }
}
void demo_button_checkable(){
  // 获取显示图层
  lv_obj_t* screen = lv_scr_act();
  // 创建按钮
  lv_obj_t* btn = lv_btn_create(screen);
  // 设置按钮尺寸
  lv_obj_set_size(btn, 120, 50);
  
  // 4. 在按钮上创建文本并居中显示
  lv_obj_t* label = lv_label_create(btn);
  lv_label_set_text(label, "Toggle");
  // lv_obj_center(label);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  // 5. 设置按钮可选中
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);

  // 默认选中
//  lv_obj_add_state(btn, LV_STATE_CHECKED);

  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_VALUE_CHANGED, NULL);
  // 居中
  lv_obj_center(btn);
}

int main(void) {
  // 配置全局中断分组
  nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
  // 初始化系统嘀嗒定时器
  systick_config();
  // 初始化USART
  USART_init();
  I2C_init();
  
  // 1. 初始化LVGL
  lv_init();
//  CST816T_Init();
  // 2.显示屏驱动初始化
  lv_port_disp_init();
//  ST7789_Init();
//  ST7789_Test();
  
  // 3. 触摸屏(输入设备要在屏幕初始化之后再init，否则会失效)
  lv_port_indev_init();
  
  // 1000Hz
  // 预分频系数 10
  // Period: SystemCoreClock / 10 / 1000
  basic_timer_config(10, SystemCoreClock / 10 / 1000);
  
  demo_button_checkable();

  while(1) {
    // 4. 每隔x毫秒调用一次心跳
//    lv_tick_inc(1);
    // 5. 执行定时任务（屏幕渲染，事件处理）
		lv_timer_handler();
    
    // 休眠1ms
		delay_1ms(1);
  }
}
