#ifndef HD44780_H
#define HD44780_H

// LCD Pins Configuration
#define LCD_RS  21  // Register Select
#define LCD_E   22  // Enable
#define LCD_D4  19  // Data Bit 4
#define LCD_D5  18  // Data Bit 5
#define LCD_D6  17  // Data Bit 6
#define LCD_D7  16  // Data Bit 7

// LCD Commands
#define LCD_CMD_CLEAR       0x01  // Clear display
#define LCD_CMD_HOME        0x02  // Return home
#define LCD_CMD_ENTRY_MODE  0x06  // Entry mode set
#define LCD_CMD_DISPLAY_ON  0x0C  // Display ON, cursor OFF
#define LCD_CMD_FUNCTION_SET 0x28  // 4-bit mode, 2-line display

void lcd_init(void);
void lcd_send_command(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_clear(void);
void lcd_home(void);
void lcd_send_string(const char *str);
void lcd_napsat(const char *str);


#endif 