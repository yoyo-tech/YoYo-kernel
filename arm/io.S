.globl out32
out32:
    str w1, [x0]
    ret

.globl in32
in32:
    ldr w0, [x0]
    ret