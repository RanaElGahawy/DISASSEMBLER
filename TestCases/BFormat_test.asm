Loop:
addi x3,x0,1
addi x4,x0,1
add x2,x3,x4
beq x3,x4,Label2
addi x2,x2,2
bne  x2,x3,Loop

Label2:
addi x5,x0,5
addi x6,x0,3
bge x5,x4,Loop
blt x6,x5,Label3
bne x6,x5,Label2

Label3:
bltu x6,x5,Loop
bgeu x5,x6,Label2
bne x5,x6,Label3



