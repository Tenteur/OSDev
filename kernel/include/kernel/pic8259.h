#ifndef _PIC8259_H_
#define _PIC8259_H_

#include <stddef.h>

#define MASTER_PORT 0x20
#define SLAVE_PORT 0xA0

#define MASTER_PORT_1 0x21
#define SLAVE_PORT_1 0xA1

#define ICW_1 0x11

#define ICW_2_M 0x20
#define ICW_2_S 0x28

#define ICW_3_M 0x04
#define ICW_3_S 0x02

#define ICW_4 0x01

#define GET_IRR_STATUS 0x0b

#define EOI 0x20

#define IRQ_NUM 16


typedef enum irq_types {
    TIMER,
    KEYBOARD,
    TO_SLAVE_PIC,
    COM2_4,
    COM1_3,
    LPT2,
    FLOPPY,
    LPT1,
    REAL_TIME_CLOCK,
    AVAILABLE_1,
    AVAILABLE_2,
    AVAILABLE_3,
    MOUSE,
    MATH_CPU,
    FIRST_HD,
    SECOND_HD
} IRQ_t;

/*!
    \struct IRQ_s
    \brief Struttura dati per gestire gli IRQ  condivisi
*/
typedef struct IRQ_struct {
    void (*IRQ_func)();/**< Puntatore alla funzione handler di un IRQ*/
    struct IRQ_struct* next;/**< Prossimo handler per questo IRQ*/
}IRQ_s;

extern byte master_cur_mask;
extern byte slave_cur_mask;

void irq_init();
void irq_setup();
int irq_enable(IRQ_t);
int irq_disable(IRQ_t);
int irq_get_current();
void irq_add_handler(int, void (*func)());
#endif