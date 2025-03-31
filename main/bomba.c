#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hd44780.h"
#include "senzorzvuk.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "globals.h"

#define lcd_tag "lcd"


TaskHandle_t lcd_task_handle = NULL;
TaskHandle_t senzorzvuk_task_handle = NULL;

void lcd_task(void *pvParameters){
	while(1){
		lcd_send_command(0x02);  // Move cursor to the first position
		lcd_send_string("Hello, World!");
		
		// Move to the second line and print another message
		lcd_send_command(0xC0);  // Move cursor to the second line
		lcd_send_string("ESP32 LCD");
		
		vTaskDelay(pdMS_TO_TICKS(5000));
		
		lcd_clear();
		lcd_send_command(0x02);  // Move cursor to the first position
		lcd_send_string("MILAN ");
		
		// Move to the second line and print another message
		lcd_send_command(0xC0);  // Move cursor to the second line
		lcd_send_string("PP MAN");
		vTaskDelay(pdMS_TO_TICKS(5000));
	}
}

void senzorzvuku_task(void *pvParameters){
	senzor_zvuk_init();
	while(1){
		if(flag_senzor_zvuk){
			senzor_zvuk_alarm();
			vTaskDelete(NULL);
		}
		vTaskDelay(pdMS_TO_TICKS(2500));
	}
}

void hw_init(void){
	lcd_init();
}

void taskcreation(void){
	xTaskCreate(lcd_task,"psani lcd",2048,NULL,1,&lcd_task_handle);
	xTaskCreate(senzorzvuku_task,"je to moc nahlas",2048,NULL,1,&senzorzvuk_task_handle);

}

void app_main(void)
{
	hw_init();
	taskcreation();

}
