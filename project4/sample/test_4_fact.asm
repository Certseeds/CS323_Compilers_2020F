.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text

write:
    li $v0, 1
    syscall
    li $v0, 4
    la $a0, _ret
    syscall
    move $v0, $0
    jr $ra
read:
    li $v0, 4
    la $a0, _prompt
    syscall
    li $v0, 5
    syscall
    jr $ra

fact:
    ## variable v1 is $a0
    li $t4, 1
    beq $a0, $t4, label1 ## IF v1 == #1 GOTO label1
    j label2 ## GOTO label2
label1: ## LABEL label1 :
    move $v0, $a0
    jr $ra ## RETURN v1
label2: ## LABEL label2 :
    addi $sp, $sp, -8
    sw $a0, ($sp)
    sw $ra, 4($sp)
    sub $a0, $a0, 1 ## t1 := v1 - #1
    jal fact
    lw $a0, ($sp)
    lw $ra, 4($sp)
    addi $sp, $sp, 8
    mul $v0, $v0, $a0
    jr $ra

main:
    addi $sp, $sp, -8
    sw $a0,  0($sp)
    sw $ra, 4($sp)
    jal read
    lw $a0,  0($sp)
    lw $ra,  4($sp)
    addi $sp, $sp, 8

    move $t1, $v0
    li $t3, 1
    bgt $t1, $t3, label3
    j label4
label3:
    addi $sp, $sp, -8
    sw $a0,  0($sp)
    sw $ra, 4($sp)
    move $a0, $t1
    jal fact
    lw $a0,  0($sp)
    lw $ra,  4($sp)
    addi $sp, $sp, 8
    move $t2, $v0
    j label5
label4:
    li $t2, 1
label5:
    addi $sp, $sp, -8
    sw $a0,  0($sp)
    sw $ra, 4($sp)
    move $a0, $t2
    jal write
    lw $a0,  0($sp)
    lw $ra,  4($sp)
    addi $sp, $sp, 8
    jr $ra


