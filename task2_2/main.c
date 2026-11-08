#include <stdio.h>
#include "pico/stdlib.h"

// Implemented in asm_funcs.S
extern int add_asm(int a, int b);

int main(void) {
    stdio_init_all();

#ifdef PICO_DEFAULT_LED_PIN
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#endif

    int counter = 0;
    while (true) {
#ifdef PICO_DEFAULT_LED_PIN
        gpio_put(PICO_DEFAULT_LED_PIN, counter & 1);
#endif
        printf("[%d] 2 + 3 = %d\n", counter++, add_asm(2, 3));
        sleep_ms(500);
    }
}
