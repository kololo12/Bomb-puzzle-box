#include <stdio.h>
#include "hd44780.h"
#include "esp_log.h"
#include "driver/gpio.h"         
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Function to send the 4-bit data to the LCD
static void lcd_send_4bit(uint8_t data)
{
    gpio_set_level(LCD_D4, (data >> 4) & 0x01);
    gpio_set_level(LCD_D5, (data >> 5) & 0x01);
    gpio_set_level(LCD_D6, (data >> 6) & 0x01);
    gpio_set_level(LCD_D7, (data >> 7) & 0x01);

    // Toggle Enable pin
    gpio_set_level(LCD_E, 1);
    vTaskDelay(pdMS_TO_TICKS(5));  // Small delay to allow for data transmission
    gpio_set_level(LCD_E, 0);
    vTaskDelay(pdMS_TO_TICKS(5));  // Small delay to allow for data transmission
}

// Send command to the LCD
void lcd_send_command(uint8_t cmd)
{
    gpio_set_level(LCD_RS, 0);  // RS = 0 for command
    lcd_send_4bit(cmd & 0xF0);  // Send high nibble
    lcd_send_4bit(cmd << 4); 	// Send low nibble
	vTaskDelay(pdMS_TO_TICKS(10));	
}

// Send data to the LCD
void lcd_send_data(uint8_t data)
{
    gpio_set_level(LCD_RS, 1);  // RS = 1 for data
    lcd_send_4bit(data & 0xF0);  // Send high nibble
    lcd_send_4bit(data << 4);    // Send low nibble
}

// Initialize the LCD
void lcd_init(void)
{
    // Set GPIOs as output
    gpio_set_direction(LCD_RS, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_E, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D4, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D5, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D6, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D7, GPIO_MODE_OUTPUT);

    // Wait for LCD to power up
    vTaskDelay(pdMS_TO_TICKS(15));  // Wait for 15ms

    // Function Set: 4-bit mode, 2-line display, 5x8 font
    lcd_send_command(LCD_CMD_FUNCTION_SET);

    // Display ON: Cursor OFF
    lcd_send_command(LCD_CMD_DISPLAY_ON);

    // Clear screen
    lcd_clear();

    // Set entry mode: Auto increment, No shift
    lcd_send_command(LCD_CMD_ENTRY_MODE);
	
	// Wait for the LCD to power up
    vTaskDelay(pdMS_TO_TICKS(50));
}

// Clear the LCD screen
void lcd_clear(void)
{
    lcd_send_command(LCD_CMD_CLEAR);
    vTaskDelay(pdMS_TO_TICKS(2));  // Wait for 2ms
}

// Return the cursor to the home position
void lcd_home(void)
{
    lcd_send_command(LCD_CMD_HOME);
    vTaskDelay(pdMS_TO_TICKS(2));  // Wait for 2ms
}

// Send a string to the LCD
void lcd_send_string(const char *str)
{
    while (*str) {
        lcd_send_data(*str++);
		vTaskDelay(pdMS_TO_TICKS(10));
    }
	vTaskDelay(pdMS_TO_TICKS(20));
}

void lcd_napsat(const char *str){
	lcd_clear();
	lcd_home();
	lcd_send_string(str);
}
