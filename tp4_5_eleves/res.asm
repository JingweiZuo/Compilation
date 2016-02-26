	inc	1
	jp	main
fibonacci:
	libp	-2
	copy	1
	pushr	3.000000
	ls
	jf	L000
	libp	-3
	libp	-2
	copy	1
	move	1
	ret
	jp	L001
L000:
	libp	-3
	inc	1
	libp	-2
	copy	1
	pushr	1.000000
	sub
	savebp
	inc	0
	call	fibonacci
	dec	0
	rstrbp
	dec	1
	inc	1
	libp	-2
	copy	1
	pushr	2.000000
	sub
	savebp
	inc	0
	call	fibonacci
	dec	0
	rstrbp
	dec	1
	add
	move	1
	ret
L001:
main:
	push	0
	pushr	1.000000
	move	1
L002:
	push	0
	copy	1
	pushr	10.000000
	ls
	jf	L003
	inc	1
	push	0
	copy	1
	savebp
	inc	0
	call	fibonacci
	dec	0
	rstrbp
	dec	1
	output
	push	0
	push	0
	copy	1
	pushr	1.000000
	add
	move	1
	jp	L002
L003:
	halt
	end
