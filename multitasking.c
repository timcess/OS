#include <stdint.h>
#include "multitasking.h"

void boring_proc() {
    int a = 1;
    while(1) {
        a++;
    }
}

/*Last initilized process*/
int _proc_count = 0;

/*Current running process*/
int _cur_proc = 0;
int _is_boring_proc = 0;
const int ESP_FOR_NEW_PROC[MAX_PROC] = {0x82800, 0x85000}; /*10KiB of stack for every procedure*/ 
struct procedure_context PROCS[MAX_PROC];
struct procedure_context boring_process = {0x80000, 0x80000, (uint32_t)boring_proc, 0, 1};

struct procedure_context* init_proc(uint32_t proc_begin) {
    struct procedure_context *res = &PROCS[_proc_count];
    res->esp = ESP_FOR_NEW_PROC[_proc_count];
    res->ebp = res->esp;
    res->eip = proc_begin;

    res->in_queue = 1;
    res->loaded = 0;
    _proc_count++;
    return res;
}



void load_proc(struct procedure_context * pctx) {
    /*Set esp*/
    __asm__ volatile (
            "movl %0, %%esp;"
            ::"r"(pctx->esp)
            );
    pctx->loaded = 1;
    /*Call process*/
    __asm__ volatile (
            "movl %0, %%eax;"
            "sti;"
            "call %%eax;"
            ::"p"(pctx->eip)
            );
}

void switcher() {   
    struct procedure_context *cp;
    if (_is_boring_proc) {
       cp = &boring_process;
    } else {
       cp  = &PROCS[_cur_proc];
    }
    int i;
    /*Save ebp*/
    __asm__ volatile (
            "movl %%ebp, (%0);"
            ::"p"(&cp->ebp)
            );

    /*find next proc*/
    for (i = (_cur_proc+1)%MAX_PROC; i != _cur_proc; i = (i+1)%MAX_PROC) {
        if (PROCS[i].in_queue == 1)   
            break;
    }
    

    /*if we didn't find it launch boring_proc*/
    if (i == _cur_proc && PROCS[i].in_queue == 0) {
        cp = &boring_process;
        _is_boring_proc = 1;
    } else {
        _is_boring_proc = 0;
        _cur_proc = i;
        cp = &PROCS[i];
    }

    if (!cp->loaded) {
        load_proc(cp);
    } else {
        /*Load ebp of other process*/
        __asm__ volatile (
                "movl %0, %%ebp;"
                ::"r"(cp->ebp)
                );
    }
}


void stop_proc(char n) {
    if (n < MAX_PROC)
       PROCS[n].in_queue ^= 1;
}
