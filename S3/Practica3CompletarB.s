.text
	.align 4
	.globl OperaMat
	.type	OperaMat, @function
OperaMat:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
# Aqui has de introducir el codigo
	movl $0, -4(%ebp)
	movl $0, -8(%ebp)
for1:	cmpl $3, -8(%ebp)
	jge end1
	movl $0, -12(%ebp)
for2:	cmpl $3, -12(%ebp)
	jge end2

	imul $16, -8(%ebp), %esi	
	addl 8(%ebp), %esi		# %esi = (i*3 + i)*4 + @Matriz
	movl (%esi), %esi		# %esi = Matriz[i][i]
	addl -12(%ebp), %esi
	subl %esi, -4(%ebp)
		
	incl -12(%ebp)
	jmp for2

end2:	movl 12(%ebp), %edi
	addl %edi, -8(%ebp)
	jmp for1
end1:
# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx	
	movl %ebp,%esp
	popl %ebp
	ret
