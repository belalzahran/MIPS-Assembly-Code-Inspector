# This is a hello world program in assembly
# This program uses no temporary or saved registers
.text
main:    # Label!
    lui $at, 0x1001
    ori $a0, $at, 0x0 # This builds the address of where Hello_str is defined 0x10010000
    addiu $v0, $zero, 0x4
    syscall

# The data section can be defined anywhere in the file
.data
    Hello_str: .asciiz "Hello World"   #This comment is counted, but the label is not!
    # Comments can appear in the .data section and indented

.text
    # More code for the program
    addiu $v0, $zero, 10   #         immediate value format varies (label, decimal value, hexadecimal)
    syscall

                # That is all the code!
