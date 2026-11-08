#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int led1 = 0;
const int led2 = 1;
const int led3 = 2;
const int led4 = 3;

const int button1 = 4;
const int button2 = 5;
volatile int counter = 0;

void button_isr(uint gpio, uint32_t events) { // uint gpio = vilken knapp som tryckts ned, uint32_t events = vilken typ av avbrott
    if (gpio == button1) {
        counter++;
    } else if (gpio == button2) {
        counter--;
    }
    if  (counter > 15){
        counter = 15;
    } else if (counter < 0){
        counter = 0;
    }
};

int main() {
    stdio_init_all();

    gpio_init(led1);
    gpio_set_dir(led1, GPIO_OUT);
    gpio_init(led2);
    gpio_set_dir(led2, GPIO_OUT);
    gpio_init(led3);
    gpio_set_dir(led3, GPIO_OUT);
    gpio_init(led4);
    gpio_set_dir(led4, GPIO_OUT);

    gpio_init(button1);
    gpio_set_dir(button1, GPIO_IN);
    gpio_pull_up(button1); //När knappen inte trycks ned är den 1

    gpio_init(button2);
    gpio_set_dir(button2, GPIO_IN);
    gpio_pull_up(button2); //När knappen inte trycks ned är den 1

    gpio_set_irq_enabled_with_callback( // funktion som aktiverar avbrott
        button1, // vilken knapp
        GPIO_IRQ_EDGE_FALL,
        true, // aktivera avbrott
        &button_isr // pekar på funktionen button_isr
    );

    gpio_set_irq_enabled(
        button2,
        GPIO_IRQ_EDGE_FALL,
        true
    );

    while (true) {
        // Display the counter value on the LEDs
        gpio_put(led1, counter & 0x01); // & betyder AND med bitar
        gpio_put(led2, (counter >> 1) & 0x01); // >> betyder shift right
        gpio_put(led3, (counter >> 2) & 0x01);
        gpio_put(led4, (counter >> 3) & 0x01);
    } 
};
