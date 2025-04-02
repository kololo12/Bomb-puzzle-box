#include "matic_4x4.h"



// GPIO pin mappings for rows and columns
const int row_pins[ROWS] = {12, 14, 27, 26};  // Update to match your setup
const int col_pins[COLS] = {25, 33, 32, 23};


const char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Initialize keypad GPIOs
void keypad_init() {
    // Configure row pins as outputs (start HIGH)
    for (int i = 0; i < ROWS; i++) {
        gpio_set_direction(row_pins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(row_pins[i], 1);  // Default HIGH
    }

    // Configure column pins as inputs with pull-up resistors
    for (int i = 0; i < COLS; i++) {
        gpio_set_direction(col_pins[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(col_pins[i], GPIO_PULLUP_ONLY);  // Pull-up for LOW detection
    }
}

// Scan the keypad for a pressed key
char scan_keypad() {
    for (int row = 0; row < ROWS; row++) {
        gpio_set_level(row_pins[row], 0);  // Activate row (set LOW)

        for (int col = 0; col < COLS; col++) {
            if (gpio_get_level(col_pins[col]) == 0) {  // Key press detected (LOW)
                vTaskDelay(pdMS_TO_TICKS(50));  // Debounce

                TickType_t press_time = xTaskGetTickCount();

                // Wait for key release with timeout
                while (gpio_get_level(col_pins[col]) == 0) {
                    if ((xTaskGetTickCount() - press_time) > pdMS_TO_TICKS(LONG_PRESS_TIMEOUT_MS)) {
                        printf("Key held too long, ignoring\n");
                        gpio_set_level(row_pins[row], 1);  // Restore row HIGH
                        return '\0';  // Ignore long press
                    }
                    vTaskDelay(pdMS_TO_TICKS(10));  // Prevent CPU overload
                }

                gpio_set_level(row_pins[row], 1);  // Restore row HIGH
                return keys[row][col];  // Return key pressed
            }
        }

        gpio_set_level(row_pins[row], 1);  // Restore row HIGH
    }
    return '\0';  // No key pressed
}