.text
	.align 4
	.globl OperaVec
	.type	OperaVec, @function
OperaVec:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
# Aqui has de introducir el codigo
	movl $1, %edi
for:	cmpl 12(%ebp), %edi
	jge end
	movl 8(%ebp), %esi		# %esi = @Vector
	movl (%esi, %edi, 4), %esi	# %esi = @Vector + 4i
if:	cmpl -4(%ebp), %esi
	jge endif
	movl %esi, -4(%ebp)
endif:	incl %edi
	jmp for
end:
# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
