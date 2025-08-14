struct:
    .word 0xc
    .half 0xffff
    .word 0xa
    .string "test"
word2:
    .word 0xd0
half:
    .word 0xf0

# test comment
    #test comment 2
     #test

main:
    lw   x1, 0(word)
    lw   x3, 0(word2)
    lw   x4, 0(half)

    addi x2, x1, 1
    addi x4, x3, 1

balls:
    .byte 0xab
string:
    .string "fe"