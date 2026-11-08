#include <stdio.h>
#include "pico/stdlib.h"

#define LED1 0
#define LED2 1
#define BTN1 2
#define BTN2 3
#define LED

#define GPIO_IN (*(volatile uint32_t *) 0xD0000004) //initierar macros för att använda i program. dom är av datatypen uin32_t och är volatile så att deom inte ska ändras när de kompileras
#define GPIO_OUT_SET (*(volatile uint32_t *) 0xD0000014)
#define GPIO_OUT_CLR (*(volatile uint32_t *) 0xD0000018)


int main(){

  gpio_init(LED1); //initiera led
  gpio_set_dir(LED1, GPIO_OUT);
  gpio_init(LED2);
  gpio_set_dir(LED2, GPIO_OUT);

  gpio_init(BTN1); //initiera knappar
  gpio_set_dir(BTN1, GPIO_IN);
  gpio_init(BTN2);
  gpio_set_dir(BTN2, GPIO_IN);

  while(true){
    if (GPIO_IN & (1u << 2)){
      GPIO_OUT_SET = (1u << 0); //pinsen är typ sparades i 16 bitar eller något? 001, 010, 100 osv.
      GPIO_OUT_SET = (1u << 1);
    }

    else if (GPIO_IN & (1u << 3)){
      GPIO_OUT_CLR = (1u << 0);
      GPIO_OUT_CLR = (1u << 1);
    }

  sleep_ms(100);

  }
}
