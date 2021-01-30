.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
_n: .word 0
_sum: .word 0
_t0: .word 0
_t1: .word 0
_t2: .word 0
_t3: .word 0
_t4: .word 0
_t5: .word 0
_t6: .word 0
_t7: .word 0
_t8: .word 0
_t9: .word 0
_t10: .word 0
_t11: .word 0
_t12: .word 0
_t13: .word 0
_t14: .word 0
_t15: .word 0
_t16: .word 0
_t17: .word 0
_t18: .word 0
_t19: .word 0

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
    ## $a0 PARAM n
    ## $a1 PARAM p1
    ## $a2 PARAM p2
    ## $a3 PARAM p3

    li $t0,1
    sw $t0,_t0  ## t0 := #1

    move $t0,$a0
    lw   $t1,_t0
    beq  $t0,$t1,label1 ## IF n == t0 GOTO label1

    j    label2     ## GOTO label2

label1:
    li   $t0,10000
    sw   $t0,_t1  ## t0 := #10000

    move $t0,$a1
    lw   $t1,_t1
    mul  $t2,$t0,$t1
    sw   $t2,_t2 ## t2 := p1 * t1

    lw   $t0,_t2
    move $t1,$a3
    add  $t2,$t0,$t1
    sw   $t2,_t3 ## t3 := t2 + p3

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra,  4($sp) ### store $ra
    lw $a0,_t3  ## WRITE t3
    jal write ### invoke write
    lw $a0,  0($sp) ## store $a0
    lw $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8
    j label3 ## GOTO label3

label2:
    li   $t0,1
    sw   $t0,_t4  ## t4 := #1

    move $t0,$a0
    lw   $t1,_t4
    sub  $t2,$t0,$t1
    sw   $t2,_t5 ## t5 := n - t4


    addi $sp, $sp, -108 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $a1,  4($sp) ## store $a1
    sw $a2,  8($sp) ## store $a2
    sw $a3, 12($sp) ## store $a3
    lw $t0,_t0
    sw $t0, 16($sp)
    lw $t0,_t1
    sw $t0, 20($sp)
    lw $t0,_t2
    sw $t0, 24($sp)
    lw $t0,_t3
    sw $t0, 28($sp)
    lw $t0,_t4
    sw $t0, 32($sp)
    lw $t0,_t5
    sw $t0, 36($sp)
    lw $t0,_t6
    sw $t0, 40($sp)
    lw $t0,_t7
    sw $t0, 44($sp)
    lw $t0,_t8
    sw $t0, 48($sp)
    lw $t0,_t9
    sw $t0, 52($sp)
    lw $t0,_t10
    sw $t0, 56($sp)
    lw $t0,_t11
    sw $t0, 60($sp)
    lw $t0,_t12
    sw $t0, 64($sp)
    lw $t0,_t13
    sw $t0, 68($sp)
    lw $t0,_t14
    sw $t0, 72($sp)
    lw $t0,_t15
    sw $t0, 76($sp)
    lw $t0,_t16
    sw $t0, 80($sp)
    lw $t0,_t17
    sw $t0, 84($sp)
    lw $t0,_t18
    sw $t0, 88($sp)
    lw $t0,_t19
    sw $t0, 92($sp)
    lw $t0,_n
    sw $t0, 96($sp)
    lw $t0,_sum
    sw $t0, 100($sp)
    sw $ra, 104($sp) ### store $ra
    lw $a3,8($sp)
    lw $a2,12($sp)
    lw $a1,4($sp)
    lw $a0,_t5
    jal hanoi ### invoke write
    lw $a0,  0($sp) ## store $a0
    lw $a1,  4($sp) ## store $a1
    lw $a2,  8($sp) ## store $a2
    lw $a3, 12($sp) ## store $a3
    lw $t0, 16($sp)
    sw $t0,_t0
    lw $t0, 20($sp)
    sw $t0,_t1
    lw $t0, 24($sp)
    sw $t0,_t2
    lw $t0, 28($sp)
    sw $t0,_t3
    lw $t0, 32($sp)
    sw $t0,_t4
    lw $t0, 36($sp)
    sw $t0,_t5
    lw $t0, 40($sp)
    sw $t0,_t6
    lw $t0, 44($sp)
    sw $t0,_t7
    lw $t0, 48($sp)
    sw $t0,_t8
    lw $t0, 52($sp)
    sw $t0,_t9
    lw $t0, 56($sp)
    sw $t0,_t10
    lw $t0, 60($sp)
    sw $t0,_t11
    lw $t0, 64($sp)
    sw $t0,_t12
    lw $t0, 68($sp)
    sw $t0,_t13
    lw $t0, 72($sp)
    sw $t0,_t14
    lw $t0, 76($sp)
    sw $t0,_t15
    lw $t0, 80($sp)
    sw $t0,_t16
    lw $t0, 84($sp)
    sw $t0,_t17
    lw $t0, 88($sp)
    sw $t0,_t18
    lw $t0, 92($sp)
    sw $t0,_t19
    lw $t0, 96($sp)
    sw $t0,_n
    lw $t0, 100($sp)
    sw $t0,_sum
    lw $ra, 104($sp) ## read $ra
    addi $sp, $sp, 108
    sw $v0,_t6 ## t6 = hanoi(n-1,p1,p3,p2);


    li   $t0,10000
    sw   $t0,_t7  ## t7 := #10000

    move $t0,$a1
    lw   $t1,_t7
    mul  $t2,$t0,$t1
    sw   $t2,_t8 ## t8 := p1 * t7

    lw   $t0,_t8
    move $t1,$a3
    add  $t2,$t0,$t1
    sw   $t2,_t9 ## t9 := t8 + p3

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra,  4($sp) ### store $ra
    lw $a0,_t9
    jal write ### invoke write
    lw $ra,  4($sp) ## read $ra
    lw $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8 ## WRITE t9

    li   $t0,1
    sw   $t0,_t10  ##  t10 := #1

    move $t0,$a0
    lw   $t1,_t10
    sub  $t2,$t0,$t1
    sw   $t2,_t11 ## t11 := n - t10

  addi $sp, $sp, -108 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $a1,  4($sp) ## store $a1
    sw $a2,  8($sp) ## store $a2
    sw $a3, 12($sp) ## store $a3
    lw $t0,_t0
    sw $t0, 16($sp)
    lw $t0,_t1
    sw $t0, 20($sp)
    lw $t0,_t2
    sw $t0, 24($sp)
    lw $t0,_t3
    sw $t0, 28($sp)
    lw $t0,_t4
    sw $t0, 32($sp)
    lw $t0,_t5
    sw $t0, 36($sp)
    lw $t0,_t6
    sw $t0, 40($sp)
    lw $t0,_t7
    sw $t0, 44($sp)
    lw $t0,_t8
    sw $t0, 48($sp)
    lw $t0,_t9
    sw $t0, 52($sp)
    lw $t0,_t10
    sw $t0, 56($sp)
    lw $t0,_t11
    sw $t0, 60($sp)
    lw $t0,_t12
    sw $t0, 64($sp)
    lw $t0,_t13
    sw $t0, 68($sp)
    lw $t0,_t14
    sw $t0, 72($sp)
    lw $t0,_t15
    sw $t0, 76($sp)
    lw $t0,_t16
    sw $t0, 80($sp)
    lw $t0,_t17
    sw $t0, 84($sp)
    lw $t0,_t18
    sw $t0, 88($sp)
    lw $t0,_t19
    sw $t0, 92($sp)
    lw $t0,_n
    sw $t0, 96($sp)
    lw $t0,_sum
    sw $t0, 100($sp)
    sw $ra, 104($sp) ### store $ra
    lw $a3,12($sp)
    lw $a2,4($sp)
    lw $a1,8($sp)
  lw $a0,_t11
    jal hanoi ### invoke write
  lw $a0,  0($sp) ## store $a0
    lw $a1,  4($sp) ## store $a1
    lw $a2,  8($sp) ## store $a2
    lw $a3, 12($sp) ## store $a3
    lw $t0, 16($sp)
    sw $t0,_t0
    lw $t0, 20($sp)
    sw $t0,_t1
    lw $t0, 24($sp)
    sw $t0,_t2
    lw $t0, 28($sp)
    sw $t0,_t3
    lw $t0, 32($sp)
    sw $t0,_t4
    lw $t0, 36($sp)
    sw $t0,_t5
    lw $t0, 40($sp)
    sw $t0,_t6
    lw $t0, 44($sp)
    sw $t0,_t7
    lw $t0, 48($sp)
    sw $t0,_t8
    lw $t0, 52($sp)
    sw $t0,_t9
    lw $t0, 56($sp)
    sw $t0,_t10
    lw $t0, 60($sp)
    sw $t0,_t11
    lw $t0, 64($sp)
    sw $t0,_t12
    lw $t0, 68($sp)
    sw $t0,_t13
    lw $t0, 72($sp)
    sw $t0,_t14
    lw $t0, 76($sp)
    sw $t0,_t15
    lw $t0, 80($sp)
    sw $t0,_t16
    lw $t0, 84($sp)
    sw $t0,_t17
    lw $t0, 88($sp)
    sw $t0,_t18
    lw $t0, 92($sp)
    sw $t0,_t19
    lw $t0, 96($sp)
    sw $t0,_n
    lw $t0, 100($sp)
    sw $t0,_sum
    lw $ra, 104($sp) ## read $ra
    addi $sp, $sp, 108
  sw $v0,_t12     ## t12 = hanoi(n - 1, p2, p1, p3);

label3:
    li   $t0,0
    sw   $t0,_t13  ## t13 := #0

    lw $s7,28($sp)
    lw $s6,24($sp)
    lw $s5,20($sp)
    lw $s4,16($sp)
    lw $s3,12($sp)
    lw $s2,8($sp)
    lw $s1,4($sp)
    lw $s0,0($sp)
    addi $sp,$sp,32

    lw $v0,_t13
    jr $ra       ## RETURN t13

main:
    li $t0,3
    sw $t0,_t14  ## t14 := #3

    lw $t0,_t14
    sw $t0,_sum  ## sum := t14

    li $t0,1
    sw $t0,_t15  ## t15 := #1

    li $t0,2
    sw $t0,_t16  ## t16 := #2

    li $t0,3
    sw $t0,_t17  ## t17 := #3

    addi $sp, $sp, -60 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $a1,  4($sp) ## store $a1
    sw $a2,  8($sp) ## store $a2
    sw $a3, 12($sp) ## store $a3
    sw $t0, 16($sp) ## store $t0
    sw $t1, 20($sp) ## store $t1
    sw $t2, 24($sp) ## store $t2
    sw $t3, 28($sp) ## store $t3
    sw $t4, 32($sp) ## store $t4
    sw $t5, 36($sp) ## store $t5
    sw $t6, 40($sp) ## store $t6
    sw $t7, 44($sp) ## store $a7
    sw $t8, 48($sp) ## store $a8
    sw $t9, 52($sp) ## store $a9
    sw $ra, 56($sp) ### store $ra
    lw $a3,_t17
    lw $a2,_t16
    lw $a1,_t15
    lw $a0,_sum
    jal hanoi ### invoke hanoi
    lw $a0,  0($sp) ## store $a0
    lw $a1,  4($sp) ## store $a1
    lw $a2,  8($sp) ## store $a2
    lw $a3, 12($sp) ## store $a3
    lw $t0, 16($sp) ## store $t0
    lw $t1, 20($sp) ## store $t1
    lw $t2, 24($sp) ## store $t2
    lw $t3, 28($sp) ## store $t3
    lw $t4, 32($sp) ## store $t4
    lw $t5, 36($sp) ## store $t5
    lw $t6, 40($sp) ## store $t6
    lw $t7, 44($sp) ## store $a7
    lw $t8, 48($sp) ## store $a8
    lw $t9, 52($sp) ## store $a9
    lw $ra, 56($sp) ## read $ra
    addi $sp, $sp, 60
    move $t0,$v0
    sw $t0,_t18 ## t18 := CALL hanoi

    li $t0,0
    sw $t0,_t19  ## t17 := #3

    lw $v0,_t19
    jr $ra       ## RETURN t13