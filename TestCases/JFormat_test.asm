Loop:
addi x3,x2,5
addi x3,x3,1
bne x3,x2,Label
jal Loop

Label:
add x4,x4,x3
beq x4,x3,Label
jal Label2

Label2:
add x5,x5,x2
jal Label