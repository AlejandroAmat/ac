.text
	.align 4
	.globl procesar
	.type	procesar, @function
procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo
	movl 8(%ebp), %eax			# eax <- @mata
	movl 12(%ebp), %ebx			# ebx <- @matb
	movl 16(%ebp), %ecx			# ecx <- @matc
	movl 20(%ebp), %esi			# esi <- n
	imul %esi, %esi 			# esi <- n*n
	movl $0, %edi				# edi = k = 0
	psubb %xmm0, %xmm0			# xmm0 = 0
for:	movdqa (%eax, %edi), %xmm1		# xmm1 <- mata[k]..[k + 15]
	movdqa (%ebx, %edi), %xmm2
	psubb %xmm2, %xmm1			# xmm1 <- xmm1 - matb[k]..[k + 15]		
	pcmpgtb %xmm0, %xmm1
	movdqa %xmm1, (%ecx, %edi)				
	addl $16, %edi
	cmpl %esi, %edi				
	jge endfor
	jmp for
endfor:

# El final de la rutina ya esta programado

	emms	# Instruccion necesaria si os equivocais y usais MMX
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
