#include <stdio.h>

#include "s3c_uart.h"
#include "s3c_gpio.h"
#include "s3c6410.h"
#include "button.h"
#include "lcd.h"
#include "interrupt.h"

/*
typedef struct {
    int x;
    int y;
    int life;
} player;

typedef struct {
    int stage;
    int time;
    struct player pl;
} world;
*/

static void mango_hw_init(void);
static void mango_sw_game(int stage, int x, int y);

int main(void) {
  /* Hardware Setting */
  mango_hw_init(); 

  /* Game Setting 
  struct world w;
  w.pl.x = 0;
  w.pl.y = 0;
  w.pl.life = 5;
  //w->pl.time = 300; //300 seconds
  w.stage = 0;  
  */
  int stage;
  int x = 0, y = 0;

  /* Game Play*/
  int c;

  while (1) {
    printf("\nSelect Stage\n");
    printf("1> Stage 1\n");
    printf("2> Stage 2\n");
    printf("3> Stage 3\n");
    printf("4> Stage 4\n");
    printf("x> Exit\n");
    c = getchar();
    printf(" is selected\n");

    switch (c) {
    case '1':
	stage = 0;
        break;
    case '2':
	stage = 1;
        break;
    case '3':
	stage = 2;
        break;
    case '4':
	stage = 3;
	break;
    case 'x':
//	interrupt_reset();
        goto finished;
    default:
        printf("No item\n");
        break;
    }

    draw_image(stage, x, y);
    mango_sw_game(stage, x, y);

finished:
	break;
    }

  return 0;
}

static void mango_hw_init(void)
{
  /* UART */
  mango_uart_init(1, 115200);

  /* LED */
  mango_led_init();

  /* Button */
  mango_btn_init();

  /* Interrupt */
  disable_interrupts();
  //mango_timer_init();
  mango_touch_init();

  /* LCD */
  lcd_bl_on(MAX_BL_LEV-1);
  lcd_pwr_on();
  init_lcd_reg();
  set_lcd_pos(0, 0, S3CFB_HRES, S3CFB_VRES);

}

static void mango_sw_game(int stage, int x, int y)
{
    int len;
    char buf;

    enable_interrupts();
    printf("enabled_interrupts\n");

    /* Turn off all leds at first */
    mango_led_control(LED_CONTROL_OFF, 1);
    mango_led_control(LED_CONTROL_OFF, 2);

    printf("To exit test, press any key (in keyboard)\n");

    while (1) {
 	

        len = mango_uart_read(&buf, 1, 1);
        if (len > 0)
            break;
     
	MANGO_BTN_STATE up = mango_btn_scan(MANGO_BTN_KEYCODE_UP);
	MANGO_BTN_STATE down = mango_btn_scan(MANGO_BTN_KEYCODE_DOWN);
	MANGO_BTN_STATE left = mango_btn_scan(MANGO_BTN_KEYCODE_LEFT);
	MANGO_BTN_STATE right = mango_btn_scan(MANGO_BTN_KEYCODE_RIGHT);


        if (up == MANGO_BTN_STATE_DOWN) {
            printf("Up key pressed\n");
	    //mango_led_control(LED_CONTROL_OFF, 1);	
	    y += 10;
	    draw_image(stage, x, y);
        }
       
        if (down == MANGO_BTN_STATE_DOWN) {
            printf("DOWN key pressed\n");
            //mango_led_control(LED_CONTROL_OFF, 1);	
	    y -= 10;
	    draw_image(stage, x, y);
        }

        if (left == MANGO_BTN_STATE_DOWN) {
            printf("LEFT key pressed\n");
	    //mango_led_control(LED_CONTROL_OFF, 1);	
	    x -= 10;
	    draw_image(stage, x, y);
	}

        if (right == MANGO_BTN_STATE_DOWN) {
            printf("RIGHT key pressed\n");
	    //mango_led_control(LED_CONTROL_OFF, 1);	
	    x += 10;
	    draw_image(stage, x, y);
        }

        /*
        if (up == MANGO_BTN_STATE_UP) {
            printf("Up key released\n");
            mango_led_control(LED_CONTROL_ON, 1);
	
	}
	
        if (down == MANGO_BTN_STATE_UP) {
            printf("DOWN key released\n");
            mango_led_control(LED_CONTROL_ON, 1);
        }

        if (left == MANGO_BTN_STATE_UP) {
            printf("LEFT key released\n");
	    mango_led_control(LED_CONTROL_ON, 2);
	}

        if (right == MANGO_BTN_STATE_UP) {
            mango_led_control(LED_CONTROL_ON, 2);
            printf("RIGHT key released\n");
        }
	*/

    }
}

