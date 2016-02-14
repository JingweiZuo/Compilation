debut:
	inc	1
	push	0
	input
	push	0
	cont
	pushr	10.0
	gt
	jf	l1
	outchar ">10"	
	halt
l1:
	outchar "<10"
	halt
	end
