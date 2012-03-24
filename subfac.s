/* Compiles with subfac.c with gcc -m32 -o gs subfac.c subfac.s */ 
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_subfac
	.align	4, 0x90
_subfac:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	subl $24, %esp
	movl 8(%ebp), %ebx /* Store n */
	movl 12(%ebp), %esi /* Store i0 */ 
	movl $1, %eax /* Store result */
	movl $1, %edi /*Store i*/
	cmpl %edi, %ebx
	je .L2
.L1:
	imull %edi, %eax
	incl %edi
	negl %esi
	addl %esi, %eax
	cmpl  %ebx, %edi
	jle .L1
.L2:
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
