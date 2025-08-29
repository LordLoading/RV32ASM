struct:
    .word 0xc
    .half 0xffff
    .word 0xa
word2:
    .word 0xd0
half:
    .word 0xf0

# test comment
# test comment 2
# test

routine:
    addi x2, x0, 0x12
    jalr x0, main(x0)

main:
    lw x1, word(x0)
    lw x3, word2(x0)
    lh x4, half(x0)

    addi x2, x1, 1
    addi x4, x3, 1

balls:
    .byte 0xab
word:
    .word 0xba115