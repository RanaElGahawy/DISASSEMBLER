0x0     	beq		x8, x0, 0x2
0x2     	addi	x0, x0, 0
0x4     	jal		x0, 0x2
0x6     	addi	x10, x10, 5
0x8     	beq		x8, x0, 0x2
0xa     	bne		x9, x0, 0x8
0xc     	addi	x8, x0, 5
0xe     	addi	sp, sp, 32
0x10     	srli	x11, x11, 4
0x12     	srai	x10, x10, 4
0x14     	andi	x8, x8, 5
0x16     	and		x12, x12, x11
0x18     	or		x13, x13, x14
0x1a     	xor		x14, x14, x15
0x1c     	sub		x10, x10, x11