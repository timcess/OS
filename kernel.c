#include <stdint.h>
#include "sysconst.h"
#include "multitasking.h"

char * const VIDEO_MEM = (char *)0xb8000;
char * const END_MEM = (char *)0xb8f9e;
int cur_ptr=0;

void scroll(n) {
    int i;
    char *j;
    if (n == 0)
        return;

    j = VIDEO_MEM+160*n;
    for (i = 0; i < cur_ptr; i++) {
        VIDEO_MEM[i] = *j;
        j++;
    }
    cur_ptr = cur_ptr-160*n;
    if (cur_ptr < 0)
        cur_ptr = 0;
    i = cur_ptr;

    while (VIDEO_MEM+i != END_MEM+2) {
        VIDEO_MEM[i] = ' ';
        VIDEO_MEM[i+1] = 0x7;
        i+=2;
    }
}

void print_message(const char *msg) {
    int i, j = 0;
    char c = msg[0];

    i = cur_ptr;
    while (c != '\0') {
        switch (c) {
            case '\r':
                i = i+160;
                break;
            case '\n':
                i = (i+160)-(i%160);
                break;
            default:
                VIDEO_MEM[i] = c;
                VIDEO_MEM[i+1] = 0x7;
                i+=2;
                break;
        }
        if (i/160+1 == 26) {
            cur_ptr = i;
            scroll(1);
            i = i-160;
        }
        j++;
        c = msg[j];
    }
    cur_ptr = i;
}


/*screen is 80x25*/
void clear_screen() {
    int i;
    for (i = 0; i < 160*25; i+=2) {
        VIDEO_MEM[i] = ' ';
        VIDEO_MEM[i+1] = 0x7;
    }
}

void sleep()
{
    int i = 0;
    int k = 2;
    for (i = 0; i < 1000000; i++) {
        k = k*k*k;
    }
}

char n2h(uint32_t value) {
    if ((value & 0xf) <= 9)
	    return (value & 0xf) + '0';
    else
        return (value & 0xf)-10+'a'; 
}

print_addr(uint32_t value) {
    char msg[12];
    msg[0] = '0';
    msg[1] = 'x';
    msg[2] = n2h(value >> 28);
    msg[3] = n2h(value >> 24);
    msg[4] = n2h(value >> 20);
    msg[5] = n2h(value >> 16);
    msg[6] = n2h(value >> 12);
    msg[7] = n2h(value >> 8);
    msg[8] = n2h(value >> 4);
    msg[9] = n2h(value);
    msg[10] = '\n';
    msg[11] = '\0';
    print_message(msg);
}

void empty_proc() {
    int a = 1;
    while (1) {
        a = a*a;
    }
}

void proc1() {
    while (1) {
        print_message("process 1\n");
    }
}

void proc2() {
    while (1) {
        print_message("process 2\n");
    }
}

int main()
{
    clear_screen();
    init_interrupt_table();
    print_addr(boring_proc);
    print_addr(switcher);

    /*launch first process*/
    struct procedure_context* first_proc = init_proc((uint32_t)proc1);
    init_proc((uint32_t)proc2);

    load_proc(first_proc);
    return 0;
}
