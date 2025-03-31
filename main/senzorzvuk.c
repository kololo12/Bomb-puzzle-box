#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"         
#include "esp_intr_alloc.h"
#include "senzorzvuk.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"


volatile bool flag_senzor_zvuk = false;
 
 
// ISR Handler
static void IRAM_ATTR gpio_isr_handler(void *arg) {
    ESP_EARLY_LOGI("ISR", "Interrupt detected on GPIO");
	flag_senzor_zvuk = true;
	gpio_intr_disable(senzor_zvuk_pin);
}

void senzor_zvuk_init(void){
	gpio_set_direction(senzor_zvuku_alarm, GPIO_MODE_OUTPUT);
	gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_POSEDGE,   // Trigger on falling edge
        .mode = GPIO_MODE_INPUT,          // Set as input mode
        .pin_bit_mask = (1ULL << senzor_zvuk_pin), // Pin bitmask
        .pull_up_en = 0,                  // zakázat pull-up resistor
    };
	
	gpio_config(&io_conf);
	
    // Install ISR service
    gpio_install_isr_service(ESP_INTR_FLAG_IRAM);

    // Attach ISR handler to GPIO
    gpio_isr_handler_add(senzor_zvuk_pin, gpio_isr_handler, (void *)senzor_zvuk_pin);
}

void senzor_zvuk_alarm(){
	gpio_set_level(senzor_zvuku_alarm, 1);
}



