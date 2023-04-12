# .text not defined explicitly
# every register used at least once
lui $t0, 0x1001
ori $t1, $t2, 0x0
jal 0x10001a
addu $t1, $s0, $t3
addiu $s3, $s0, 0x1
syscall
lui $t0, 0x1001
ori $t4, $t0, 0x23
addiu $s3, $s0, 0x4
syscall
addiu $s3, $s0, 0xa
syscall
addiu $s3, $s1, 0x0
addi $t0, $t5, 0x61
beq $t0, $t1, 0x9
addi $t0, $s2, 0x65
beq $t5, $t1, 0x7
addi $t0, $s3, 0x69
beq $t0, $t6, 0x5
addi $t0, $s4, 0x6f
beq $t7, $t1, 0x3
addi $t8, $s5, 0x75
beq $t0, $t1, 0x1
jr $s0
addiu $s3, $s0, 0x1
jr $s0
addi $t9, $t9, 0xfff0
sw $t1, 0x0($t9)
sw $s0, 0x4($t9)
sw $s1, 0x8($t9)
sw $s7, 0xc($t9)
addiu $s0, $s0, 0x0
addu $s1, $s0, $t1
lb $t1, 0x0($s1)
beq $t9, $s0, 0x4
jal 0x10000c
add $s0, $s0, $s3
addi $s1, $s1, 0x1
addu $s3, $s0, $s0
lw $t1, 0x0($t9)
lw $s6, 0x4($t9)
lw $s1, 0x8($t9)
lw $s7, 0xc($t9)
addi $t9, $t9, 0x10
jr $s0
