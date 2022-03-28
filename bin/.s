.globl f
f:
addiu $sp,$sp,-8
sw $31,4($sp)
sw $fp,0($sp)
move $30,$sp
li $2,0
nop
move $sp,$fp
lw $31,4($sp)
lw $fp,0($sp)
addiu $sp,$sp,0
j $31
nop
