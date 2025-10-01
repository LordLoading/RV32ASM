main:
    call setup
    call strLoop

setup:
    li t2, 0x20000
    ret

strLoop:
    lb t0, msg(t1)
    addi t1, t1, 1
    beq t0, x0, 0xffff
    sb t2, 0(t2)
    call strLoop

msg:
    .string "alerta alerta antifacista"