#ifndef MATIC_4x4
#define MATIC_4x4

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Keypad dimensions
#define ROWS 4
#define COLS 4

// Long press timeout in milliseconds
#define LONG_PRESS_TIMEOUT_MS 1000

// Function prototypes
void keypad_init();        // Initialize the keypad GPIOs
char scan_keypad();        // Scan for a pressed key



#endif 