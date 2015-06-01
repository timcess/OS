BITS 16

org 0x7c00

xor ax, ax
mov ds, ax
mov gs, ax
mov fs, ax
mov es, ax


jmp readblock
;;;;;;;;;;;;;;;;;;;;;;;;;;;
jmp print
hello db "****Welcome****"
hello_len equ $-hello

print:
;set mode
mov ax, 3
int 0x10

;set another mode
mov ah, 0x0
mov al, 0xe
int 0x10

;print char
mov cx, hello_len
print_c:
    lea bx, [hello+hello_len]
    sub bx, cx
    mov al, [bx]
    xor bx, bx
    mov ah, 0xe
    mov bl, 0x4
    int 0x10
    loop print_c
;;;;;;;;;;;;;;;;;;;;;;;;;;;

readblock:
;reading 2blocks from disk.img to RAM
mov ax, 0x50
mov es, ax
xor bx, bx
;C
mov ch, 0
;H
xor dh, dh
mov dl, 0x80 ;2**7 - first hard disk
;S 
mov cl, 2 ;number of sector
mov al, 10;number of sectors to read
mov ah, 2 
int 0x13

;absolute jmp to physical address of kernel code
jmp 0x00000500

;padding and setting magic number
times (510 - ($ - $$)) db 0x90
db 0x55, 0xAA
