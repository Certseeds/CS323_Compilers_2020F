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
    li  $t0,1     ## t0 := #1
    beq $a0,$t0,label1 ## IF n == t0 GOTO label1
    j   label2     ## GOTO label2

label1:
    li   $t1,10000    ## t1 := #10000
    mul  $t2,$a1,$t1 ## t2 := p1 * t1
    add  $t3,$t2,$a3 ## t3 := t2 + p3

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra, 4($sp) ### store $ra
    move $a0, $t3 ## WRITE t3
    jal write ### invoke write
    lw $a0,  0($sp) ## store $a0
    lw $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8
    j label3 ## GOTO label3

label2:
    li $t4,1 ## t4 := #1
    sub $t5,$a0,$t4 ## t5 := n - t4

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
    lw $a3,8($sp)
    lw $a2,12($sp)
    lw $a1,4($sp)
    lw $a0,36($sp)
    jal hanoi ### invoke write
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
    move $t6,$v0     ## t6 = hanoi(n-1,p1,p3,p2);

    li   $t7,10000   ## t7 := #10000
    mul  $t8,$a1,$t7 ## t8 := p1 * t7
    add  $t9,$t8,$a3 ## t9 := t8 + p3

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra,  4($sp) ### store $ra
    move $a0, $t9 ## WRITE t9
    jal write ### invoke write
    lw $ra,  4($sp) ## read $ra
    lw $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8

    li $s0, 1 ## t10 := #1
    sub $s1,$a0,$s0 ## t11 := n - t10

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
    lw $a3,12($sp)
    lw $a2,4($sp)
    lw $a1,8($sp)
    move $a0,$s1
    jal hanoi ### invoke write
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
    move $s2,$v0     ## t12 = hanoi(n - 1, p2, p1, p3);
label3:
    li $s3,0     ## t13 := #0

    lw $s7,28($sp)
    lw $s6,24($sp)
    lw $s5,20($sp)
    lw $s4,16($sp)
    lw $s3,12($sp)
    lw $s2,8($sp)
    lw $s1,4($sp)
    lw $s0,0($sp)
    addi $sp,$sp,32

    move $v0,$s3
    jr $ra       ## RETURN t13

main:
    li $t0,3
    move $t1,$t0
    li $t2,1
    li $t3,2
    li $t4,3


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

    lw $a3,32($sp)
    lw $a2,28($sp)
    lw $a1,24($sp)
    lw $a0,20($sp)
    jal hanoi ### invoke write

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

    move $t5,$v0
    li $t6,0
    jr $ra       ## RETURN t13