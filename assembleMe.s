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
    jal x0, 20
    call keyboardSetup
    addi t0, t0, 1
    sb t0, 0(t2)
    call strLoop

keyboardSetup:
    li t3, keyboard
    lw t3, 0(t3)
    call keyboardLoop

keyboardLoop:
    lbu t0, 0(t3)
    sb t0, 0(t3)
    sb t0, 0(t2)
    call keyboardLoop

msg:
    .string "alerta alerta antifacista!"

terminal:
    .word 0x02000000

keyboard:
    .word 0x03000000
