#include "smart_watch.h"

#include <stdio.h>
#include <time.h>

#include "SmartWatch_UI/ui.h"
#include "lvgl/lvgl.h"

void smart_watch_init(void) {
  // 初始化自定义的SmartWatch UI
  ui_init();

  smart_watch_update();
}

void smart_watch_update(void) {
  // 更新表盘显示
  // 获取当前时间的时间戳
  time_t currentTime;
  time(&currentTime);

  // 使用localtime函数将时间戳转换为struct tm结构体的副本
  struct tm localTime;

  localtime_s(&localTime, &currentTime);  // 在Windows上使用localtime_s

  // 提取年、月、日、时、分和秒
  int year = localTime.tm_year + 1900;  // 年份是从1900年开始的
  int month = localTime.tm_mon + 1;  // 月份是从0开始的，所以要加1
  int day = localTime.tm_mday;
  int hour = localTime.tm_hour;
  int minute = localTime.tm_min;
  int second = localTime.tm_sec;
  int wday = localTime.tm_wday;  // 星期几 星期天为0

  // 打印当前年、月、日、时、分和秒
  printf("Current date and time: %d-%02d-%02d %02d:%02d:%02d\n", 
            year, month, day, hour, minute, second);

  // 1. 小时:分钟更新
  lv_label_set_text_fmt(ui_labelClock, "%02d   %02d", hour, minute);

  // 2. 分钟表针旋转 [0, 60) -> [0, 3600)
  int16_t angle_minutes = (int16_t)((minute * 1.0f / 60.0f) * 3600.0f);
  lv_img_set_angle(ui_min, angle_minutes);

  // 3. 时钟指针旋转 [0, 12) -> [0, 3600) 考虑分钟增量
  int16_t angle_hours = (int16_t)((hour * 1.0f / 12.0f) * 3600.0f) + (int16_t)((minute * 1.0f / 60.0f) * 300.0f);
  lv_img_set_angle(ui_hour, angle_hours);
  
}