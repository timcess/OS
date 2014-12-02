#include <stdint.h>

/*0x00 - first part of address (first byte)
**0x00 - second part of address (fourth byte)
**0x0000 - third part of address (5-6 byte)
**0xffff - size of segment
*/
uint64_t gdt_table[3] = {
0x0000000000000000,
0x00DF9F000000FFFF,
0x00FFFF000000FFFF,
//0x00DF97000000FFFF
};
typedef struct __attribute__((__packed__)) {
    uint16_t table_size;
    uint32_t linear_address;
} GDTR;
GDTR new_gdtr = {23, (uint32_t)gdt_table};

void enter_protected()
{
    /*Switch to protected mode*/
    asm(".code16gcc");
    __asm__ (

    ".intel_syntax;"
    "in %al, 0x92;"
    "or %al, 2;"
    "out 0x92, %al;"
    "cli;"
    "lgdt [new_gdtr];"
    "mov %eax, %cr0;"
    "or %al, 1;"
    "mov %cr0, %eax;"
    "jmp 0x8:next;"
    "next:"
    ".att_syntax;"
    );
}
