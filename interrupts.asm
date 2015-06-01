BITS 32

global ih32_stub
global ih33_stub
extern ih32
extern ih33
extern switcher

ih32_stub:
    cli
    pusha
    call ih32
    call switcher
    popa
    iret

ih33_stub:
    pusha
    cli
    call ih33
    sti
    popa
    iret
