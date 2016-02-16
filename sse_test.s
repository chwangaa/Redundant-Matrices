	.file	"sse_test.c"
	.text
	.type	_mm_malloc, @function
_mm_malloc:
.LFB129:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$1, -32(%rbp)
	jne	.L2
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	malloc
	jmp	.L7
.L2:
	cmpq	$2, -32(%rbp)
	je	.L4
	cmpq	$4, -32(%rbp)
	jne	.L5
.L4:
	movq	$8, -32(%rbp)
.L5:
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rcx
	leaq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	posix_memalign
	testl	%eax, %eax
	jne	.L6
	movq	-8(%rbp), %rax
	jmp	.L7
.L6:
	movl	$0, %eax
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE129:
	.size	_mm_malloc, .-_mm_malloc
	.section	.rodata
.LC2:
	.string	"%.2f \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB708:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	subq	$112, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	movl	$128, -124(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -104(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -96(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -88(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -80(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -72(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -64(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -56(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -48(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -40(%rbp)
	movl	$0, -132(%rbp)
	jmp	.L9
.L10:
	movq	-104(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	vcvtsi2ss	-132(%rbp), %xmm0, %xmm0
	vmovss	%xmm0, (%rax)
	movq	-96(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	-132(%rbp), %edx
	addl	%edx, %edx
	vcvtsi2ss	%edx, %xmm0, %xmm0
	vmovss	%xmm0, (%rax)
	movq	-88(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	(%rax,%rdx), %rcx
	movl	-132(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	vcvtsi2ss	%eax, %xmm0, %xmm0
	vmovss	%xmm0, (%rcx)
	movq	-80(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	-132(%rbp), %edx
	sall	$2, %edx
	vcvtsi2ss	%edx, %xmm0, %xmm0
	vmovss	%xmm0, (%rax)
	movq	-72(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	(%rax,%rdx), %rcx
	movl	-132(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	vcvtsi2ss	%eax, %xmm0, %xmm0
	vmovss	%xmm0, (%rcx)
	movq	-64(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	(%rax,%rdx), %rcx
	movl	-132(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	vcvtsi2ss	%eax, %xmm0, %xmm0
	vmovss	%xmm0, (%rcx)
	movq	-56(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	(%rax,%rdx), %rcx
	movl	-132(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	vcvtsi2ss	%eax, %xmm0, %xmm0
	vmovss	%xmm0, (%rcx)
	movq	-48(%rbp), %rax
	movl	-132(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	-132(%rbp), %edx
	sall	$3, %edx
	vcvtsi2ss	%edx, %xmm0, %xmm0
	vmovss	%xmm0, (%rax)
	movl	-132(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rax, %rdx
	movl	.LC0(%rip), %eax
	movl	%eax, (%rdx)
	addl	$1, -132(%rbp)
.L9:
	movl	-132(%rbp), %eax
	cmpl	-124(%rbp), %eax
	jl	.L10
	movl	$8, -120(%rbp)
	movl	-124(%rbp), %eax
	movl	%eax, -116(%rbp)
	movl	$8, -112(%rbp)
	movl	.LC1(%rip), %eax
	movl	%eax, -108(%rbp)
	movq	-104(%rbp), %rax
	movl	-116(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	-112(%rbp), %ecx
	movl	-108(%rbp), %edx
#APP
# 38 "sse_test.c" 1
	movq -104(%rbp), %r15 
	movq -96(%rbp), %r14 
	movq -88(%rbp), %r13 
	movq -80(%rbp), %r12 
	movq -72(%rbp), %r11 
	movq -64(%rbp), %r10 
	movq -56(%rbp), %r9 
	movq -48(%rbp), %r8 
	loop:vmovaps (%r15), %ymm0 
	vmovaps (%r14), %ymm1 
	vmovaps (%r13), %ymm2 
	vmovaps (%r12), %ymm3 
	vmovaps (%r11), %ymm4 
	vmovaps (%r10), %ymm5 
	vmovaps (%r9), %ymm6 
	vmovaps (%r8), %ymm7 
	vaddps %ymm0, %ymm1, %ymm0 
	vaddps %ymm2, %ymm3, %ymm2 
	vaddps %ymm4, %ymm5, %ymm4 
	vaddps %ymm6, %ymm7, %ymm6 
	vmovaps %ymm0, (%r15) 
	leaq (%r14, %rcx, 4), %r14;leaq (%r15, %rcx, 4), %r15;leaq (%r13, %rcx, 4), %r13;leaq (%r12, %rcx, 4), %r12;leaq (%r11, %rcx, 4), %r11;leaq (%r10, %rcx, 4), %r10;leaq (%r9, %rcx, 4), %r9;leaq (%r8, %rcx, 4), %r8;cmpq %r15, %rax;jg loop;
# 0 "" 2
#NO_APP
	movl	$0, -128(%rbp)
	jmp	.L11
.L12:
	movq	-104(%rbp), %rax
	movl	-128(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	vmovss	(%rax), %xmm0
	vunpcklps	%xmm0, %xmm0, %xmm0
	vcvtps2pd	%xmm0, %xmm0
	movq	stderr(%rip), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf
	addl	$1, -128(%rbp)
.L11:
	movl	-128(%rbp), %eax
	cmpl	-124(%rbp), %eax
	jl	.L12
	movl	$0, %eax
	addq	$112, %rsp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE708:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	0
	.align 4
.LC1:
	.long	1056964608
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
