.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
    li $v0, 4
    la $a0, _prompt
    syscall
    li $v0, 5
    syscall
    jr $ra
write:
    li $v0, 1
    syscall
    li $v0, 4
    la $a0, _ret
    syscall
    move $v0, $0
    jr $ra

main:
    li   $t0,110 ## t0 := #110
    move $t1,$t0 ## a := t0
    li   $t2,97 ## t1 := #97
    move $t3,$t2 ## b := t1
    li   $t4,3 ## t2 := #3
    move $t5,$t4 ## c := t2
    sub  $t6,$t1,$t3 ## t3 := a - b
    li   $t7,2 ## t4 := #2
    mul  $t8,$t5,$t7 ## t5 := c * t4
    add  $t9,$t6,$t8 ## t6 := t3 + t5
    move $t5,$t9 ## c := t6

    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    move $a0,  $t5
    jal  write ### invoke write
    lw   $ra,  4($sp) ## read $ra
    lw   $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8

    li $a0,0
    move $v0,$a0
    jr $ra
