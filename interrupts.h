#include <stdint.h>

#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H
/*IDT - interrupt table*/
//0x530 - address of interrupt_handler
uint64_t idt_table[32];

//0x0000860000080530
typedef struct __attribute__((__packed__)) {
	uint16_t table_size;
	uint32_t linear_address;
} IDTR;
IDTR new_idtr;

void ih1();
void ih2();
void ih3();
void ih4();
void ih5();
void ih6();
void ih7();
void ih8();
void ih9();
void ih10();
void ih11();
void ih12();
void ih13();
void ih14();
void ih15();
void ih16();
void ih17();
void ih18();
void ih19();
void ih20();
void ih21();
void ih22();
void ih23();
void ih24();
void ih25();
void ih26();
void ih27();
void ih28();
void ih29();
void ih30();
void ih31();
void ih32();

void init_interrupt_table();

#endif
