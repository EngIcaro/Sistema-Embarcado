#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <misc/printk.h>
#include <shell/shell.h>
#include <stdlib.h>

#include "input.h"
#include "output.h"


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

output_t out_led0, out_led1, out_led2, out_led3;
input_t in_button0, in_button1, in_button2, in_button3;

struct state_leds state;


void blinky_led(int n){
			if(n == 0){
				if(state.led_zero){
					// Acender
          state.led_zero = 0;
          output_set(&out_led0,0);
				}
				else{
					// Apagar
          state.led_zero = 1;
          output_set(&out_led0,1);
				}
			}
		else if(n == 1){
			if(state.led_one){
				// Acender
        state.led_one = 0;
        output_set(&out_led1,0);
      }
			else{
				// Apagar
        state.led_one = 1;
        output_set(&out_led1,1);
      }
		}
		else if(n == 2){
			if(state.led_two){
				// Acender
        state.led_two = 0;
        output_set(&out_led2,0);
			}
			else{
				// Apagar
        state.led_two = 1;
        output_set(&out_led2,1);
			}
		}
		else if(n == 3){
			if(state.led_three){
				// Acender
        state.led_three = 0;
        output_set(&out_led3,0);
			}
			else{
				// Apagar
        state.led_three = 1;
        output_set(&out_led3,1);
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

static int gpio_set(const struct shell *shell, size_t argc, char **argv) {
      char led = *(*(argv+1));
      char read = (u8_t) *(*(argv+2));
      u8_t state = 0;
      shell_print(shell, "state: %d", state);
      switch(read){
      case '0':
          state = 0;
          break;
      case '1':
          state = 1;
          break;
      default:
          shell_print(shell, "Valor invalido");
          return -1;
      }
       switch (led) {
       case '0':
           output_set(&out_led0, state);
           break;
       case '1':
           output_set(&out_led1, state);
           //state.led_one = *(*(argv+2));
           break;
       case '2':
           output_set(&out_led2, state);
            //state.led_two = *(*(argv+2));
           break;
       case '3':
           output_set(&out_led3, state);
        //   state.led_three = *(*(argv+2));
           break;
       default:
           shell_print(shell, "Opcao invalida");
           return -1;
       }
        return 0;
}

// Subcommands array for command "gpio_led"
SHELL_STATIC_SUBCMD_SET_CREATE(gpio_led,
      SHELL_CMD_ARG(set, NULL, "Set led state command.", gpio_set, 3, NULL),
    SHELL_SUBCMD_SET_END
);

// Root command "app"
SHELL_CMD_REGISTER(gpio, &gpio_led, "gpio commands.", NULL);


void main(void)
{

  output_open(&out_led0,LED_CONTROLLER_ZERO);
  output_configure(&out_led0,LED_PIN_ZERO, GPIO_DIR_OUT);
  output_set(&out_led0, 1);
  state.led_zero = 1;
  output_open(&out_led1,LED_CONTROLLER_ONE);
  output_configure(&out_led1,LED_PIN_ONE, GPIO_DIR_OUT);
  output_set(&out_led1, 1);
  state.led_one = 1;
  output_open(&out_led2,LED_CONTROLLER_TWO);
  output_configure(&out_led2,LED_PIN_TWO, GPIO_DIR_OUT);
  output_set(&out_led2, 1);
  state.led_two = 1;
  output_open(&out_led3,LED_CONTROLLER_THREE);
  output_configure(&out_led3,LED_PIN_THREE, GPIO_DIR_OUT);
  output_set(&out_led3, 1);
  state.led_three = 1;
  input_open(&in_button0,PORT0);
  input_open(&in_button1,PORT1);
  input_open(&in_button2,PORT2);
  input_open(&in_button3,PORT3);
  //

	/* GPIO_DIR_IN = GPIO PIN TO BE INPUT
		 GPIO_INT    = GPIO TRIGGER interrupt
		 PULL_UP 		 = BUTÃO COMO PULL_UP
		 EDGE        = DO EDGE TRIGGER | 256
 	*/
  //
  in_button0.gpio_callback = gpio_cb_zero;
  input_configure(&in_button0, PIN0, GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | DEBOUCE, button_zero_pressed);
  //
  //
  in_button1.gpio_callback = gpio_cb_one;
  input_configure(&in_button1, PIN1, GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | DEBOUCE, button_one_pressed);
  //
  //
  in_button2.gpio_callback = gpio_cb_two;
  input_configure(&in_button2, PIN2, GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | DEBOUCE, button_two_pressed);
  //
  //
  in_button3.gpio_callback = gpio_cb_three;
  input_configure(&in_button3, PIN3, GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | DEBOUCE, button_three_pressed);

	while (1) {
		u32_t val = 0U;
    input_read(&in_button0, &val);
    input_read(&in_button1, &val);
    input_read(&in_button2, &val);
    input_read(&in_button3, &val);

		k_sleep(SLEEP_TIME);
	}
}
