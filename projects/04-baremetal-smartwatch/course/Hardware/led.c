#include "led.h"
#include "gd32f4xx.h"

int flag = 0;
/**
gpio 配置
timer 配置
adc 配置
*/

#define LED_RCU   RCU_GPIOB
#define LED_PORT  GPIOB
#define LED_PIN   GPIO_PIN_2
static void led_gpio_init(){
	// 打开时钟线
	rcu_periph_clock_enable(LED_RCU);
	// 输出配置
	gpio_mode_set(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
	gpio_output_options_set(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED_PIN);
	
	led_set_state(flag);
}

void led_init(){
	led_gpio_init();
}

void led_toggle(){
	led_set_state(!flag);	
}

int led_get_state(){
	return flag;
}

void led_set_state(uint8_t state){
	flag = state;
	gpio_bit_write(LED_PORT,LED_PIN,flag);
}