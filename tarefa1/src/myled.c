#include "myled.h"

void blinky_led(int n){
			if(n == 0){
				if(state.led_zero){
					// Acender
          state.led_zero = 0;
					gpio_pin_write(devZero, LED_PIN_ZERO, state.led_zero);
				}
				else{
					// Apagar
          state.led_zero = 1;
					gpio_pin_write(devZero, LED_PIN_ZERO, state.led_zero);
				}
			}
		else if(n == 1){
			if(state.led_one){
				// Acender
        state.led_one = 0;
				gpio_pin_write(devOne, LED_PIN_ONE, state.led_one);
			}
			else{
				// Apagar
        state.led_one = 1;
				gpio_pin_write(devOne, LED_PIN_ONE, state.led_one);
			}
		}
		else if(n == 2){
			if(state.led_two){
				// Acender
        state.led_two = 0;
				gpio_pin_write(devTwo, LED_PIN_TWO, state.led_two);
			}
			else{
				// Apagar
        state.led_two = 1;
				gpio_pin_write(devTwo, LED_PIN_TWO, state.led_two);
			}
		}
		else if(n == 3){
			if(state.led_three){
				// Acender
        state.led_three = 0;
				gpio_pin_write(devThree, LED_PIN_THREE, state.led_three);
			}
			else{
				// Apagar
        state.led_three = 1;
				gpio_pin_write(devThree, LED_PIN_THREE, state.led_three);
			}
		}

}
