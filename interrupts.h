#include <stdint.h>
#include <sys/io.h>

#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H


#define PIC_MASTER 0x20
#define PIC_SLAVE 0xA0
#define PIC_MASTER_COMMAND PIC_MASTER
#define PIC_MASTER_DATA (PIC_MASTER+1)
#define PIC_SLAVE_COMMAND PIC_SLAVE
#define PIC_SLAVE_DATA (PIC_SLAVE+1)

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define NEW_OFFSET 0x20
#define NEW_OFFSET_2 0x28
#define IV_4_8086 0x01

/*IDT - interrupt table*/
uint64_t idt_table[48];

typedef struct __attribute__((__packed__)) {
	uint16_t table_size;
	uint32_t linear_address;
} IDTR;


IDTR new_idtr;

void ih0();
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
void ih33();
void ih34();
void ih35();
void ih36();
void ih37();
void ih38();
void ih39();
void ih40();
void ih41();
void ih42();
void ih43();
void ih44();
void ih45();
void ih46();
void ih47();

extern void ih32_stub();
extern void ih33_stub();

void (*interrupts[48])() = {
	ih0,
	ih1,
	ih2,
	ih3,
	ih4,
	ih5,
	ih6,
	ih7,
	ih8,
	ih9,
	ih10,
	ih11,
	ih12,
	ih13,
	ih14,
	ih15,
	ih16,
	ih17,
	ih18,
	ih19,
	ih20,
	ih21,
	ih22,
	ih23,
	ih24,
	ih25,
	ih26,
	ih27,
	ih28,
	ih29,
	ih30,
	ih31,
    ih32_stub,
    ih33_stub,
    ih34,
    ih35,
    ih36,
    ih37,
    ih38,
    ih39,
    ih40,
    ih41,
    ih42,
    ih43,
    ih44,
    ih45,
    ih46,
    ih47
};


void init_interrupt_table();
void pic_remap();

#endif
