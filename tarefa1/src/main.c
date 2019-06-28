/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <misc/util.h>
#include <misc/printk.h>

/***** SETUP BUTTONS ******/
/* change this to use another GPIO port */
#define PORT0	SW0_GPIO_CONTROLLER
#define PORT1	SW1_GPIO_CONTROLLER
#define PORT2	SW2_GPIO_CONTROLLER
#define PORT3	SW3_GPIO_CONTROLLER

/* change this to use another GPIO pin */
#define PIN0     SW0_GPIO_PIN
#define PIN1     SW1_GPIO_PIN
#define PIN2     SW2_GPIO_PIN
#define PIN3     SW3_GPIO_PIN

/* change to use another GPIO pin interrupt config */
#define EDGE    GPIO_INT_EDGE
#define PULL_UP GPIO_PUD_PULL_UP
#define DEBOUCE GPIO_INT_DEBOUNCE

// SETUP LEDS
#define LED_CONTROLLER_ZERO	    LED0_GPIO_CONTROLLER
#define LED_PIN_ZERO						LED0_GPIO_PIN
#define LED_CONTROLLER_ONE		  LED1_GPIO_CONTROLLER
#define LED_PIN_ONE						  LED1_GPIO_PIN
#define LED_CONTROLLER_TWO	    LED2_GPIO_CONTROLLER
#define LED_PIN_TWO					    LED2_GPIO_PIN
#define LED_CONTROLLER_THREE	  LED3_GPIO_CONTROLLER
#define LED_PIN_THREE					  LED3_GPIO_PIN

struct state_leds{
  char led_zero  : 1;
  char led_one   : 1;
  char led_two   : 1;
  char led_three : 1;
};

struct device *devZero;
struct device *devOne;
struct device *devTwo;
struct device *devThree;

struct state_leds state;


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
/* Sleep time */
#define SLEEP_TIME	500



//int state. = 1;  // Led Inicialmente apagado
//int led_one = 1;   // Led Inicialmente apagado
//int led_two = 1;   // Led Inicialmente apagado
//int led_three = 1; // Led Inicialmente apagado


void button_zero_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins){
	printk("Button pressed at %d\n", k_cycle_get_32());
	blinky_led(0);
}

void button_one_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins){
	printk("Button pressed at %d\n", k_cycle_get_32());
	blinky_led(1);
}

void button_two_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins){
	printk("Button pressed at %d\n", k_cycle_get_32());
	blinky_led(2);
}

void button_three_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins){
	printk("Button pressed at %d\n", k_cycle_get_32());
	blinky_led(3);
}

static struct gpio_callback gpio_cb_zero;
static struct gpio_callback gpio_cb_one;
static struct gpio_callback gpio_cb_two;
static struct gpio_callback gpio_cb_three;

void main(void)
{

	struct device *gpiob_zero;
	struct device *gpiob_one;
	struct device *gpiob_two;
	struct device *gpiob_three;

	devZero = device_get_binding(LED_CONTROLLER_ZERO);
	gpio_pin_configure(devZero,   LED_PIN_ZERO,   GPIO_DIR_OUT);
	gpio_pin_write(devZero, LED_PIN_ZERO, state.led_zero = 1);

  devOne = device_get_binding(LED_CONTROLLER_ONE);
	gpio_pin_configure(devOne,   LED_PIN_ONE,   GPIO_DIR_OUT);
	gpio_pin_write(devOne, LED_PIN_ONE, state.led_one = 1);

	devTwo = device_get_binding(LED_CONTROLLER_TWO);
	gpio_pin_configure(devTwo,   LED_PIN_TWO,   GPIO_DIR_OUT);
	gpio_pin_write(devTwo, LED_PIN_TWO, state.led_two = 1);

	devThree = device_get_binding(LED_CONTROLLER_THREE);
	gpio_pin_configure(devThree,   LED_PIN_THREE,   GPIO_DIR_OUT);
	gpio_pin_write(devThree, LED_PIN_THREE, state.led_three = 1);

	gpiob_zero = device_get_binding(PORT0);
	gpiob_one = device_get_binding(PORT1);
	gpiob_two = device_get_binding(PORT2);
	gpiob_three = device_get_binding(PORT3);

	/* GPIO_DIR_IN = GPIO PIN TO BE INPUT
		 GPIO_INT    = GPIO TRIGGER interrupt
		 PULL_UP 		 = BUTÃO COMO PULL_UP
		 EDGE        = DO EDGE TRIGGER | 256
 	*/
	gpio_pin_configure(gpiob_zero, PIN0,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | DEBOUCE);

	gpio_init_callback(&gpio_cb_zero, button_zero_pressed, BIT(PIN0));

	gpio_add_callback(gpiob_zero, &gpio_cb_zero);
	gpio_pin_enable_callback(gpiob_zero, PIN0);

	gpio_pin_configure(gpiob_one, PIN1,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | DEBOUCE);

	gpio_init_callback(&gpio_cb_one, button_one_pressed, BIT(PIN1));

	gpio_add_callback(gpiob_one, &gpio_cb_one);
	gpio_pin_enable_callback(gpiob_one, PIN1);

	gpio_pin_configure(gpiob_two, PIN2,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | DEBOUCE);

	gpio_init_callback(&gpio_cb_two, button_two_pressed, BIT(PIN2));

	gpio_add_callback(gpiob_two, &gpio_cb_two);
	gpio_pin_enable_callback(gpiob_two, PIN2);

	gpio_pin_configure(gpiob_three, PIN3,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | DEBOUCE);

	gpio_init_callback(&gpio_cb_three, button_three_pressed, BIT(PIN3));

	gpio_add_callback(gpiob_three, &gpio_cb_three);
	gpio_pin_enable_callback(gpiob_three, PIN3);

	while (1) {
		u32_t val = 0U;

		gpio_pin_read(gpiob_zero, PIN0, &val);
		gpio_pin_read(gpiob_one, PIN1, &val);
		gpio_pin_read(gpiob_two, PIN2, &val);
		gpio_pin_read(gpiob_three, PIN3, &val);

		k_sleep(SLEEP_TIME);
	}
}
