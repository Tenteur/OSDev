#ifndef _IO_H_
#define _IO_H_

#define sti() __asm__ __volatile__ ("sti");
#define cli() __asm__ __volatile__ ("cli");

extern unsigned char inportb(int);
extern void outportb(int, int);

#endif