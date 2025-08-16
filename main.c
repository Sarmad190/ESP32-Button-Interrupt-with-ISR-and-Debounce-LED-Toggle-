#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN      GPIO_NUM_2
#define BUTTON_PIN   GPIO_NUM_4

volatile bool led_state = false;

// ISR with proper debouncing
void IRAM_ATTR isr_handler(void* arg) {
    static uint32_t last_interrupt_time = 0;  // Now persistent (static)
    uint32_t current_time = xTaskGetTickCountFromISR();  // ISR-safe function
    uint32_t duration = current_time - last_interrupt_time;

    if (duration > pdMS_TO_TICKS(200)) {  // 200ms debounce
        led_state = !led_state;
        gpio_set_level(LED_PIN, led_state);
        last_interrupt_time = current_time;
    }
}

void app_main() {
    
    
    gpio_config_t btn_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    gpio_config(&btn_conf);

    // LED config
    gpio_config_t led_conf = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_conf);

    // Install ISR
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, isr_handler, NULL);

    while (1) {
        vTaskDelay(portMAX_DELAY);  // Idle indefinitely (optional)
    }
}