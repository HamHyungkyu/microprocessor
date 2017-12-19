#ifndef __BUTTON_H
#define __BUTTON_H

#define MANGO_GPIO_BUTTON_PORT	S3C_GPIO_PORT_N

#define MANGO_GPIO_LED1_PORT S3C_GPIO_PORT_M
#define MANGO_GPIO_LED2_PORT S3C_GPIO_PORT_L

#define LED_CONTROL_ON 1
#define LED_CONTROL_OFF 0

typedef enum {
    MANGO_BTN_STATE_UP,
    MANGO_BTN_STATE_DOWN,
    MANGO_BTN_STATE_STABLE
} MANGO_BTN_STATE;

typedef enum {
    MANGO_BTN_KEYCODE_UP,
    MANGO_BTN_KEYCODE_DOWN,
    MANGO_BTN_KEYCODE_LEFT,
    MANGO_BTN_KEYCODE_RIGHT,
} MANGO_BTN_KEYCODE;

int prev_state[4];

void mango_btn_init(void);
void mango_led_init(void);

MANGO_BTN_STATE mango_btn_scan(MANGO_BTN_KEYCODE code);
void mango_led_control(int cmd, int led_num);


#endif	/* __BUTTON_H */

