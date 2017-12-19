#ifndef __INTERRUPT_H
#define __INTERRUPT_H

// Registers for timer interrupt
#define VIC0IRQSTATUS_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x0)
#define VIC0INTSELECT_REG __REG(ELFIN_VIC0_BASE_ADDR + 0xc)
#define VIC0INTENABLE_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x10)
#define VIC0INTENCLEAR_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x14)

#define VIC0VECTADDR24 __REG(ELFIN_VIC0_BASE_ADDR + 0x160)

#define BIT_TIMER1 (1<<24)
#define TINT_CSTAT_REG __REG(0x7f006044)
#define BIT_TIMER1_STAT (1<<6)
#define BIT_TIMER1_EN (1<<1)

// Registers for touch intterupt
#define VIC1RAWINTR_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x8)
#define VIC1IRQSTATUS_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x0)
#define VIC1INTSELECT_REG __REG(ELFIN_VIC0_BASE_ADDR + 0xc)
#define VIC1INTENABLE_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x10)
#define VIC1INTENCLEAR_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x14)

#define VIC1VECTADDR30 __REG(ELFIN_VIC0_BASE_ADDR + 0x178)
#define VIC1VECTADDR31 __REG(ELFIN_VIC0_BASE_ADDR + 0x17c)

#define BIT_ADCEOC (1<<31)
#define BIT_ADC_PEN (1<<30)

void enable_interrupts(void);
void disable_interrupts(void);
//unsigned int timer1_isr_call_count = 0;

/*
void timer1InterruptServiceRoutine(void);
void mango_timer_init(void);
*/

void touchInterruptServiceRoutine(void);
void touchInterruptServiceRoutine2(void);
void mango_touch_init(void);

//void interrupt_reset(void);

#endif	/* __INTERRUPT_H */
