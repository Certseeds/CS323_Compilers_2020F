.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"

_t6: .word 0
_t0: .word 0
_t5: .word 0
_n: .word 0
_t1: .word 0
_t2: .word 0
_t3: .word 0
_t4: .word 0

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
    addi $sp,$sp,-32
    sw $s0,0($sp)
    sw $s1,4($sp)
    sw $s2,8($sp)
    sw $s3,12($sp)
    sw $s4,16($sp)
    sw $s5,20($sp)
    sw $s6,24($sp)
    sw $s7,28($sp)

    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    jal  read ### invoke read
    lw   $a0,  0($sp) ## store $a0
    lw   $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8
    move $t0,$v0
    sw   $t0,_n

    li   $t0,0
    sw   $t0,_t0

    lw   $t0,_n
    lw   $t1,_t0
    bgt  $t0,$t1,label4

    j label5

label4:
    li   $t0,1
    sw   $t0,_t1

    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    lw   $t0,_t1
    move $a0,  $t0
    jal  write ### invoke write
    lw   $ra,  4($sp) ## read $ra
    lw   $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8

    j label6

label5:
    li   $t0,0
    sw   $t0,_t2

    lw   $t0,_n
    lw   $t1,_t2
    blt  $t0,$t1,label1

    j label2

label1:
    li   $t0,1
    sw   $t0,_t3

    move $t0,$zero
    lw   $t1,_t3
    sub  $t2,$t0,$t1
    sw   $t2,_t4

    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    lw   $t0,_t4
    move $a0,  $t0
    jal  write ### invoke write
    lw   $ra,  4($sp) ## read $ra
    lw   $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8

    j label3

label2:
    li   $t0,0
    sw   $t0,_t5

    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    lw   $t0,_t5
    move $a0,  $t0
    jal  write ### invoke write
    lw   $ra,  4($sp) ## read $ra
    lw   $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8

label3:
label6:
    li   $t0,0
    sw   $t0,_t6

    lw $s7,28($sp)
    lw $s6,24($sp)
    lw $s5,20($sp)
    lw $s4,16($sp)
    lw $s3,12($sp)
    lw $s2,8($sp)
    lw $s1,4($sp)
    lw $s0,0($sp)
    addi $sp,$sp,32
    lw   $t0,_t6
    move $v0,$t0
    jr $ra

