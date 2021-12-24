 .text
	.align 4
	.globl BuscarElemento
	.type BuscarElemento,@function
BuscarElemento:
        pushl %ebp
	movl %esp, %ebp
	pushl %edi
	pushl %esi

	movl 16(%ebp), %eax # eax <- @mid
	movl (%eax), %ecx # ecx <- *mid
	imul $12, %ecx, %edi # edi <- 12*mid
	movl 32(%ebp), %edx # edx <- @v
	movl 4(%edx, %edi), %edi # edi <- @v+12*mid+4
if1:	cmpl 24(%ebp), %edi
	jne else1
	movl %ecx, %eax
	popl %esi
	popl %edi
	movl %ebp, %esp
	popl %ebp
	ret
	
else1:	movl 12(%ebp), %edx # edx <- @high
	movl (%edx), %esi # esi <- *high
if2:	cmpl %esi, (%eax)
	jge else2 # jump if *mid >= *high
	movl (%edx), %edx # edx <- *high
	movl %edx, (%edi) # *mid = *high
	movl 8(%ebp), %esi
	incl (%esi)
	jmp endif2


else2:	movl 8(%ebp), %edi
	movl (%edi), %edi
	movl %edi, (%eax)
	decl (%edx)

endif2:	movl $-1, %eax
	popl %esi
	popl %edi
	movl %ebp, %esp
	popl %ebp
	ret
