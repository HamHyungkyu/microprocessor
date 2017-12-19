#include <stdio.h>

#include "s3c6410.h"
#include "io.h"
#include "interrupt.h"

//enable interrupt in CPU level
void enable_interrupts(void){
  __asm__ __volatile__ ("mrs r0, cpsr");
  __asm__ __volatile__ ("bic r0, r0, #0x80");
  __asm__ __volatile__ ("msr cpsr_c, r0");
}

//disable interrupt in CPU level
void disable_interrupts(void){
  __asm__ __volatile__ ("mrs r0, cpsr");
  __asm__ __volatile__ ("orr r0, r0, #0x80");
  __asm__ __volatile__ ("msr cpsr_c, r0");
}

/*
//Interrupt Service Routine for Timer1
void timer1InterruptServiceRoutine(void){
  unsigned int temp;

  //Disable any other interrupt
  temp = VIC0INTENABLE_REG;
  VIC0INTENCLEAR_REG = 0xffffffff;

  unsigned int timer1_isr_call_count = 0;
  timer1_isr_call_count++;
 // printf ("timer1InterruptSeviceRoutine is called %d times\n", timer1_isr_call_count);
 // printf ("before clear VIC0IRQSTATUS= %x\n", VIC0IRQSTATUS_REG);

  //Reset interrupt status
  TINT_CSTAT_REG |= BIT_TIMER1_STAT;
  VIC0IRQSTATUS_REG |= BIT_TIMER1;

 // printf ("after clear VIC0IRQSTATUS= %x\n", VIC0IRQSTATUS_REG);

  //Enable other interrupts
  VIC0INTENABLE_REG = temp;
}

void mango_timer_init(void){
//  int i;
  TCFG0_REG = (TCFG0_REG & ~(0xff)) | 0x20; //Prescaler 0: 0x21:32
  TCFG1_REG = (TCFG1_REG & ~(0xf<<4)) | (1<<4); //divider MUX1: 1/2

  //One interrupt per one second
  TCNTB1_REG = 1000000;
  //TCMPB1_REG = 0xffff - 1;

  TCON_REG |= (1<<9); //Timer1 Manual update
  TCON_REG = (TCON_REG & ~(0xf<<8)) | (1<<11) | (1<<8);
  //Timer1 Auto-reload on & Timer1 on

  //Enable interrupt for timer1
  VIC0INTENABLE_REG |= BIT_TIMER1;
  TINT_CSTAT_REG |= BIT_TIMER1_EN;

  //Set address of interrupt handler for timer1
  VIC0VECTADDR24 = (unsigned)timer1InterruptServiceRoutine;
} */

//Interrupt Service Routine for Touchscreen
void touchInterruptServiceRoutine(void){
  unsigned int temp;
  unsigned int temp2;

  //Disable any other interrupt
  if( !(VIC1RAWINTR_REG & 1<<30) )
	return;

  temp = VIC1INTENABLE_REG;
  VIC1INTENABLE_REG = 0xffffffff;

  temp2 = readl(ADCCON);
  temp2 |= 1;
  writel(temp2, ADCCON);
  writel(0xd4, ADCTSC);

  printf("Touch Detected\t");

  writel(0x1, ADCCLRINTPNDNUP);

  // Enable other interrupts 
  VIC1INTENABLE_REG = temp;
}

//Interrupt Service Routine for TouchScreen
void touchInterruptServiceRoutine2(void){
  unsigned int temp;
  unsigned int x, y;
//  unsigned int i, j;

  if( !(VIC1RAWINTR_REG & 1<<31) )
	return;

  //Disable any other interrupt
  temp = VIC1INTENABLE_REG;
  VIC1INTENABLE_REG = 0xffffffff;

  while( !( readl(ADCCON) & 1 << 15 ) );

  x = readl(ADCDAT0) & 0x3ff;
  y = readl(ADCDAT0) & 0x3ff;
  printf("x : %d, y: %d\n", x, y);

  writel(0xd3, ADCTSC);
  writel(0x1, ADCCLRINT);

  // Enable other interrupts 
  VIC1INTENABLE_REG = temp;
}


void mango_touch_init(void) {
  VIC1INTENABLE_REG |= BIT_ADCEOC;
  VIC1INTENABLE_REG |= BIT_ADC_PEN;

  writel(0xffff, ADCDLY);
  writel(0xd3, ADCTSC);
  writel(0x7fc1, ADCCON);

  VIC1VECTADDR30 = (unsigned)touchInterruptServiceRoutine;
  VIC1VECTADDR31 = (unsigned)touchInterruptServiceRoutine2;
}

/*
void interrupt_reset(void){
  VIC0INTENABLE_REG &= ~(BIT_TIMER1);
  TINT_CSTAT_REG &= ~(BIT_TIMER1_EN);
  VIC0VECTADDR24 = 0;
}

void mango_menu_main(void){
  int c;

  while(1){
    printf ("\nMain menu\n");
    printf ("1> Enable interrupt\n");
    printf ("2> Disable interrupt\n");
	printf ("3> Touch Test\n");
    printf ("x> Exit\n");
    c = getchar();
    printf ("\n%c is selected\n", c);

    switch(c){
      case '1':
        enable_interrupts();
        printf ("interrupt enabled\n");
        break;
      case '2':
        disable_interrupts();          
        printf ("interrupt disabled\n");
        break;
	  case '3' :
		touch_test();
		break;
      case 'x':
        interrupt_reset();
        goto finished;
      default:
        printf ("Invalid button\n");
    }
  }
  finished:
    return;
}
*/
