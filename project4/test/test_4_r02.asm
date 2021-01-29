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

    addi $sp, $sp, -4 ### push stack to store $ra
    sw $ra, 0($sp) ### store $ra
    jal read ### invoke read
    lw $ra, 0($sp) ### read $ra
    move $t0,$v0 ## READ n
    addi $sp, $sp, 4

    li $t1,0 # $t1 = t0 ## t0 := #0
    bgt $t0,$t1,label4 ##IF n > t0 GOTO label4
    j label5 ## GOTO label5
label4: ## LABEL label4 :
    li $t2,1 # t1 to $t2 ## t1 := #1

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra,  4($sp) ### store $ra
    move $a0,$t2
    jal write ### invoke write
    lw $a0,  0($sp) ## store $a0
    lw $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8

    j label6 ## GOTO label6
label5: ## LABEL label5 :
    li $t3,0 # t2 to $t3 ## t2 := #0
    blt $t0,$t3,label1
    j label2 ## GOTO label2
label1:
    li $t4,1 # t3 to $t4 ## t3 := #1
    sub $t5,$zero,$t4 # t4 to $t5 ## t4 := #0 - t3

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra,  4($sp) ### store $ra
    move $a0,$t5
    jal write ### invoke write
    lw $a0,  0($sp) ## store $a0
    lw $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8

    j label3 ## GOTO label3
label2: ## LABEL label2 :
    li $t6,0 # t5 to $t6 ## t5 := #0

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra,  4($sp) ### store $ra
    move $a0,$t6
    jal write ### invoke write
    lw $a0,  0($sp) ## store $a0
    lw $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8

label3: ## LABEL label3 :
label6: ## LABEL label6 :
    li $t7,0 # t6 to $t7
    move $v0,$t7
    jr $ra