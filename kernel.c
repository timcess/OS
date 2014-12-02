char *msg="Hello, protected mode!\0";
char *video_mem = 0xb8000;
int main()
{
    video_mem[0] = 'A';
    video_mem[1] = 0x15;
    video_mem[2] = 'B';
    video_mem[3] = 0x15;
    video_mem[4] = 'C';
    video_mem[5] = 0x15;
}
