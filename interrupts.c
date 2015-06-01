#include "interrupts.h"
#include "sysconst.h"
#include "multitasking.h"

/*TODO:
 * Вывод процессов в третье кольцо
 * Страничная организация памяти
 * Минимальная файловая система
 * */

void ih0() { print_message("0"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih1() { print_message("1"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih2() { print_message("2"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih3() { print_message("3"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih4() { print_message("4"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih5() { print_message("5"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih6() { print_message("("); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih7() { print_message("7"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih8() { print_message("8"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih9() { print_message("9"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih10() { print_message("10"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih11() { print_message("11"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih12() { print_message("12"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih13() { print_message("13"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih14() { print_message("14"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih15() { print_message("15"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih16() { print_message("16"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih17() { print_message("17"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih18() { print_message("18"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih19() { print_message("19"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih20() { print_message("20"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih21() { print_message("21"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih22() { print_message("22"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih23() { print_message("23"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih24() { print_message("24"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih25() { print_message("25"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih26() { print_message("26"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih27() { print_message("27"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih28() { print_message("28"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih29() { print_message("29"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih30() { print_message("30"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih31() { print_message("31"); __asm__ volatile ("add $0x1c, %esp; iret;"); }

void ih32() {
    int ptr = 158;
    VIDEO_MEM[ptr] = 'T';
    if (VIDEO_MEM[ptr+1] != 0) {
        VIDEO_MEM[ptr+1] = VIDEO_MEM[ptr+1]^1;
    } else {
        VIDEO_MEM[ptr+1] = 0x7;
    }
    outb(0xa0, 0x20);
    outb(0x20, 0x20);
}

void ih33() { 
    char scancode = inb(0x60);
    scancode-=2;
    stop_proc(scancode);
    outb(0x20, 0x20);
}

void ih34() { print_message("34"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih35() { print_message("35"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih36() { print_message("36"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih37() { print_message("37"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih38() { print_message("38"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih39() { print_message("39"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih40() { print_message("40"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih41() { print_message("41"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih42() { print_message("42"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih43() { print_message("43"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih44() { print_message("44"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih45() { print_message("45"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih46() { print_message("46"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih47() { print_message("47"); __asm__ volatile ("add $0x1c, %esp; iret;"); }
void ih48() { print_message("48"); __asm__ volatile ("add $0x1c, %esp; iret;"); }

uint64_t form_value(uint32_t f) {
    uint64_t res = 0;
    /*flags*/
    res = res | (((uint64_t)0xAE00) << 32);
    /*code segment 8 in GDT*/
    res = res | ((0x0008) << 16);
    /*address of interrupt handler*/
    res = res | (f & 0xffff);
    return res;
}

static inline void io_wait(void) {
    __asm__ volatile (
    "jmp 1f;"
    "1:jmp 2f;"
    "2:"
    );
}

void pic_remap() {
    uint8_t a1,a2;
    a1 = inb(PIC_MASTER_DATA);
    a2 = inb(PIC_SLAVE_DATA);

    outb(ICW1_INIT+ICW1_ICW4, PIC_MASTER_COMMAND);
    io_wait();
    outb(ICW1_INIT+ICW1_ICW4, PIC_SLAVE_COMMAND);
    io_wait();
    outb(NEW_OFFSET, PIC_MASTER_DATA);
    io_wait();
    outb(NEW_OFFSET_2, PIC_SLAVE_DATA);
    io_wait();
    outb(4, PIC_MASTER_DATA);
    io_wait();
    outb(2, PIC_SLAVE_DATA);
    io_wait();
    outb(IV_4_8086, PIC_MASTER_DATA);
    io_wait();
    outb(IV_4_8086, PIC_SLAVE_DATA);
    io_wait();
    outb(a1, PIC_MASTER_DATA);
    outb(a2, PIC_SLAVE_DATA);
}

void init_interrupt_table() {
    int i;

    /*fill IDT table*/
    for (i = 0; i < 48; i++) {
	    idt_table[i] = form_value((uint32_t)interrupts[i]);
    }

    /*remap PICs*/
    pic_remap();

    /*fill idtr register*/
    new_idtr.table_size = sizeof(idt_table)-1;
    new_idtr.linear_address = (uint32_t)idt_table;

    /*load idtr register and set interrupts flag*/
    __asm__ volatile (
	".intel_syntax;"
	"lidt [new_idtr];"
	"sti;"
	".att_syntax;"
    );
}

