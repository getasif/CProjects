/*
* mulq.s: Takes 64 bit integers. 
* Author: Akshay
* Date: March 23, 2012
*/ 
	.section    __TEXT,__text,regular,pure_instructions
	.globl	_mulq
	.align	4, 0x90
_mulq:    
        movq    %rdi, %rax
        movq    %rdx, %r8
        mulq	%rsi
	movq    %rdx, (%r8)
	movq    %rax, (%rcx)
	ret
