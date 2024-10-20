
MysteryFunction1:
	movl	$1, %eax
	jmp	.L2
.L3:
	imulq	%rdi, %rax
	movl	%edx, %esi
.L2:
	leal	-1(%rsi), %edx
	testl	%esi, %esi
	jg	.L3
	ret




MysteryFunction2:
	movl	$0, %edx
	movl	$0, %ecx
	jmp	.L5
.L6:
	addl	$1, %ecx
.L5:
	cmpl	$31, %ecx
	ja	.L8
	movl	$1, %eax
	sall	%cl, %eax
	testl	%edi, %eax
	je	.L6
	movl	$-2147483648, %eax
	shrl	%cl, %eax
	orl	%eax, %edx
	jmp	.L6
.L8:
	movl	%edx, %eax
	ret




MysteryFunction3:
	movq	(%rdi), %rcx
	movl	$1, %eax
	jmp	.L10
.L11:
	addl	$1, %eax
.L10:
	cmpl	%esi, %eax
	jge	.L14
	movslq	%eax, %rdx
	movq	(%rdi,%rdx,8), %rdx
	cmpq	%rcx, %rdx
	jle	.L11
	movq	%rdx, %rcx
	jmp	.L11
.L14:
	movq	%rcx, %rax
	ret




MysteryFunction4:
	movl	$0, %eax
	jmp	.L16
.L17:
	movl	%edi, %edx
	andl	$1, %edx
	addl	%edx, %eax
	shrq	%rdi
.L16:
	testq	%rdi, %rdi
	jne	.L17
	ret




MysteryFunction5:
	xorl	%esi, %edi
	movl	$0, %eax
	jmp	.L19
.L20:
	movl	%edi, %edx
	andl	$1, %edx
	addl	%edx, %eax
	sarl	%edi
.L19:
	testl	%edi, %edi
	jne	.L20
	ret
