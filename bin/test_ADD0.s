.globl f
f:
addiu $29,$29,-8
sw $31,4($29)
sw $30,0($29)
move $30,$29
