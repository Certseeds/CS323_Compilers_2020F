.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"

_t17: .word 0
_t16: .word 0
_t15: .word 0
_t13: .word 0
_t12: .word 0
_t11: .word 0
_t0: .word 0
_p3: .word 0
_p1: .word 0
_n: .word 0
_t5: .word 0
_t19: .word 0
_t18: .word 0
_sum: .word 0
_t1: .word 0
_t2: .word 0
_t3: .word 0
_t6: .word 0
_t4: .word 0
_t10: .word 0
_t14: .word 0
_p2: .word 0
_t7: .word 0
_t8: .word 0
_t9: .word 0

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

hanoi:
    addi $sp,$sp,-32
    sw $s0,0($sp)
    sw $s1,4($sp)
    sw $s2,8($sp)
    sw $s3,12($sp)
    sw $s4,16($sp)
    sw $s5,20($sp)
    sw $s6,24($sp)
    sw $s7,28($sp)

    li   $t0,1
    sw   $t0,_t0

    move $t0,$a0
    lw   $t1,_t0
    beq  $t0,$t1,label1

    j label2

label1:
    li   $t0,10000
    sw   $t0,_t1

    move $t0,$a1
    lw   $t1,_t1
    mul  $t2,$t0,$t1
    sw   $t2,_t2

    lw   $t0,_t2
    move $t1,$a3
    add  $t2,$t0,$t1
    sw   $t2,_t3

    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    lw   $t0,_t3
    move $a0,  $t0
    jal  write ### invoke write
    lw   $ra,  4($sp) ## read $ra
    lw   $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8

    j label3

label2:
    li   $t0,1
    sw   $t0,_t4

    move $t0,$a0
    lw   $t1,_t4
    sub  $t2,$t0,$t1
    sw   $t2,_t5

    addi $sp, $sp, -120
    sw $a0,  0($sp) ## store $a0
    sw $a1,  4($sp) ## store $a1
    sw $a2,  8($sp) ## store $a2
    sw $a3,  12($sp) ## store $a3
    lw $t0,_t17
    sw $t0, 16($sp)
    lw $t0,_t16
    sw $t0, 20($sp)
    lw $t0,_t15
    sw $t0, 24($sp)
    lw $t0,_t13
    sw $t0, 28($sp)
    lw $t0,_t12
    sw $t0, 32($sp)
    lw $t0,_t11
    sw $t0, 36($sp)
    lw $t0,_t0
    sw $t0, 40($sp)
    lw $t0,_p3
    sw $t0, 44($sp)
    lw $t0,_p1
    sw $t0, 48($sp)
    lw $t0,_n
    sw $t0, 52($sp)
    lw $t0,_t5
    sw $t0, 56($sp)
    lw $t0,_t19
    sw $t0, 60($sp)
    lw $t0,_t18
    sw $t0, 64($sp)
    lw $t0,_sum
    sw $t0, 68($sp)
    lw $t0,_t1
    sw $t0, 72($sp)
    lw $t0,_t2
    sw $t0, 76($sp)
    lw $t0,_t3
    sw $t0, 80($sp)
    lw $t0,_t6
    sw $t0, 84($sp)
    lw $t0,_t4
    sw $t0, 88($sp)
    lw $t0,_t10
    sw $t0, 92($sp)
    lw $t0,_t14
    sw $t0, 96($sp)
    lw $t0,_p2
    sw $t0, 100($sp)
    lw $t0,_t7
    sw $t0, 104($sp)
    lw $t0,_t8
    sw $t0, 108($sp)
    lw $t0,_t9
    sw $t0, 112($sp)
    sw $ra, 116($sp)
    lw $a3,8($sp)
    lw $a2,12($sp)
    lw $a1,4($sp)
    lw $a0,56($sp)
    jal hanoi
    lw $a0,  0($sp) ## store $a0
    lw $a1,  4($sp) ## store $a1
    lw $a2,  8($sp) ## store $a2
    lw $a3,  12($sp) ## store $a3
    lw $t0,16($sp)
    sw $t0,_t17
    lw $t0,20($sp)
    sw $t0,_t16
    lw $t0,24($sp)
    sw $t0,_t15
    lw $t0,28($sp)
    sw $t0,_t13
    lw $t0,32($sp)
    sw $t0,_t12
    lw $t0,36($sp)
    sw $t0,_t11
    lw $t0,40($sp)
    sw $t0,_t0
    lw $t0,44($sp)
    sw $t0,_p3
    lw $t0,48($sp)
    sw $t0,_p1
    lw $t0,52($sp)
    sw $t0,_n
    lw $t0,56($sp)
    sw $t0,_t5
    lw $t0,60($sp)
    sw $t0,_t19
    lw $t0,64($sp)
    sw $t0,_t18
    lw $t0,68($sp)
    sw $t0,_sum
    lw $t0,72($sp)
    sw $t0,_t1
    lw $t0,76($sp)
    sw $t0,_t2
    lw $t0,80($sp)
    sw $t0,_t3
    lw $t0,84($sp)
    sw $t0,_t6
    lw $t0,88($sp)
    sw $t0,_t4
    lw $t0,92($sp)
    sw $t0,_t10
    lw $t0,96($sp)
    sw $t0,_t14
    lw $t0,100($sp)
    sw $t0,_p2
    lw $t0,104($sp)
    sw $t0,_t7
    lw $t0,108($sp)
    sw $t0,_t8
    lw $t0,112($sp)
    sw $t0,_t9
    lw $ra, 116($sp)
    addi $sp, $sp, 120
    sw $v0,_t6

    li   $t0,10000
    sw   $t0,_t7

    move $t0,$a1
    lw   $t1,_t7
    mul  $t2,$t0,$t1
    sw   $t2,_t8

    lw   $t0,_t8
    move $t1,$a3
    add  $t2,$t0,$t1
    sw   $t2,_t9

    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    lw   $t0,_t9
    move $a0,  $t0
    jal  write ### invoke write
    lw   $ra,  4($sp) ## read $ra
    lw   $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8

    li   $t0,1
    sw   $t0,_t10

    move $t0,$a0
    lw   $t1,_t10
    sub  $t2,$t0,$t1
    sw   $t2,_t11

    addi $sp, $sp, -120
    sw $a0,  0($sp) ## store $a0
    sw $a1,  4($sp) ## store $a1
    sw $a2,  8($sp) ## store $a2
    sw $a3,  12($sp) ## store $a3
    lw $t0,_t17
    sw $t0, 16($sp)
    lw $t0,_t16
    sw $t0, 20($sp)
    lw $t0,_t15
    sw $t0, 24($sp)
    lw $t0,_t13
    sw $t0, 28($sp)
    lw $t0,_t12
    sw $t0, 32($sp)
    lw $t0,_t11
    sw $t0, 36($sp)
    lw $t0,_t0
    sw $t0, 40($sp)
    lw $t0,_p3
    sw $t0, 44($sp)
    lw $t0,_p1
    sw $t0, 48($sp)
    lw $t0,_n
    sw $t0, 52($sp)
    lw $t0,_t5
    sw $t0, 56($sp)
    lw $t0,_t19
    sw $t0, 60($sp)
    lw $t0,_t18
    sw $t0, 64($sp)
    lw $t0,_sum
    sw $t0, 68($sp)
    lw $t0,_t1
    sw $t0, 72($sp)
    lw $t0,_t2
    sw $t0, 76($sp)
    lw $t0,_t3
    sw $t0, 80($sp)
    lw $t0,_t6
    sw $t0, 84($sp)
    lw $t0,_t4
    sw $t0, 88($sp)
    lw $t0,_t10
    sw $t0, 92($sp)
    lw $t0,_t14
    sw $t0, 96($sp)
    lw $t0,_p2
    sw $t0, 100($sp)
    lw $t0,_t7
    sw $t0, 104($sp)
    lw $t0,_t8
    sw $t0, 108($sp)
    lw $t0,_t9
    sw $t0, 112($sp)
    sw $ra, 116($sp)
    lw $a3,12($sp)
    lw $a2,4($sp)
    lw $a1,8($sp)
    lw $a0,36($sp)
    jal hanoi
    lw $a0,  0($sp) ## store $a0
    lw $a1,  4($sp) ## store $a1
    lw $a2,  8($sp) ## store $a2
    lw $a3,  12($sp) ## store $a3
    lw $t0,16($sp)
    sw $t0,_t17
    lw $t0,20($sp)
    sw $t0,_t16
    lw $t0,24($sp)
    sw $t0,_t15
    lw $t0,28($sp)
    sw $t0,_t13
    lw $t0,32($sp)
    sw $t0,_t12
    lw $t0,36($sp)
    sw $t0,_t11
    lw $t0,40($sp)
    sw $t0,_t0
    lw $t0,44($sp)
    sw $t0,_p3
    lw $t0,48($sp)
    sw $t0,_p1
    lw $t0,52($sp)
    sw $t0,_n
    lw $t0,56($sp)
    sw $t0,_t5
    lw $t0,60($sp)
    sw $t0,_t19
    lw $t0,64($sp)
    sw $t0,_t18
    lw $t0,68($sp)
    sw $t0,_sum
    lw $t0,72($sp)
    sw $t0,_t1
    lw $t0,76($sp)
    sw $t0,_t2
    lw $t0,80($sp)
    sw $t0,_t3
    lw $t0,84($sp)
    sw $t0,_t6
    lw $t0,88($sp)
    sw $t0,_t4
    lw $t0,92($sp)
    sw $t0,_t10
    lw $t0,96($sp)
    sw $t0,_t14
    lw $t0,100($sp)
    sw $t0,_p2
    lw $t0,104($sp)
    sw $t0,_t7
    lw $t0,108($sp)
    sw $t0,_t8
    lw $t0,112($sp)
    sw $t0,_t9
    lw $ra, 116($sp)
    addi $sp, $sp, 120
    sw $v0,_t12

label3:
    li   $t0,0
    sw   $t0,_t13

    lw $s7,28($sp)
    lw $s6,24($sp)
    lw $s5,20($sp)
    lw $s4,16($sp)
    lw $s3,12($sp)
    lw $s2,8($sp)
    lw $s1,4($sp)
    lw $s0,0($sp)
    addi $sp,$sp,32
    lw   $t0,_t13
    move $v0,$t0
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

    li   $t0,3
    sw   $t0,_t14

    lw   $t0,_t14
    sw   $t0,_sum

    li   $t0,1
    sw   $t0,_t15

    li   $t0,2
    sw   $t0,_t16

    li   $t0,3
    sw   $t0,_t17

    addi $sp, $sp, -120
    sw $a0,  0($sp) ## store $a0
    sw $a1,  4($sp) ## store $a1
    sw $a2,  8($sp) ## store $a2
    sw $a3,  12($sp) ## store $a3
    lw $t0,_t17
    sw $t0, 16($sp)
    lw $t0,_t16
    sw $t0, 20($sp)
    lw $t0,_t15
    sw $t0, 24($sp)
    lw $t0,_t13
    sw $t0, 28($sp)
    lw $t0,_t12
    sw $t0, 32($sp)
    lw $t0,_t11
    sw $t0, 36($sp)
    lw $t0,_t0
    sw $t0, 40($sp)
    lw $t0,_p3
    sw $t0, 44($sp)
    lw $t0,_p1
    sw $t0, 48($sp)
    lw $t0,_n
    sw $t0, 52($sp)
    lw $t0,_t5
    sw $t0, 56($sp)
    lw $t0,_t19
    sw $t0, 60($sp)
    lw $t0,_t18
    sw $t0, 64($sp)
    lw $t0,_sum
    sw $t0, 68($sp)
    lw $t0,_t1
    sw $t0, 72($sp)
    lw $t0,_t2
    sw $t0, 76($sp)
    lw $t0,_t3
    sw $t0, 80($sp)
    lw $t0,_t6
    sw $t0, 84($sp)
    lw $t0,_t4
    sw $t0, 88($sp)
    lw $t0,_t10
    sw $t0, 92($sp)
    lw $t0,_t14
    sw $t0, 96($sp)
    lw $t0,_p2
    sw $t0, 100($sp)
    lw $t0,_t7
    sw $t0, 104($sp)
    lw $t0,_t8
    sw $t0, 108($sp)
    lw $t0,_t9
    sw $t0, 112($sp)
    sw $ra, 116($sp)
    lw $a3,16($sp)
    lw $a2,20($sp)
    lw $a1,24($sp)
    lw $a0,68($sp)
    jal hanoi
    lw $a0,  0($sp) ## store $a0
    lw $a1,  4($sp) ## store $a1
    lw $a2,  8($sp) ## store $a2
    lw $a3,  12($sp) ## store $a3
    lw $t0,16($sp)
    sw $t0,_t17
    lw $t0,20($sp)
    sw $t0,_t16
    lw $t0,24($sp)
    sw $t0,_t15
    lw $t0,28($sp)
    sw $t0,_t13
    lw $t0,32($sp)
    sw $t0,_t12
    lw $t0,36($sp)
    sw $t0,_t11
    lw $t0,40($sp)
    sw $t0,_t0
    lw $t0,44($sp)
    sw $t0,_p3
    lw $t0,48($sp)
    sw $t0,_p1
    lw $t0,52($sp)
    sw $t0,_n
    lw $t0,56($sp)
    sw $t0,_t5
    lw $t0,60($sp)
    sw $t0,_t19
    lw $t0,64($sp)
    sw $t0,_t18
    lw $t0,68($sp)
    sw $t0,_sum
    lw $t0,72($sp)
    sw $t0,_t1
    lw $t0,76($sp)
    sw $t0,_t2
    lw $t0,80($sp)
    sw $t0,_t3
    lw $t0,84($sp)
    sw $t0,_t6
    lw $t0,88($sp)
    sw $t0,_t4
    lw $t0,92($sp)
    sw $t0,_t10
    lw $t0,96($sp)
    sw $t0,_t14
    lw $t0,100($sp)
    sw $t0,_p2
    lw $t0,104($sp)
    sw $t0,_t7
    lw $t0,108($sp)
    sw $t0,_t8
    lw $t0,112($sp)
    sw $t0,_t9
    lw $ra, 116($sp)
    addi $sp, $sp, 120
    sw $v0,_t18

    li   $t0,0
    sw   $t0,_t19

    lw $s7,28($sp)
    lw $s6,24($sp)
    lw $s5,20($sp)
    lw $s4,16($sp)
    lw $s3,12($sp)
    lw $s2,8($sp)
    lw $s1,4($sp)
    lw $s0,0($sp)
    addi $sp,$sp,32
    lw   $t0,_t19
    move $v0,$t0
    jr $ra

