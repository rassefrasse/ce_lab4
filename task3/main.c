#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

volatile int counter = 0;
    
void btn_isr(){
    counter = 0;
};

int main() {
    int BTN = 4;
    int LED1 = 0;
    int LED2 = 1;
    int LED3 = 2;
    int LED4 = 3;
    
    stdio_init_all();

    gpio_init(LED1);
    gpio_set_dir(LED1, GPIO_OUT);
    gpio_init(LED2);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_init(LED3);
    gpio_set_dir(LED3, GPIO_OUT);
    gpio_init(LED4);
    gpio_set_dir(LED4, GPIO_OUT);

    gpio_init(BTN);
    gpio_set_dir(BTN, GPIO_IN);
    gpio_pull_down(BTN);

    gpio_set_irq_enabled_with_callback(
        BTN,
        GPIO_IRQ_EDGE_FALL,
        true,
        &btn_isr
    );

    

    while (true) {

        counter++;

        if (counter > 15) { 
            counter = 15; // Ser till att koden 
        }


        // Display the counter value on the LEDs
        gpio_put(LED1, counter & 0x01); // & betyder AND med bitar
        gpio_put(LED2, (counter >> 1) & 0x01); // >> betyder shift right
        gpio_put(LED3, (counter >> 2) & 0x01);
        gpio_put(LED4, (counter >> 3) & 0x01);

        sleep_ms(1000); //kontaktstuds
    }
}

