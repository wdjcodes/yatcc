.globl main
main:
push	%rbp
mov	%rsp, %rbp
mov	$0, %rax
push	%rax
movl	$2, %eax
mov	%rax, -8(%rbp)
mov	-8(%rbp), %rax
mov	%rbp, %rsp
pop	%rbp
ret
