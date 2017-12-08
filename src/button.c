#include "s3c_gpio.h"
#include "button.h"

void mango_btn_init(void)
{
    mango_gpio_set_type(MANGO_GPIO_BUTTON_PORT, 0, S3C_GPIO_TYPE_INPUT);
    mango_gpio_set_type(MANGO_GPIO_BUTTON_PORT, 1, S3C_GPIO_TYPE_INPUT);
    mango_gpio_set_type(MANGO_GPIO_BUTTON_PORT, 2, S3C_GPIO_TYPE_INPUT);
    mango_gpio_set_type(MANGO_GPIO_BUTTON_PORT, 3, S3C_GPIO_TYPE_INPUT);

    int i;
    for (i=0; i<3; i++)
	    prev_state[i] = 0;

}

void mango_led_init(void)
{
    mango_gpio_set_type(MANGO_GPIO_LED1_PORT, 5, S3C_GPIO_TYPE_OUTPUT);
    mango_gpio_set_type(MANGO_GPIO_LED2_PORT, 8, S3C_GPIO_TYPE_OUTPUT);
    mango_gpio_set_pullupdown(MANGO_GPIO_LED1_PORT, 5, S3C_GPIO_PUD_DOWN);
    mango_gpio_set_pullupdown(MANGO_GPIO_LED2_PORT, 8, S3C_GPIO_PUD_DOWN);

    mango_led_control(LED_CONTROL_OFF, 1);
    mango_led_control(LED_CONTROL_OFF, 2);
}

void mango_led_control(int cmd, int led_num)
{
    int led_port;
    int led_port_num;
    int val;
    /* map led_num to led_port number */
    if (led_num == 1) {
        led_port = MANGO_GPIO_LED1_PORT;
        led_port_num = 5;
    } else if (led_num == 2) {
        led_port = MANGO_GPIO_LED2_PORT;
        led_port_num = 8;
    }

    /* turn off the led */
    if (cmd == LED_CONTROL_OFF) {
        val = 0;
    } 
    /* turn on the led */
    else if (cmd == LED_CONTROL_ON) {
        val = 1;
    }

    mango_gpio_set_val(led_port, led_port_num, val);
}

MANGO_BTN_STATE mango_btn_scan(MANGO_BTN_KEYCODE code)
{
    int val;

    mango_gpio_get_val(MANGO_GPIO_BUTTON_PORT, code, &val);


    if (!val && prev_state[code]==0) 	/* pressed */
	{
		prev_state[code]=1;
	        return MANGO_BTN_STATE_DOWN;
	}
    
    if (!val) return MANGO_BTN_STATE_STABLE;

    if (val && prev_state[code]==1)
	{
		prev_state[code]=0;
		return MANGO_BTN_STATE_UP;
	}
 
    return MANGO_BTN_STATE_STABLE;

}



