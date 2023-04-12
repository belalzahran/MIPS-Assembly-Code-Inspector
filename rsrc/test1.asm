.text another
# This program attempts to have 1 example for each "type"
functionF:
    add $t0, $t1, $t2

done:   lb $s0, 0x0 ($s0)
syscall
jal functionF$
