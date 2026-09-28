#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include "USART.h"
#include "I2C.h"

#include "st7789.h"
#include "cst816t.h"
#include "led.h"

#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "bsp_basic_timer.h"
#include "ui.h"

#include "FreeRTOS.h"
#include "task.h"

/***********************
任务：模板工程


************************/

TaskHandle_t            xStartTask_Handler;
TaskHandle_t            xTaskLVGL_Handler;
TaskHandle_t            xTaskTimer_Handler;


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
void demo_button_checkable() {
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



// 十位取出左移4位 + 个位 (得到BCD数)
#define WRITE_BCD(val) 	((val / 10) << 4) + (val % 10)
// 将高4位乘以10 + 低四位 (得到10进制数)
#define READ_BCD(val) 	(val >> 4) * 10 + (val & 0x0F)

static void RTC_config() {
  // 电池管理加载
  rcu_periph_clock_enable(RCU_PMU);
  pmu_backup_write_enable();

  // 重置备份域（不重置可能导致无法设置晶振，出现不走字情况）
  /* reset backup domain */
  rcu_bkp_reset_enable();
  rcu_bkp_reset_disable();

  // 2. 设置时钟的晶振 HXTAL -> 8M
  rcu_osci_on(RCU_HXTAL);
  // 等待晶振稳定
  rcu_osci_stab_wait(RCU_HXTAL);
  /* 给rtc配置晶振 configure the RTC clock source selection */
  rcu_rtc_clock_config(RCU_RTCSRC_HXTAL_DIV_RTCDIV);
  // 分频系数（HXTAL时，需要配置） // DIV25 -> 320K
  rcu_rtc_div_config(RCU_RTC_HXTAL_DIV25);

  // RTC功能加载
  rcu_periph_clock_enable(RCU_RTC);
  rtc_register_sync_wait();

  rtc_parameter_struct rps;
  rps.year = WRITE_BCD(24);
  rps.month = WRITE_BCD(6);
  rps.date = WRITE_BCD(17);
  rps.day_of_week = WRITE_BCD(0);
  rps.hour = WRITE_BCD(14);
  rps.minute = WRITE_BCD(54);
  rps.second = WRITE_BCD(55);
  rps.display_format = RTC_24HOUR;
  rps.am_pm = RTC_AM;
  // 配置异步和同步分频器数值HXTAL_DIV25
  rps.factor_asyn = 127;   // 7位异步预分频器， 0x0 - 0x7F
  rps.factor_syn  = 2499;   // 15位同步预分频器。0x0 - 0x7FFF

  rtc_init(&rps);
}


void update_screen_led_state() {
  int state = led_get_state();
  // 修改屏幕上LED透明度：亮255， 灭50
  lv_opa_t value = state ? 255 : 50;
  lv_obj_set_style_bg_opa(ui_Panel6, value, 0);

}

void on_led_btn_clicked(lv_event_t * e)
{
  // Your code here
  // 把真正的LED灯点亮或熄灭
  led_toggle();

  // 再根据现有LED状态，更新屏幕上的LED
  printf("led_state: %d\n", led_get_state());

  update_screen_led_state();
}

void vApplicationTickHook() {
  /* 执行功能 */
  lv_tick_inc(1);
}

void task_lvgl(void * pvParameters) {

  // 1. 初始化LVGL
  lv_init();
  // 2.显示屏驱动初始化
  lv_port_disp_init();
  // 3. 触摸屏(输入设备要在屏幕初始化之后再init，否则会失效)
  lv_port_indev_init();

//  demo_button_checkable();
  // LVGL ui init
  ui_init();

  update_screen_led_state();
  // 将gif图片加载到gifPanel里

  // 显示外星人转动动画
  LV_IMG_DECLARE(man);
  // 2. 创建gif
  lv_obj_t* gif = lv_gif_create(ui_gifPanel);
  // 3. 设置
  lv_gif_set_src(gif, &man);

  while(1) {
    //RTC_read();
    rtc_parameter_struct rps;
    rtc_current_time_get(&rps);

    uint16_t year = READ_BCD(rps.year) + 2000;
    uint8_t month = READ_BCD(rps.month);
    uint8_t day   = READ_BCD(rps.date);
    uint8_t wday  = READ_BCD(rps.day_of_week);
    uint8_t hour  = READ_BCD(rps.hour);
    uint8_t minute = READ_BCD(rps.minute);
    uint8_t second = READ_BCD(rps.second);
    printf("%4d-%02d-%02d %d %02d:%02d:%02d\r\n",
           year, month, day, wday, hour, minute, second);
    // 1. 小时:分钟更新
    lv_label_set_text_fmt(ui_labelClock, "%02d   %02d", hour, minute);

    // 2. 分钟表针旋转 [0, 60) -> [0, 3600)
    int16_t angle_minutes = (int16_t)((minute * 1.0f / 60.0f) * 3600.0f);
    lv_img_set_angle(ui_min, angle_minutes);

    // 3. 时钟指针旋转 [0, 12) -> [0, 3600) 考虑分钟增量
    int16_t angle_hours = (int16_t)((hour * 1.0f / 12.0f) * 3600.0f) + (int16_t)((minute * 1.0f / 60.0f) * 300.0f);
    lv_img_set_angle(ui_hour, angle_hours);

    // 休眠500ms
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void task_timer_handler(void * pvParameters) {
  while(1) {
    // 5. 执行定时任务（屏幕渲染，事件处理）
    lv_timer_handler();
    // 休眠1ms
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}

void sys_init() {
  // 初始化USART
  USART_init();
  I2C_init();
  RTC_config();
  led_init();
}

void vStartTask(void * pvParameters) {
  sys_init();

  printf("task start!\n");

  taskENTER_CRITICAL();
  // 临界区代码
  // 创建3个子任务
  xTaskCreate(
    (TaskFunction_t) task_lvgl,        // 任务函数的指针，函数名
    (const char * ) "taskKey",         // 任务名称，最大长度：configMAX_TASK_NAME_LEN
    (uint16_t)      1024,              // 任务栈大小，单位：半字Half Word 128*2 / 字Word
    (void*)         NULL,              // 任务函数的参数：通常NULL
    (UBaseType_t)   6,                 // 任务优先级，数值越大，优先级越高
    (TaskHandle_t *)&xTaskLVGL_Handler  // 任务句柄
  );

  xTaskCreate(
    (TaskFunction_t) task_timer_handler,// 任务函数的指针，函数名
    (const char * ) "task1",            // 任务名称，最大长度：configMAX_TASK_NAME_LEN
    (uint16_t)      512,                // 任务栈大小，单位：半字Half Word 128*2 / 字Word
    (void*)         NULL,               // 任务函数的参数：通常NULL
    (UBaseType_t)   10,                 // 任务优先级，数值越大，优先级越高
    (TaskHandle_t *)&xTaskTimer_Handler // 任务句柄
  );
  taskEXIT_CRITICAL();

  // 销毁自己
  vTaskDelete(NULL);


}

int main(void) {
  nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
  // 不要初始化系统嘀嗒定时器

  // 创建任务
  BaseType_t rst = xTaskCreate(
                     (TaskFunction_t) vStartTask,        // 任务函数的指针，函数名
                     (const char * ) "start_task",       // 任务名称，最大长度：configMAX_TASK_NAME_LEN
                     (uint16_t)      128,                // 任务栈大小，单位：半字Half Word 128*2 / 字Word
                     (void*)         NULL,               // 任务函数的参数：通常NULL
                     (UBaseType_t)   1,                  // 任务优先级，数值越大，优先级越高
                     (TaskHandle_t *)&xStartTask_Handler  // 任务句柄
                   );
  // rst: pdPASS成功，pdFAIL失败

  // 开启任务调度
  vTaskStartScheduler();

  while(1) {};
}

