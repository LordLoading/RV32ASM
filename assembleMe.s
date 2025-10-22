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
    beq t0, x0, 0xffff
    sb t0, 0(t2)
    call strLoop

msg:
    .string "alerta alerta antifacista!"

terminal:
    .word 0x02000000