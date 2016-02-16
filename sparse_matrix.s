	.file	"sparse_matrix.c"
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
.LC0:
	.string	"sparse_matrix.c"
.LC1:
	.string	"fin != ((void *)0)"
.LC2:
	.string	"%d %d"
.LC3:
	.string	"%d"
	.text
	.type	readInNewPair, @function
readInNewPair:
.LFB708:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L9
	movl	$__PRETTY_FUNCTION__.5367, %ecx
	movl	$20, %edx
	movl	$.LC0, %esi
	movl	$.LC1, %edi
	call	__assert_fail
.L9:
	leaq	-20(%rbp), %rcx
	leaq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf
	movl	-24(%rbp), %edx
	movq	-48(%rbp), %rax
	movl	%edx, (%rax)
	movl	-20(%rbp), %edx
	movq	-48(%rbp), %rax
	movl	%edx, 4(%rax)
	movl	-20(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L10
.L11:
	leaq	-16(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	$.LC3, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movl	-16(%rbp), %eax
	movl	%eax, (%rdx)
	addl	$1, -12(%rbp)
.L10:
	movl	-20(%rbp), %eax
	cmpl	%eax, -12(%rbp)
	jl	.L11
	movq	-48(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE708:
	.size	readInNewPair, .-readInNewPair
	.section	.rodata
.LC4:
	.string	"%f %d"
	.text
	.type	readInNewScaler, @function
readInNewScaler:
.LFB709:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L13
	movl	$__PRETTY_FUNCTION__.5380, %ecx
	movl	$37, %edx
	movl	$.LC0, %esi
	movl	$.LC1, %edi
	call	__assert_fail
.L13:
	leaq	-16(%rbp), %rcx
	leaq	-20(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	$.LC4, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf
	movl	-16(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L14
.L15:
	movl	-12(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readInNewPair
	addl	$1, -12(%rbp)
.L14:
	movl	-16(%rbp), %eax
	cmpl	%eax, -12(%rbp)
	jl	.L15
	movq	-48(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movl	-20(%rbp), %eax
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movl	-16(%rbp), %edx
	movq	-48(%rbp), %rax
	movl	%edx, 4(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE709:
	.size	readInNewScaler, .-readInNewScaler
	.section	.rodata
.LC5:
	.string	"r"
.LC6:
	.string	"%d %d %d"
	.text
	.globl	init_SparseMatrix
	.type	init_SparseMatrix, @function
init_SparseMatrix:
.LFB710:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	movl	$.LC5, %esi
	movq	%rax, %rdi
	call	fopen
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L17
	movl	$__PRETTY_FUNCTION__.5392, %ecx
	movl	$54, %edx
	movl	$.LC0, %esi
	movl	$.LC1, %edi
	call	__assert_fail
.L17:
	leaq	-40(%rbp), %rsi
	leaq	-32(%rbp), %rcx
	leaq	-36(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rsi, %r8
	movl	$.LC6, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf
	movl	$24, %edi
	call	malloc
	movq	%rax, -16(%rbp)
	movl	-40(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -8(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L18
.L19:
	movl	-28(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readInNewScaler
	addl	$1, -28(%rbp)
.L18:
	movl	-40(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	jl	.L19
	movl	-40(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movl	-32(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, 4(%rax)
	movl	-36(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE710:
	.size	init_SparseMatrix, .-init_SparseMatrix
	.globl	isInMatrix
	.type	isInMatrix, @function
isInMatrix:
.LFB711:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	vmovss	%xmm0, -28(%rbp)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L22
.L26:
	movl	-12(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	vmovss	(%rax), %xmm0
	vucomiss	-28(%rbp), %xmm0
	jp	.L23
	vucomiss	-28(%rbp), %xmm0
	jne	.L23
	movl	$1, %eax
	jmp	.L25
.L23:
	addl	$1, -12(%rbp)
.L22:
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	cmpl	-12(%rbp), %eax
	jg	.L26
	movl	$0, %eax
.L25:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE711:
	.size	isInMatrix, .-isInMatrix
	.globl	getNumberOfCol
	.type	getNumberOfCol, @function
getNumberOfCol:
.LFB712:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	4(%rax), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE712:
	.size	getNumberOfCol, .-getNumberOfCol
	.globl	getNumberOfRow
	.type	getNumberOfRow, @function
getNumberOfRow:
.LFB713:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE713:
	.size	getNumberOfRow, .-getNumberOfRow
	.globl	getNumberOfDistinctElement
	.type	getNumberOfDistinctElement, @function
getNumberOfDistinctElement:
.LFB714:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE714:
	.size	getNumberOfDistinctElement, .-getNumberOfDistinctElement
	.globl	getScalers
	.type	getScalers, @function
getScalers:
.LFB715:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE715:
	.size	getScalers, .-getScalers
	.section	.rodata
	.align 8
.LC8:
	.string	"the value of result is %.2f %.2f %.2f \n"
	.text
	.globl	accumulateRows
	.type	accumulateRows, @function
accumulateRows:
.LFB716:
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
	pushq	%rbx
	andq	$-32, %rsp
	subq	$928, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, %rax
	movq	%rsi, %r10
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movq	%r10, %rdi
	movq	%rsi, 48(%rsp)
	movq	%rdi, 56(%rsp)
	movq	%rdx, 40(%rsp)
	movl	%ecx, 36(%rsp)
	movl	%r8d, 32(%rsp)
	movl	%r9d, 28(%rsp)
	movl	52(%rsp), %eax
	movl	%eax, 88(%rsp)
	movq	56(%rsp), %rax
	movq	%rax, 152(%rsp)
	movl	$0, 68(%rsp)
	jmp	.L37
.L38:
	movl	68(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rax, %rdx
	movl	.LC7(%rip), %eax
	movl	%eax, (%rdx)
	addl	$1, 68(%rsp)
.L37:
	movl	68(%rsp), %eax
	cmpl	32(%rsp), %eax
	jl	.L38
	movl	$0, 72(%rsp)
	movl	88(%rsp), %eax
	cltd
	shrl	$29, %edx
	addl	%edx, %eax
	andl	$7, %eax
	subl	%edx, %eax
	movl	%eax, 92(%rsp)
	movl	92(%rsp), %eax
	movl	88(%rsp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, 96(%rsp)
	jmp	.L39
.L51:
	movl	72(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 100(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 104(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 108(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$3, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 112(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$4, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 116(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$5, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 120(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$6, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 124(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$7, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 128(%rsp)
	movl	100(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %rbx
	movl	104(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %r12
	movl	108(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %r13
	movl	112(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %r14
	movl	116(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %r15
	movl	120(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	movq	%rax, 16(%rsp)
	movl	124(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	movq	%rax, 8(%rsp)
	movl	128(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	movq	%rax, (%rsp)
	movl	$0, 76(%rsp)
	jmp	.L40
.L50:
	movl	76(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%rbx, %rax
	movq	%rax, 168(%rsp)
	movq	168(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 320(%rsp)
	movl	76(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%r12, %rax
	movq	%rax, 176(%rsp)
	movq	176(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 352(%rsp)
	movl	76(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%r13, %rax
	movq	%rax, 184(%rsp)
	movq	184(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 384(%rsp)
	movl	76(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%r14, %rax
	movq	%rax, 192(%rsp)
	movq	192(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 416(%rsp)
	movl	76(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%r15, %rax
	movq	%rax, 200(%rsp)
	movq	200(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 448(%rsp)
	movl	76(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	16(%rsp), %rax
	movq	%rax, 208(%rsp)
	movq	208(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 480(%rsp)
	movl	76(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	8(%rsp), %rax
	movq	%rax, 216(%rsp)
	movq	216(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 512(%rsp)
	movl	76(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	(%rsp), %rax
	movq	%rax, 224(%rsp)
	movq	224(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 544(%rsp)
	movl	76(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, 232(%rsp)
	movq	232(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 608(%rsp)
	vmovaps	320(%rsp), %ymm1
	vmovaps	352(%rsp), %ymm0
	vaddps	%ymm0, %ymm1, %ymm1
	vmovaps	384(%rsp), %ymm0
	vaddps	%ymm0, %ymm1, %ymm1
	vmovaps	416(%rsp), %ymm0
	vaddps	%ymm0, %ymm1, %ymm1
	vmovaps	448(%rsp), %ymm0
	vaddps	%ymm0, %ymm1, %ymm1
	vmovaps	480(%rsp), %ymm0
	vaddps	%ymm0, %ymm1, %ymm1
	vmovaps	512(%rsp), %ymm0
	vaddps	%ymm0, %ymm1, %ymm1
	vmovaps	544(%rsp), %ymm0
	vaddps	%ymm0, %ymm1, %ymm0
	vaddps	608(%rsp), %ymm0, %ymm0
	vmovaps	%ymm0, 608(%rsp)
#APP
# 147 "sparse_matrix.c" 1
	vmovaps 320(%rsp), %ymm0 
	vmovaps 352(%rsp), %ymm1 
	vmovaps 384(%rsp), %ymm2 
	vmovaps 384(%rsp), %ymm3 
	vaddps %ymm0, %ymm1, %ymm1 
	vaddps %ymm2, %ymm3, %ymm3 
	vaddps %ymm1, %ymm3, %ymm3 
	vmovaps %ymm3, 576(%rsp)
# 0 "" 2
#NO_APP
	vmovss	576(%rsp), %xmm0
	vunpcklps	%xmm0, %xmm0, %xmm0
	vcvtps2pd	%xmm0, %xmm2
	vmovss	352(%rsp), %xmm0
	vunpcklps	%xmm0, %xmm0, %xmm0
	vcvtps2pd	%xmm0, %xmm1
	vmovss	320(%rsp), %xmm0
	vunpcklps	%xmm0, %xmm0, %xmm0
	vcvtps2pd	%xmm0, %xmm0
	movq	stderr(%rip), %rax
	movl	$.LC8, %esi
	movq	%rax, %rdi
	movl	$3, %eax
	call	fprintf
	movl	76(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, 240(%rsp)
	vmovaps	608(%rsp), %ymm0
	vmovaps	%ymm0, 832(%rsp)
	movq	240(%rsp), %rax
	vmovaps	832(%rsp), %ymm0
	vmovaps	%ymm0, (%rax)
	addl	$8, 76(%rsp)
.L40:
	movl	76(%rsp), %eax
	cmpl	32(%rsp), %eax
	jl	.L50
	addl	$8, 72(%rsp)
.L39:
	movl	72(%rsp), %eax
	cmpl	96(%rsp), %eax
	jl	.L51
	movl	88(%rsp), %eax
	subl	$4, %eax
	cmpl	72(%rsp), %eax
	jl	.L52
	movl	72(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 132(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 136(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 140(%rsp)
	movl	72(%rsp), %eax
	cltq
	addq	$3, %rax
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 144(%rsp)
	movl	132(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %rbx
	movl	136(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %r12
	movl	140(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %r13
	movl	144(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	leaq	(%rdx,%rax), %r14
	movl	$0, 80(%rsp)
	jmp	.L53
.L59:
	movl	80(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%rbx, %rax
	movq	%rax, 248(%rsp)
	movq	248(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 640(%rsp)
	movl	80(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%r12, %rax
	movq	%rax, 256(%rsp)
	movq	256(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 672(%rsp)
	movl	80(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%r13, %rax
	movq	%rax, 264(%rsp)
	movq	264(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 704(%rsp)
	movl	80(%rsp), %eax
	cltq
	salq	$2, %rax
	addq	%r14, %rax
	movq	%rax, 272(%rsp)
	movq	272(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 736(%rsp)
	movl	80(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, 280(%rsp)
	movq	280(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 768(%rsp)
	vmovaps	672(%rsp), %ymm0
	vmovaps	640(%rsp), %ymm1
	vaddps	%ymm0, %ymm1, %ymm0
	vaddps	704(%rsp), %ymm0, %ymm0
	vaddps	736(%rsp), %ymm0, %ymm0
	vaddps	768(%rsp), %ymm0, %ymm0
	vmovaps	%ymm0, 768(%rsp)
	movl	80(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, 288(%rsp)
	vmovaps	768(%rsp), %ymm0
	vmovaps	%ymm0, 864(%rsp)
	movq	288(%rsp), %rax
	vmovaps	864(%rsp), %ymm0
	vmovaps	%ymm0, (%rax)
	addl	$8, 80(%rsp)
.L53:
	movl	80(%rsp), %eax
	cmpl	32(%rsp), %eax
	jl	.L59
	addl	$4, 72(%rsp)
	jmp	.L60
.L52:
	jmp	.L60
.L65:
	movl	72(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	152(%rsp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 148(%rsp)
	movl	148(%rsp), %eax
	imull	28(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	movq	%rax, 160(%rsp)
	movl	$0, 84(%rsp)
	jmp	.L61
.L64:
	movl	84(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, 296(%rsp)
	movq	296(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 800(%rsp)
	movl	84(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	160(%rsp), %rax
	addq	%rdx, %rax
	movq	%rax, 304(%rsp)
	movq	304(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vaddps	800(%rsp), %ymm0, %ymm0
	vmovaps	%ymm0, 800(%rsp)
	movl	84(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, 312(%rsp)
	vmovaps	800(%rsp), %ymm0
	vmovaps	%ymm0, 896(%rsp)
	movq	312(%rsp), %rax
	vmovaps	896(%rsp), %ymm0
	vmovaps	%ymm0, (%rax)
	addl	$8, 84(%rsp)
.L61:
	movl	84(%rsp), %eax
	cmpl	32(%rsp), %eax
	jl	.L64
	addl	$1, 72(%rsp)
.L60:
	movl	72(%rsp), %eax
	cmpl	88(%rsp), %eax
	jl	.L65
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE716:
	.size	accumulateRows, .-accumulateRows
	.section	.rodata
.LC9:
	.string	"scaler != 0"
	.text
	.globl	scaleRow
	.type	scaleRow, @function
scaleRow:
.LFB717:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	andq	$-32, %rsp
	subq	$288, %rsp
	movl	%edi, 28(%rsp)
	vmovss	%xmm0, 24(%rsp)
	movq	%rsi, 16(%rsp)
	movq	%rdx, 8(%rsp)
	vxorps	%xmm0, %xmm0, %xmm0
	vucomiss	24(%rsp), %xmm0
	jp	.L67
	vxorps	%xmm0, %xmm0, %xmm0
	vucomiss	24(%rsp), %xmm0
	jne	.L67
	movl	$__PRETTY_FUNCTION__.5506, %ecx
	movl	$205, %edx
	movl	$.LC0, %esi
	movl	$.LC9, %edi
	call	__assert_fail
.L67:
	movl	24(%rsp), %eax
	movl	%eax, 36(%rsp)
	vbroadcastss	36(%rsp), %ymm0
	vmovaps	%ymm0, 64(%rsp)
	movl	$0, 32(%rsp)
	jmp	.L70
.L74:
	movl	32(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rsp), %rax
	addq	%rdx, %rax
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 96(%rsp)
	movl	32(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	8(%rsp), %rax
	addq	%rdx, %rax
	movq	%rax, 48(%rsp)
	movq	48(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 128(%rsp)
	vmovaps	96(%rsp), %ymm0
	vmovaps	%ymm0, 192(%rsp)
	vmovaps	64(%rsp), %ymm0
	vmovaps	%ymm0, 224(%rsp)
	vmovaps	224(%rsp), %ymm0
	vmovaps	192(%rsp), %ymm1
	vmulps	%ymm0, %ymm1, %ymm0
	vmovaps	%ymm0, 160(%rsp)
	vmovaps	128(%rsp), %ymm0
	vmovaps	160(%rsp), %ymm1
	vaddps	%ymm0, %ymm1, %ymm0
	vmovaps	%ymm0, 160(%rsp)
	movl	32(%rsp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	8(%rsp), %rax
	addq	%rdx, %rax
	movq	%rax, 56(%rsp)
	vmovaps	160(%rsp), %ymm0
	vmovaps	%ymm0, 256(%rsp)
	movq	56(%rsp), %rax
	vmovaps	256(%rsp), %ymm0
	vmovaps	%ymm0, (%rax)
	addl	$8, 32(%rsp)
.L70:
	movl	32(%rsp), %eax
	cmpl	28(%rsp), %eax
	jl	.L74
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE717:
	.size	scaleRow, .-scaleRow
	.globl	ScaleMatrixTo
	.type	ScaleMatrixTo, @function
ScaleMatrixTo:
.LFB718:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, %rax
	movq	%rsi, %r10
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movq	%r10, %rdi
	movq	%rsi, -80(%rbp)
	movq	%rdi, -72(%rbp)
	movq	%rdx, -88(%rbp)
	movl	%ecx, -92(%rbp)
	movl	%r8d, -96(%rbp)
	movl	%r9d, -100(%rbp)
	movl	-76(%rbp), %eax
	movl	%eax, -52(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -40(%rbp)
	movl	-80(%rbp), %eax
	movl	%eax, -48(%rbp)
	movl	-96(%rbp), %eax
	cltq
	salq	$2, %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	_mm_malloc
	movq	%rax, -32(%rbp)
	movl	$0, -56(%rbp)
	jmp	.L78
.L79:
	movl	-56(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	imull	40(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movl	-100(%rbp), %r9d
	movl	-96(%rbp), %r8d
	movl	-92(%rbp), %ecx
	movq	-88(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdi
	movq	%rdi, (%rsp)
	movq	%rsi, %rdi
	movq	%rax, %rsi
	call	accumulateRows
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movl	-48(%rbp), %eax
	movl	-96(%rbp), %ecx
	movl	%eax, -104(%rbp)
	vmovss	-104(%rbp), %xmm0
	movl	%ecx, %edi
	call	scaleRow
	addl	$1, -56(%rbp)
.L78:
	movl	-56(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L79
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE718:
	.size	ScaleMatrixTo, .-ScaleMatrixTo
	.section	.rodata
.LC10:
	.string	"((unsigned long)B & 31) == 0"
.LC11:
	.string	"M == getNumberOfRow(A)"
.LC12:
	.string	"K == getNumberOfCol(A)"
	.text
	.globl	SparseMatrixMultiplication
	.type	SparseMatrixMultiplication, @function
SparseMatrixMultiplication:
.LFB719:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movl	%edi, -52(%rbp)
	movl	%esi, -56(%rbp)
	movl	%edx, -60(%rbp)
	movq	%rcx, -72(%rbp)
	movq	%r8, -80(%rbp)
	movl	%r9d, -64(%rbp)
	movq	-80(%rbp), %rax
	andl	$31, %eax
	testq	%rax, %rax
	je	.L81
	movl	$__PRETTY_FUNCTION__.5547, %ecx
	movl	$245, %edx
	movl	$.LC0, %esi
	movl	$.LC10, %edi
	call	__assert_fail
.L81:
	movl	-52(%rbp), %ebx
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	getNumberOfRow
	cmpl	%eax, %ebx
	je	.L82
	movl	$__PRETTY_FUNCTION__.5547, %ecx
	movl	$246, %edx
	movl	$.LC0, %esi
	movl	$.LC11, %edi
	call	__assert_fail
.L82:
	movl	-60(%rbp), %ebx
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	getNumberOfCol
	cmpl	%eax, %ebx
	je	.L83
	movl	$__PRETTY_FUNCTION__.5547, %ecx
	movl	$247, %edx
	movl	$.LC0, %esi
	movl	$.LC12, %edi
	call	__assert_fail
.L83:
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	getNumberOfDistinctElement
	movl	%eax, -44(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	getScalers
	movq	%rax, -40(%rbp)
	movl	$0, -48(%rbp)
	jmp	.L84
.L89:
	movl	-48(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	vmovss	-32(%rbp), %xmm0
	vunpcklps	%xmm0, %xmm0, %xmm0
	vcvtps2pd	%xmm0, %xmm0
	vmovsd	.LC13(%rip), %xmm1
	vucomisd	%xmm0, %xmm1
	jbe	.L85
	vmovss	-32(%rbp), %xmm0
	vunpcklps	%xmm0, %xmm0, %xmm0
	vcvtps2pd	%xmm0, %xmm0
	vucomisd	.LC14(%rip), %xmm0
	ja	.L88
.L85:
	movl	-64(%rbp), %r9d
	movl	-56(%rbp), %r8d
	movl	-60(%rbp), %ecx
	movq	-80(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	24(%rbp), %edi
	movl	%edi, 24(%rsp)
	movl	-56(%rbp), %edi
	movl	%edi, 16(%rsp)
	movl	-52(%rbp), %edi
	movl	%edi, 8(%rsp)
	movq	16(%rbp), %rdi
	movq	%rdi, (%rsp)
	movq	%rsi, %rdi
	movq	%rax, %rsi
	call	ScaleMatrixTo
.L88:
	addl	$1, -48(%rbp)
.L84:
	movl	-48(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L89
	addq	$104, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE719:
	.size	SparseMatrixMultiplication, .-SparseMatrixMultiplication
	.section	.rodata
	.type	__PRETTY_FUNCTION__.5367, @object
	.size	__PRETTY_FUNCTION__.5367, 14
__PRETTY_FUNCTION__.5367:
	.string	"readInNewPair"
	.align 16
	.type	__PRETTY_FUNCTION__.5380, @object
	.size	__PRETTY_FUNCTION__.5380, 16
__PRETTY_FUNCTION__.5380:
	.string	"readInNewScaler"
	.align 16
	.type	__PRETTY_FUNCTION__.5392, @object
	.size	__PRETTY_FUNCTION__.5392, 18
__PRETTY_FUNCTION__.5392:
	.string	"init_SparseMatrix"
	.type	__PRETTY_FUNCTION__.5506, @object
	.size	__PRETTY_FUNCTION__.5506, 9
__PRETTY_FUNCTION__.5506:
	.string	"scaleRow"
	.align 16
	.type	__PRETTY_FUNCTION__.5547, @object
	.size	__PRETTY_FUNCTION__.5547, 27
__PRETTY_FUNCTION__.5547:
	.string	"SparseMatrixMultiplication"
	.align 4
.LC7:
	.long	0
	.align 8
.LC13:
	.long	3944497965
	.long	1058682594
	.align 8
.LC14:
	.long	3944497965
	.long	-1088801054
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
