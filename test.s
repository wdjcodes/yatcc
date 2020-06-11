	.file	"test.cpp"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, -4(%rbp)
	cmpl	$20, -4(%rbp)
	ja	.L11
	movl	-4(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L4(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L4(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L11-.L4
	.long	.L3-.L4
	.long	.L5-.L4
	.long	.L6-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L7-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L11-.L4
	.long	.L8-.L4
	.text
.L3:
	movl	$1, -4(%rbp)
	jmp	.L9
.L5:
	movl	$2, -4(%rbp)
	jmp	.L9
.L7:
	movl	$12, -4(%rbp)
	jmp	.L9
.L6:
	movl	$3, -4(%rbp)
	jmp	.L9
.L8:
	movl	$20, -4(%rbp)
	jmp	.L9
.L11:
	nop
.L9:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
