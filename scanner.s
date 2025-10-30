	.file	"scanner.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "bx\0"
	.align 8
.LC1:
	.ascii "[WARNING] parser_scan_file: Invalid file extension: cannot compile files that are not \".bx\"\0"
	.align 8
.LC2:
	.ascii "parser_scan_file: valid file extension. reading file.\0"
.LC3:
	.ascii "r\0"
.LC4:
	.ascii "Error opening file\0"
	.align 8
.LC5:
	.ascii "[WARNING] parser_scan_file: memory allocation failed\0"
	.text
	.globl	parser_scan_file
	.def	parser_scan_file;	.scl	2;	.type	32;	.endef
	.seh_proc	parser_scan_file
parser_scan_file:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movl	$46, %edx
	movq	%rax, %rcx
	call	strrchr
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L2
	movq	-8(%rbp), %rax
	addq	$1, %rax
	leaq	.LC0(%rip), %rdx
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	je	.L3
.L2:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$1, %ecx
	call	exit
.L3:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC3(%rip), %rdx
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	fopen
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L4
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L4:
	movq	-16(%rbp), %rax
	movl	$2, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	call	fseek
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	ftell
	movl	%eax, -20(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	rewind
	movl	-20(%rbp), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rcx
	call	malloc
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L5
	leaq	.LC5(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	fclose
	movl	$1, %ecx
	call	exit
.L5:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %r9
	movq	%rdx, %r8
	movl	$1, %edx
	movq	%rax, %rcx
	call	fread
	movq	%rax, -40(%rbp)
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	fclose
	movq	-32(%rbp), %rax
	addq	$80, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-msvcrt-posix-seh, built by Brecht Sanders, r1) 15.2.0"
	.def	strrchr;	.scl	2;	.type	32;	.endef
	.def	strcmp;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	fopen;	.scl	2;	.type	32;	.endef
	.def	perror;	.scl	2;	.type	32;	.endef
	.def	fseek;	.scl	2;	.type	32;	.endef
	.def	ftell;	.scl	2;	.type	32;	.endef
	.def	rewind;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	fclose;	.scl	2;	.type	32;	.endef
	.def	fread;	.scl	2;	.type	32;	.endef
