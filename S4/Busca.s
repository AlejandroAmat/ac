 .text
	.align 4
	.globl Buscar
	.type Buscar,@function
Buscar:
	pushl %ebp
	movl %esp, %ebp
	addl 16, %esp
	movl $-1, -4(%ebp)
	movl $0, -16(%ebp)
	movl $0, -8(%ebp)
	movl 24(%ebp), %ecx
	decl %ecx		# ecx <- N-1
 	movl %ecx, -8(%ebp)	# high = N-1
while:	cmpl %ecx, -16(%ebp)
	jg endwhile
	pushl 8(%ebp)
	pushl 20(%ebp)
	pushl 16(%ebp)
	pushl 12(%ebp)
	leal -8(%ebp), %eax
	pushl %eax
	leal -12(%ebp), %eax
	pushl %eax
	leal -16(%ebp), %eax
	pushl %eax
	call BuscarElemento
	movl %eax, -4(%ebp)
	cmpl $0, %eax
	jl endwhile
	jmp while
	
endwhile:
	movl -4(%ebp), %eax
	subl $16, %esp
	movl %ebp, %esp
	popl %ebp
	ret
