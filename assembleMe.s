main:
    call setup
    call strLoop

setup:
    li t2, terminal
    lw t2, 0(t2)
    li t1, msg
    ret

strLoop:
    lb t0, 0(t1)
    addi t1, t1, 1
    beq t0, x0, 8
    j 8;
    call keyboardSetup
    sb t0, 0(t2)
    call strLoop

keyboardSetup:
    li t3, keyboard
    lw t3, 0(t3)
    call keyboardLoop

keyboardLoop:
    lbu t0, 0(keyboard)
    sb t0, 0(keyboard)
    sb t2,

msg:
    .string "alerta alerta antifacista!"

terminal:
    .word 0x02000000

keyboard:
    .word 0x03000000
