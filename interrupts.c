#include "interrupts.h"

void ih1() {
    print_message("1");
}
void ih2() {
    print_message("2");
}
void ih3() {
    print_message("3");
}
void ih4() {
    print_message("4");
}
void ih5() {
    print_message("5");
}
void ih6() {
    print_message("6");
}
void ih7() {
    print_message("7");
}
void ih8() {
    print_message("8");
}
void ih9() {
    print_message("9");
}
void ih10() {
    print_message("10");
}
void ih11() {
    print_message("11");
}
void ih12() {
    print_message("12");
}
void ih13() {
    print_message("13");
}
void ih14() {
    print_message("14");
}
void ih15() {
    print_message("3");
}
void ih16() {
    print_message("4");
}
void ih17() {
    print_message("5");
}
void ih18() {
    print_message("6");
}
void ih19() {
    print_message("7");
}
void ih20() {
    print_message("8");
}
void ih21() {
    print_message("9");
}
void ih22() {
    print_message("10");
}
void ih23() {
    print_message("11");
}
void ih24() {
    print_message("12");
}
void ih25() {
    print_message("7");
}
void ih26() {
    print_message("8");
}
void ih27() {
    print_message("9");
}
void ih28() {
    print_message("10");
}
void ih29() {
    print_message("11");
}
void ih30() {
    print_message("12");
}
void ih31() {
    print_message("11");
}
void ih32() {
    print_message("12");
}

uint64_t form_value(void (*f)()) {
    uint64_t res = 0;
    /*flags*/
    res = res | ((uint64_t)0x8600) << 32;
    /*code segment 8 in GDT*/
    res = res | (0x0008) << 16;
    /*address of interrupt handler*/
    res = res | (f && 0xffff);
    return res;
}

void init_interrupt_table() {
    int i;
    /*fill interrupt handler*/
    void (*interrupts[32])() = {
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
	ih32
    };
    for (i = 0; i < 32; i++) {
	idt_table[i] = form_value(interrupts[i]);
    }
    /*fill idtr register*/
    new_idtr.table_size = sizeof(idt_table)-1;
    new_idtr.linear_address = (uint32_t)idt_table;
    /*load idtr register and set interrupts flag*/
    //b b74   
    __asm__ volatile (
	".intel_syntax;"
	"lidt [new_idtr];"
	"sti;"
	".att_syntax;"
    );
}


