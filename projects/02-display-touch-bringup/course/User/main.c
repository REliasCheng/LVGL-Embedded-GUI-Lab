#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include "USART.h"
#include "I2C.h"

#include "st7789.h"
#include "cst816t.h"

/***********************
任务：模板工程


************************/
void USART0_on_recv(uint8_t* data, uint32_t len) {
  printf("recv[%d]:%s\n", len, data);
}

int main(void) {
  // 配置全局中断分组
  nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
  // 初始化系统嘀嗒定时器
  systick_config();
  // 初始化USART
  USART_init();
  
  // 初始化I2C
  I2C_init();
  CST816T_Init();
  
  ST7789_Init();
  ST7789_Test();

  while(1) {
    
    delay_1ms(1000);
  }
}
