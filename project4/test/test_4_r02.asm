.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
_n: .word 0
_t0: .word 0
_t1: .word 0
_t2: .word 0
_t3: .word 0
_t4: .word 0
_t5: .word 0
_t6: .word 0
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
    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    jal  read ### invoke read
    lw   $a0,  0($sp) ## store $a0
    lw   $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8
    move $t0,$v0
    sw   $t0,_n # READ n

    li   $t0,0
    sw   $t0,_t0 ## t0 := #0

    lw   $t0,_n
    lw   $t1,_t0
    bgt  $t0,$t1,label4 ##IF n > t0 GOTO label4
    j    label5 ## GOTO label5

label4: ## LABEL label4 :
    li   $t0,1
    sw   $t0,_t1 ## t1 := #1

    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    lw   $a0,_t1
    jal  write ### invoke write
    lw   $a0,  0($sp) ## store $a0
    lw   $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8

    j    label6 ## GOTO label6

label5: ## LABEL label5 :
    li   $t0,0
    sw   $t0,_t2 ## t2 := #0

    lw   $t0,_n
    lw   $t1,_t2
    blt  $t0,$t1,label1
    j    label2 ## GOTO label2

label1:
    li $t0,1
    sw $t0, _t3 ## t3 := #1

    move $t0,$zero
    lw $t1,_t3
    sub $t2,$t0,$t1
    sw $t2, _t4 ## t4 := #0 - t3

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra,  4($sp) ### store $ra
    lw $a0,_t4
    jal write ### invoke write
    lw $a0,  0($sp) ## store $a0
    lw $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8 ## WRITE t4

    j label3 ## GOTO label3

label2: ## LABEL label2 :
    li $t0,0
    sw $t0, _t5 ## t5 := #0

    addi $sp, $sp, -8 ### push stack to store $ra
    sw $a0,  0($sp) ## store $a0
    sw $ra,  4($sp) ### store $ra
    lw $a0,_t5
    jal write ### invoke write
    lw $a0,  0($sp) ## store $a0
    lw $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8 ## WRITE t5

label3: ## LABEL label3 :
label6: ## LABEL label6 :
    li $t0,0
    sw $t0,_t6 ## t6 := #0

    lw $v0,_t6
    jr $ra