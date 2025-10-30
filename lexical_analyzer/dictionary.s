	.file	"dictionary.c"
	.text
	.globl	CONST_words_keyword
	.section .rdata,"dr"
.LC0:
	.ascii "if\0"
.LC1:
	.ascii "else\0"
.LC2:
	.ascii "for\0"
.LC3:
	.ascii "while\0"
.LC4:
	.ascii "true\0"
.LC5:
	.ascii "false\0"
.LC6:
	.ascii "break\0"
.LC7:
	.ascii "var\0"
.LC8:
	.ascii "print\0"
.LC9:
	.ascii "continue\0"
	.data
	.align 32
CONST_words_keyword:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.quad	.LC5
	.quad	.LC6
	.quad	.LC7
	.quad	.LC8
	.quad	.LC9
	.globl	CONST_words_reserved
	.section .rdata,"dr"
.LC10:
	.ascii "switch\0"
.LC11:
	.ascii "func\0"
.LC12:
	.ascii "string\0"
.LC13:
	.ascii "return\0"
.LC14:
	.ascii "case\0"
.LC15:
	.ascii "default\0"
.LC16:
	.ascii "const\0"
.LC17:
	.ascii "null\0"
	.data
	.align 32
CONST_words_reserved:
	.quad	.LC10
	.quad	.LC11
	.quad	.LC12
	.quad	.LC13
	.quad	.LC14
	.quad	.LC15
	.quad	.LC16
	.quad	.LC17
	.globl	CONST_words_noise
	.section .rdata,"dr"
.LC18:
	.ascii "int\0"
.LC19:
	.ascii "float\0"
.LC20:
	.ascii "bool\0"
.LC21:
	.ascii "char\0"
	.data
	.align 32
CONST_words_noise:
	.quad	.LC18
	.quad	.LC19
	.quad	.LC20
	.quad	.LC21
	.globl	CONST_symbol_delimiters
	.section .rdata,"dr"
.LC22:
	.ascii ";\0"
.LC23:
	.ascii "semicolon\0"
.LC24:
	.ascii "(\0"
.LC25:
	.ascii "l_paren\0"
.LC26:
	.ascii ")\0"
.LC27:
	.ascii "r_paren\0"
.LC28:
	.ascii "{\0"
.LC29:
	.ascii "l_brace\0"
.LC30:
	.ascii "}\0"
.LC31:
	.ascii "r_brace\0"
.LC32:
	.ascii ",\0"
.LC33:
	.ascii "comma\0"
.LC34:
	.ascii "'\0"
.LC35:
	.ascii "s_quote\0"
.LC36:
	.ascii "\"\0"
.LC37:
	.ascii "d_quote\0"
	.data
	.align 32
CONST_symbol_delimiters:
	.quad	.LC22
	.quad	.LC23
	.quad	.LC24
	.quad	.LC25
	.quad	.LC26
	.quad	.LC27
	.quad	.LC28
	.quad	.LC29
	.quad	.LC30
	.quad	.LC31
	.quad	.LC32
	.quad	.LC33
	.quad	.LC34
	.quad	.LC35
	.quad	.LC36
	.quad	.LC37
	.globl	CONST_symbol_arithmetic
	.section .rdata,"dr"
.LC38:
	.ascii "++\0"
.LC39:
	.ascii "increment\0"
.LC40:
	.ascii "--\0"
.LC41:
	.ascii "decrement\0"
.LC42:
	.ascii "+=\0"
.LC43:
	.ascii "add_assign\0"
.LC44:
	.ascii "-=\0"
.LC45:
	.ascii "subtract_assign\0"
.LC46:
	.ascii "*=\0"
.LC47:
	.ascii "multiply_assign\0"
.LC48:
	.ascii "/=\0"
.LC49:
	.ascii "divide_assign\0"
.LC50:
	.ascii "%=\0"
.LC51:
	.ascii "modulo_assign\0"
.LC52:
	.ascii "^=\0"
.LC53:
	.ascii "power_assign\0"
.LC54:
	.ascii "*\0"
.LC55:
	.ascii "multiply\0"
.LC56:
	.ascii "+\0"
.LC57:
	.ascii "add\0"
.LC58:
	.ascii "-\0"
.LC59:
	.ascii "subtract\0"
.LC60:
	.ascii "/\0"
.LC61:
	.ascii "divide\0"
.LC62:
	.ascii "%\0"
.LC63:
	.ascii "modulo\0"
.LC64:
	.ascii "=\0"
.LC65:
	.ascii "assignment\0"
.LC66:
	.ascii "^\0"
.LC67:
	.ascii "power\0"
	.data
	.align 32
CONST_symbol_arithmetic:
	.quad	.LC38
	.quad	.LC39
	.quad	.LC40
	.quad	.LC41
	.quad	.LC42
	.quad	.LC43
	.quad	.LC44
	.quad	.LC45
	.quad	.LC46
	.quad	.LC47
	.quad	.LC48
	.quad	.LC49
	.quad	.LC50
	.quad	.LC51
	.quad	.LC52
	.quad	.LC53
	.quad	.LC54
	.quad	.LC55
	.quad	.LC56
	.quad	.LC57
	.quad	.LC58
	.quad	.LC59
	.quad	.LC60
	.quad	.LC61
	.quad	.LC62
	.quad	.LC63
	.quad	.LC64
	.quad	.LC65
	.quad	.LC66
	.quad	.LC67
	.globl	CONST_symbol_logical
	.section .rdata,"dr"
.LC68:
	.ascii "<\0"
.LC69:
	.ascii "less_than\0"
.LC70:
	.ascii ">\0"
.LC71:
	.ascii "greater_than\0"
.LC72:
	.ascii "!=\0"
.LC73:
	.ascii "not_equal\0"
.LC74:
	.ascii "==\0"
.LC75:
	.ascii "equal\0"
.LC76:
	.ascii "<=\0"
.LC77:
	.ascii "less_equal\0"
.LC78:
	.ascii ">=\0"
.LC79:
	.ascii "greater_equal\0"
	.data
	.align 32
CONST_symbol_logical:
	.quad	.LC68
	.quad	.LC69
	.quad	.LC70
	.quad	.LC71
	.quad	.LC72
	.quad	.LC73
	.quad	.LC74
	.quad	.LC75
	.quad	.LC76
	.quad	.LC77
	.quad	.LC78
	.quad	.LC79
	.globl	REGEX_ARRAY_LEN
	.section .rdata,"dr"
	.align 4
REGEX_ARRAY_LEN:
	.long	9
	.globl	REGEX_ARRAY
.LC80:
	.ascii "commment\0"
.LC81:
	.ascii "//[^\12/]+|///[^*]*///\0"
.LC82:
	.ascii "(\"[^\"]*\"|'[^']*')\0"
.LC83:
	.ascii "-?[0-9]+\\.[0-9]+\0"
.LC84:
	.ascii "integer\0"
.LC85:
	.ascii "-?[0-9]+\0"
.LC86:
	.ascii "delimiters\0"
.LC87:
	.ascii "\\(|\\)|{|}|;\0"
.LC88:
	.ascii "text\0"
.LC89:
	.ascii "[a-zA-Z_][a-zA-Z0-9_]*\0"
.LC90:
	.ascii "arithmetic\0"
	.align 8
.LC91:
	.ascii "\\+\\+?=?|\\-\\-?=?|\\*=?|/=?|%=?|\\^=?|=\0"
.LC92:
	.ascii "logical\0"
.LC93:
	.ascii "<|>|!|==|!=|<=|>=\0"
.LC94:
	.ascii "!! INVALID\0"
.LC95:
	.ascii "[^ \11\12]+\0"
	.data
	.align 32
REGEX_ARRAY:
	.quad	.LC80
	.quad	.LC81
	.quad	.LC12
	.quad	.LC82
	.quad	.LC19
	.quad	.LC83
	.quad	.LC84
	.quad	.LC85
	.quad	.LC86
	.quad	.LC87
	.quad	.LC88
	.quad	.LC89
	.quad	.LC90
	.quad	.LC91
	.quad	.LC92
	.quad	.LC93
	.quad	.LC94
	.quad	.LC95
	.section .rdata,"dr"
.LC96:
	.ascii "\0"
	.text
	.globl	dictionary_lookup_symbol
	.def	dictionary_lookup_symbol;	.scl	2;	.type	32;	.endef
	.seh_proc	dictionary_lookup_symbol
dictionary_lookup_symbol:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L5:
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	CONST_symbol_delimiters(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L3
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	8+CONST_symbol_delimiters(%rip), %rax
	movq	(%rdx,%rax), %rax
	jmp	.L4
.L3:
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	$7, %eax
	jbe	.L5
	movl	$0, -8(%rbp)
	jmp	.L6
.L8:
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	CONST_symbol_arithmetic(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L7
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	8+CONST_symbol_arithmetic(%rip), %rax
	movq	(%rdx,%rax), %rax
	jmp	.L4
.L7:
	addl	$1, -8(%rbp)
.L6:
	movl	-8(%rbp), %eax
	cmpl	$14, %eax
	jbe	.L8
	movl	$0, -12(%rbp)
	jmp	.L9
.L11:
	movl	-12(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	CONST_symbol_logical(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L10
	movl	-12(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	8+CONST_symbol_logical(%rip), %rax
	movq	(%rdx,%rax), %rax
	jmp	.L4
.L10:
	addl	$1, -12(%rbp)
.L9:
	movl	-12(%rbp), %eax
	cmpl	$5, %eax
	jbe	.L11
	leaq	.LC96(%rip), %rax
.L4:
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC97:
	.ascii "keyword\0"
.LC98:
	.ascii "reserved\0"
.LC99:
	.ascii "noise\0"
.LC100:
	.ascii "identifier\0"
	.text
	.globl	dictionary_lookup_text
	.def	dictionary_lookup_text;	.scl	2;	.type	32;	.endef
	.seh_proc	dictionary_lookup_text
dictionary_lookup_text:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L13
.L16:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	CONST_words_keyword(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L14
	leaq	.LC97(%rip), %rax
	jmp	.L15
.L14:
	addl	$1, -4(%rbp)
.L13:
	movl	-4(%rbp), %eax
	cmpl	$9, %eax
	jbe	.L16
	movl	$0, -8(%rbp)
	jmp	.L17
.L19:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	CONST_words_reserved(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L18
	leaq	.LC98(%rip), %rax
	jmp	.L15
.L18:
	addl	$1, -8(%rbp)
.L17:
	movl	-8(%rbp), %eax
	cmpl	$7, %eax
	jbe	.L19
	movl	$0, -12(%rbp)
	jmp	.L20
.L22:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	CONST_words_noise(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L21
	leaq	.LC99(%rip), %rax
	jmp	.L15
.L21:
	addl	$1, -12(%rbp)
.L20:
	movl	-12(%rbp), %eax
	cmpl	$3, %eax
	jbe	.L22
	leaq	.LC100(%rip), %rax
.L15:
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-msvcrt-posix-seh, built by Brecht Sanders, r1) 15.2.0"
	.def	strcmp;	.scl	2;	.type	32;	.endef
