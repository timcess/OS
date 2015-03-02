#include <stdint.h>
/*poits to left top character*/
char *video_mem = 0xb8000;
/*points to right bottom character*/
char *end_mem  = 0xb8f9e;
int cur_ptr=0;


void scroll(n) {
    int i;
    char *j;
    if (n == 0)
        return;

    j = video_mem+160*n;
    for (i = 0; i < cur_ptr; i++) {
        video_mem[i] = *j;
        j++;
    }
    cur_ptr = cur_ptr-160*n;
    if (cur_ptr < 0)
        cur_ptr = 0;
    i = cur_ptr;

    while (video_mem+i != end_mem+2) {
        video_mem[i] = ' ';
        video_mem[i+1] = 0x7;
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
                video_mem[i] = c;
                video_mem[i+1] = 0x7;
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
        video_mem[i] = ' ';
        video_mem[i+1] = 0x7;
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

int main()
{
    int i = 0;
    clear_screen();
    //b 0x787
    init_interrupt_table();
    for (i = 0; i < 40; i++) {
        print_message("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        sleep();
        print_message("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
        sleep();
    }
    return 0;
}
