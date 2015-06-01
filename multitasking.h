#include <stdint.h>

struct procedure_context {
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    uint32_t loaded;
    uint32_t in_queue;
};

#define MAX_PROC 2
extern int _proc_count;
extern int _cur_proc;
extern const int ESP_FOR_NEW_PROC[MAX_PROC];

struct procedure_context* init_proc(uint32_t proc_begin);
void load_proc(struct procedure_context * pctx);
void switcher();
void stop_proc(char n);
void boring_proc();
