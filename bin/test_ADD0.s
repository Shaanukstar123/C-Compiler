.globl f
f:
addiu $29,$29,-8
sw $31,4($29)
sw $30,0($29)
move $30,$29
li $8,0
li $9,0
add $2,$8,$9
nop
move $29,$30
lw $31,4($29)
lw $30,0($29)
addiu $29,$29,0
j $31
nop
