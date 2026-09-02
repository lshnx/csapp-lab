	.file	"cmp_flags.c"
	.text
	.globl	cmp_gt
	.def	cmp_gt;	.scl	2;	.type	32;	.endef
	.seh_proc	cmp_gt
cmp_gt:
	.seh_endprologue
	cmpl	%edx, %ecx
	setg	%al
	movzbl	%al, %eax
	ret
	.seh_endproc
	.globl	cmp_eq
	.def	cmp_eq;	.scl	2;	.type	32;	.endef
	.seh_proc	cmp_eq
cmp_eq:
	.seh_endprologue
	cmpl	%edx, %ecx
	sete	%al
	movzbl	%al, %eax
	ret
	.seh_endproc
	.globl	cmp_ltu
	.def	cmp_ltu;	.scl	2;	.type	32;	.endef
	.seh_proc	cmp_ltu
cmp_ltu:
	.seh_endprologue
	cmpl	%edx, %ecx
	setb	%al
	movzbl	%al, %eax
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
