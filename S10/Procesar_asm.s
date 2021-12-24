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
	movl $0, %edi				# edi <- 0
for:	movb (%eax, %edi), %dl			
	subb (%ebx, %edi), %dl 			
if:	cmpb $0, %dl				
	jbe else
	movb $255, (%ecx, %edi)
	jmp endif
else:	movb $0, (%ecx, %edi)		
endif: 	incl %edi
	cmpl %esi, %edi			
	jge endfor
	jmp for
endfor:

# El final de la rutina ya esta programado

	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
