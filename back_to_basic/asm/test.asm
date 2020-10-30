	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.file	1 "/Users/gimsehwan/Desktop/ingkle/c_study/c_study" "c_study/main.c"
	.globl	_dice                   ## -- Begin function dice
	.p2align	4, 0x90
_dice:                                  ## @dice
Lfunc_begin0:
	.loc	1 3 0                   ## c_study/main.c:3:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
Ltmp0:
	.loc	1 4 32 prologue_end     ## c_study/main.c:4:32
	movl	-4(%rbp), %esi
	.loc	1 4 5 is_stmt 0         ## c_study/main.c:4:5
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	.loc	1 5 1 is_stmt 1         ## c_study/main.c:5:1
	addq	$16, %rsp
	popq	%rbp
	retq
Ltmp1:
Lfunc_end0:
	.cfi_endproc
                                        ## -- End function
	.globl	_add                    ## -- Begin function add
	.p2align	4, 0x90
_add:                                   ## @add
Lfunc_begin1:
	.loc	1 7 0                   ## c_study/main.c:7:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
Ltmp2:
	.loc	1 8 12 prologue_end     ## c_study/main.c:8:12
	movl	-4(%rbp), %eax
	.loc	1 8 14 is_stmt 0        ## c_study/main.c:8:14
	addl	-8(%rbp), %eax
	.loc	1 8 5                   ## c_study/main.c:8:5
	popq	%rbp
	retq
Ltmp3:
Lfunc_end1:
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
Lfunc_begin2:
	.loc	1 11 0 is_stmt 1        ## c_study/main.c:11:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
Ltmp4:
	.loc	1 12 9 prologue_end     ## c_study/main.c:12:9
	movl	$10, -8(%rbp)
	.loc	1 13 9                  ## c_study/main.c:13:9
	movl	$20, -12(%rbp)
	.loc	1 14 24                 ## c_study/main.c:14:24
	movl	-8(%rbp), %edi
	.loc	1 14 26 is_stmt 0       ## c_study/main.c:14:26
	movl	-12(%rbp), %esi
	.loc	1 14 20                 ## c_study/main.c:14:20
	callq	_add
	.loc	1 14 5                  ## c_study/main.c:14:5
	leaq	L_.str.1(%rip), %rdi
	movl	%eax, %esi
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	.loc	1 15 5 is_stmt 1        ## c_study/main.c:15:5
	movl	%ecx, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
Ltmp5:
Lfunc_end2:
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"throw dice! %d\n"

L_.str.1:                               ## @.str.1
	.asciz	"%d\n"

	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.asciz	"Apple clang version 12.0.0 (clang-1200.0.32.21)" ## string offset=0
	.asciz	"/Users/gimsehwan/Desktop/ingkle/c_study/c_study/c_study/main.c" ## string offset=48
	.asciz	"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk" ## string offset=111
	.asciz	"MacOSX10.15.sdk"       ## string offset=211
	.asciz	"/Users/gimsehwan/Desktop/ingkle/c_study/c_study" ## string offset=227
	.asciz	"Darwin"                ## string offset=275
	.asciz	"\"-DDEBUG=1\""         ## string offset=282
	.asciz	"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/include" ## string offset=294
	.asciz	"C"                     ## string offset=406
	.asciz	"stdio"                 ## string offset=408
	.asciz	"dice"                  ## string offset=414
	.asciz	"add"                   ## string offset=419
	.asciz	"main"                  ## string offset=423
	.asciz	"int"                   ## string offset=428
	.asciz	"input"                 ## string offset=432
	.asciz	"a"                     ## string offset=438
	.asciz	"b"                     ## string offset=440
	.asciz	"x"                     ## string offset=442
	.asciz	"y"                     ## string offset=444
	.asciz	"/Users/gimsehwan/Library/Developer/Xcode/DerivedData/ModuleCache.noindex/Q2N7KSZ3BDOJ/Darwin-1IVCWVLR6MT9T.pcm" ## string offset=446
	.section	__DWARF,__debug_abbrev,regular,debug
Lsection_abbrev:
	.byte	1                       ## Abbreviation Code
	.byte	17                      ## DW_TAG_compile_unit
	.byte	1                       ## DW_CHILDREN_yes
	.byte	37                      ## DW_AT_producer
	.byte	14                      ## DW_FORM_strp
	.byte	19                      ## DW_AT_language
	.byte	5                       ## DW_FORM_data2
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.ascii	"\202|"                 ## DW_AT_LLVM_sysroot
	.byte	14                      ## DW_FORM_strp
	.ascii	"\357\177"              ## DW_AT_APPLE_sdk
	.byte	14                      ## DW_FORM_strp
	.byte	16                      ## DW_AT_stmt_list
	.byte	23                      ## DW_FORM_sec_offset
	.byte	27                      ## DW_AT_comp_dir
	.byte	14                      ## DW_FORM_strp
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	6                       ## DW_FORM_data4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	2                       ## Abbreviation Code
	.byte	30                      ## DW_TAG_module
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.ascii	"\201|"                 ## DW_AT_LLVM_config_macros
	.byte	14                      ## DW_FORM_strp
	.ascii	"\200|"                 ## DW_AT_LLVM_include_path
	.byte	14                      ## DW_FORM_strp
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	3                       ## Abbreviation Code
	.byte	30                      ## DW_TAG_module
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.ascii	"\201|"                 ## DW_AT_LLVM_config_macros
	.byte	14                      ## DW_FORM_strp
	.ascii	"\200|"                 ## DW_AT_LLVM_include_path
	.byte	14                      ## DW_FORM_strp
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	4                       ## Abbreviation Code
	.byte	8                       ## DW_TAG_imported_declaration
	.byte	0                       ## DW_CHILDREN_no
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	24                      ## DW_AT_import
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	5                       ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	6                       ## DW_FORM_data4
	.byte	64                      ## DW_AT_frame_base
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	25                      ## DW_FORM_flag_present
	.byte	63                      ## DW_AT_external
	.byte	25                      ## DW_FORM_flag_present
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	6                       ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	7                       ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	6                       ## DW_FORM_data4
	.byte	64                      ## DW_AT_frame_base
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	25                      ## DW_FORM_flag_present
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	25                      ## DW_FORM_flag_present
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	8                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	9                       ## Abbreviation Code
	.byte	36                      ## DW_TAG_base_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	62                      ## DW_AT_encoding
	.byte	11                      ## DW_FORM_data1
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	10                      ## Abbreviation Code
	.byte	17                      ## DW_TAG_compile_unit
	.byte	0                       ## DW_CHILDREN_no
	.byte	37                      ## DW_AT_producer
	.byte	14                      ## DW_FORM_strp
	.byte	19                      ## DW_AT_language
	.byte	5                       ## DW_FORM_data2
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	16                      ## DW_AT_stmt_list
	.byte	23                      ## DW_FORM_sec_offset
	.byte	27                      ## DW_AT_comp_dir
	.byte	14                      ## DW_FORM_strp
	.ascii	"\261B"                 ## DW_AT_GNU_dwo_id
	.byte	7                       ## DW_FORM_data8
	.ascii	"\260B"                 ## DW_AT_GNU_dwo_name
	.byte	14                      ## DW_FORM_strp
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	0                       ## EOM(3)
	.section	__DWARF,__debug_info,regular,debug
Lsection_info:
Lcu_begin0:
.set Lset0, Ldebug_info_end0-Ldebug_info_start0 ## Length of Unit
	.long	Lset0
Ldebug_info_start0:
	.short	4                       ## DWARF version number
.set Lset1, Lsection_abbrev-Lsection_abbrev ## Offset Into Abbrev. Section
	.long	Lset1
	.byte	8                       ## Address Size (in bytes)
	.byte	1                       ## Abbrev [1] 0xb:0xef DW_TAG_compile_unit
	.long	0                       ## DW_AT_producer
	.short	12                      ## DW_AT_language
	.long	48                      ## DW_AT_name
	.long	111                     ## DW_AT_LLVM_sysroot
	.long	211                     ## DW_AT_APPLE_sdk
.set Lset2, Lline_table_start0-Lsection_line ## DW_AT_stmt_list
	.long	Lset2
	.long	227                     ## DW_AT_comp_dir
	.quad	Lfunc_begin0            ## DW_AT_low_pc
.set Lset3, Lfunc_end2-Lfunc_begin0     ## DW_AT_high_pc
	.long	Lset3
	.byte	2                       ## Abbrev [2] 0x32:0x29 DW_TAG_module
	.long	275                     ## DW_AT_name
	.long	282                     ## DW_AT_LLVM_config_macros
	.long	294                     ## DW_AT_LLVM_include_path
	.byte	2                       ## Abbrev [2] 0x3f:0x1b DW_TAG_module
	.long	406                     ## DW_AT_name
	.long	282                     ## DW_AT_LLVM_config_macros
	.long	294                     ## DW_AT_LLVM_include_path
	.byte	3                       ## Abbrev [3] 0x4c:0xd DW_TAG_module
	.long	408                     ## DW_AT_name
	.long	282                     ## DW_AT_LLVM_config_macros
	.long	294                     ## DW_AT_LLVM_include_path
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	4                       ## Abbrev [4] 0x5b:0x7 DW_TAG_imported_declaration
	.byte	1                       ## DW_AT_decl_file
	.byte	1                       ## DW_AT_decl_line
	.long	76                      ## DW_AT_import
	.byte	5                       ## Abbrev [5] 0x62:0x24 DW_TAG_subprogram
	.quad	Lfunc_begin0            ## DW_AT_low_pc
.set Lset4, Lfunc_end0-Lfunc_begin0     ## DW_AT_high_pc
	.long	Lset4
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	414                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	3                       ## DW_AT_decl_line
                                        ## DW_AT_prototyped
                                        ## DW_AT_external
	.byte	6                       ## Abbrev [6] 0x77:0xe DW_TAG_formal_parameter
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	124
	.long	432                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	3                       ## DW_AT_decl_line
	.long	242                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	7                       ## Abbrev [7] 0x86:0x36 DW_TAG_subprogram
	.quad	Lfunc_begin1            ## DW_AT_low_pc
.set Lset5, Lfunc_end1-Lfunc_begin1     ## DW_AT_high_pc
	.long	Lset5
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	419                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	7                       ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	242                     ## DW_AT_type
                                        ## DW_AT_external
	.byte	6                       ## Abbrev [6] 0x9f:0xe DW_TAG_formal_parameter
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	124
	.long	438                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	7                       ## DW_AT_decl_line
	.long	242                     ## DW_AT_type
	.byte	6                       ## Abbrev [6] 0xad:0xe DW_TAG_formal_parameter
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	120
	.long	440                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	7                       ## DW_AT_decl_line
	.long	242                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	7                       ## Abbrev [7] 0xbc:0x36 DW_TAG_subprogram
	.quad	Lfunc_begin2            ## DW_AT_low_pc
.set Lset6, Lfunc_end2-Lfunc_begin2     ## DW_AT_high_pc
	.long	Lset6
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	423                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	11                      ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	242                     ## DW_AT_type
                                        ## DW_AT_external
	.byte	8                       ## Abbrev [8] 0xd5:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	120
	.long	442                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	12                      ## DW_AT_decl_line
	.long	242                     ## DW_AT_type
	.byte	8                       ## Abbrev [8] 0xe3:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	116
	.long	444                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	13                      ## DW_AT_decl_line
	.long	242                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	9                       ## Abbrev [9] 0xf2:0x7 DW_TAG_base_type
	.long	428                     ## DW_AT_name
	.byte	5                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	0                       ## End Of Children Mark
Ldebug_info_end0:
Lcu_begin1:
.set Lset7, Ldebug_info_end1-Ldebug_info_start1 ## Length of Unit
	.long	Lset7
Ldebug_info_start1:
	.short	4                       ## DWARF version number
.set Lset8, Lsection_abbrev-Lsection_abbrev ## Offset Into Abbrev. Section
	.long	Lset8
	.byte	8                       ## Address Size (in bytes)
	.byte	10                      ## Abbrev [10] 0xb:0x1f DW_TAG_compile_unit
	.long	0                       ## DW_AT_producer
	.short	12                      ## DW_AT_language
	.long	275                     ## DW_AT_name
.set Lset9, Lline_table_start0-Lsection_line ## DW_AT_stmt_list
	.long	Lset9
	.long	227                     ## DW_AT_comp_dir
	.quad	-8347940981868583520    ## DW_AT_GNU_dwo_id
	.long	446                     ## DW_AT_GNU_dwo_name
Ldebug_info_end1:
	.section	__DWARF,__apple_names,regular,debug
Lnames_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	3                       ## Header Bucket Count
	.long	3                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.long	0                       ## Bucket 1
	.long	-1                      ## Bucket 2
	.long	193486030               ## Hash in Bucket 1
	.long	2090185018              ## Hash in Bucket 1
	.long	2090499946              ## Hash in Bucket 1
.set Lset10, LNames2-Lnames_begin       ## Offset in Bucket 1
	.long	Lset10
.set Lset11, LNames0-Lnames_begin       ## Offset in Bucket 1
	.long	Lset11
.set Lset12, LNames1-Lnames_begin       ## Offset in Bucket 1
	.long	Lset12
LNames2:
	.long	419                     ## add
	.long	1                       ## Num DIEs
	.long	134
	.long	0
LNames0:
	.long	414                     ## dice
	.long	1                       ## Num DIEs
	.long	98
	.long	0
LNames1:
	.long	423                     ## main
	.long	1                       ## Num DIEs
	.long	188
	.long	0
	.section	__DWARF,__apple_objc,regular,debug
Lobjc_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_namespac,regular,debug
Lnamespac_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_types,regular,debug
Ltypes_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	1                       ## Header Hash Count
	.long	20                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	3                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.short	3                       ## DW_ATOM_die_tag
	.short	5                       ## DW_FORM_data2
	.short	4                       ## DW_ATOM_type_flags
	.short	11                      ## DW_FORM_data1
	.long	0                       ## Bucket 0
	.long	193495088               ## Hash in Bucket 0
.set Lset13, Ltypes0-Ltypes_begin       ## Offset in Bucket 0
	.long	Lset13
Ltypes0:
	.long	428                     ## int
	.long	1                       ## Num DIEs
	.long	242
	.short	36
	.byte	0
	.long	0
.subsections_via_symbols
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
Lline_table_start0:
