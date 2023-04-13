
    hi:
    addiu $t0, $zero, 0x539
    add $t0, $t1, $t2
        addiu $t1, $zero, 10000000000   # Any ASCII string in immediate field
            sub $t3, $t4, $t5
    add $t0, $zero, $t0
    syscall

.data

# Declare any global variables here
label_x: .word 10, 11, 12, 14
    var_1234: .asciiz "My variable is 1234!"
MySpace: .space 40

# Remember indents don't matter!
    .text 
sub $t0 $t0 $s3  # commas are optional
srl $t1 $s6 0x1
beq $t1 $s7 0x6

lui $at, label_x
ori $t4, $at, 0x0
lw $t4, 0x0($t4)
j 0x100000

# why the funny indents?
                                addiu $v0, $zero, 0xa
syscall

