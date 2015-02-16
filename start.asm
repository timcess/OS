[BITS 16]
extern main
extern enter_protected

call enter_protected
;Here is 32-bit code already;
[BITS 32]
mov ax, 0x10
mov ds, ax
call main
hung:
jmp hung
