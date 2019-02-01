	.text
	.intel_syntax noprefix
	.file	"main.cpp"
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	lea	rdi, [rip + _ZStL8__ioinit]
	call	_ZNSt8ios_base4InitC1Ev@PLT
	mov	rdi, qword ptr [rip + _ZNSt8ios_base4InitD1Ev@GOTPCREL]
	lea	rsi, [rip + _ZStL8__ioinit]
	lea	rdx, [rip + __dso_handle]
	call	__cxa_atexit@PLT
	mov	dword ptr [rbp - 4], eax # 4-byte Spill
	add	rsp, 16
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc
                                        # -- End function
	.text
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 80
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rbp - 8], rax
	mov	dword ptr [rbp - 52], 0
	mov	dword ptr [rbp - 12], 7
	mov	dword ptr [rbp - 16], 13
	mov	rdi, qword ptr [rip + _ZSt3cin@GOTPCREL]
	lea	rax, [rbp - 12]
	mov	rsi, rax
	mov	qword ptr [rbp - 64], rax # 8-byte Spill
	call	_ZNSirsERi@PLT
	lea	rsi, [rbp - 16]
	mov	rdi, rax
	mov	qword ptr [rbp - 72], rsi # 8-byte Spill
	call	_ZNSirsERi@PLT
	#APP

	#############################################

	#NO_APP
	mov	ecx, dword ptr [rbp - 12]
	mov	dword ptr [rbp - 56], ecx
	mov	ecx, dword ptr [rbp - 16]
	mov	dword ptr [rbp - 12], ecx
	mov	ecx, dword ptr [rbp - 56]
	mov	dword ptr [rbp - 16], ecx
	#APP

	#############################################

	#NO_APP
	mov	rdi, qword ptr [rbp - 64] # 8-byte Reload
	mov	rsi, qword ptr [rbp - 72] # 8-byte Reload
	mov	qword ptr [rbp - 80], rax # 8-byte Spill
	call	_Z4swapIiEvRT_S1_
	#APP

	#############################################

	#NO_APP
	mov	rdi, qword ptr [rbp - 64] # 8-byte Reload
	mov	rsi, qword ptr [rbp - 72] # 8-byte Reload
	call	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	#APP

	#############################################

	#NO_APP
	mov	rax, qword ptr [rbp - 64] # 8-byte Reload
	mov	qword ptr [rbp - 32], rax
	mov	rsi, qword ptr [rbp - 72] # 8-byte Reload
	mov	qword ptr [rbp - 24], rsi
	movups	xmm0, xmmword ptr [rbp - 32]
	movaps	xmmword ptr [rbp - 48], xmm0
	mov	rdi, qword ptr [rbp - 48]
	mov	rsi, qword ptr [rbp - 40]
	call	_Z6dofuncIZ4mainE3$_0EvT_
	#APP

	#############################################

	#NO_APP
	mov	rax, qword ptr fs:[40]
	mov	rsi, qword ptr [rbp - 8]
	cmp	rax, rsi
	jne	.LBB1_2
# %bb.1:
	xor	eax, eax
	add	rsp, 80
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.LBB1_2:
	.cfi_def_cfa rbp, 16
	call	__stack_chk_fail@PLT
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	.text._Z4swapIiEvRT_S1_,"axG",@progbits,_Z4swapIiEvRT_S1_,comdat
	.weak	_Z4swapIiEvRT_S1_       # -- Begin function _Z4swapIiEvRT_S1_
	.p2align	4, 0x90
	.type	_Z4swapIiEvRT_S1_,@function
_Z4swapIiEvRT_S1_:                      # @_Z4swapIiEvRT_S1_
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 8], rdi
	mov	qword ptr [rbp - 16], rsi
	mov	rsi, qword ptr [rbp - 8]
	mov	eax, dword ptr [rsi]
	mov	dword ptr [rbp - 20], eax
	mov	rsi, qword ptr [rbp - 16]
	mov	eax, dword ptr [rsi]
	mov	rsi, qword ptr [rbp - 8]
	mov	dword ptr [rsi], eax
	mov	eax, dword ptr [rbp - 20]
	mov	rsi, qword ptr [rbp - 16]
	mov	dword ptr [rsi], eax
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end2:
	.size	_Z4swapIiEvRT_S1_, .Lfunc_end2-_Z4swapIiEvRT_S1_
	.cfi_endproc
                                        # -- End function
	.section	.text._ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,"axG",@progbits,_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,comdat
	.weak	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_ # -- Begin function _ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.p2align	4, 0x90
	.type	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,@function
_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_: # @_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rbp - 8], rax
	mov	qword ptr [rbp - 24], rdi
	mov	qword ptr [rbp - 32], rsi
	mov	rdi, qword ptr [rbp - 24]
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	mov	ecx, dword ptr [rax]
	mov	dword ptr [rbp - 12], ecx
	mov	rdi, qword ptr [rbp - 32]
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	mov	ecx, dword ptr [rax]
	mov	rax, qword ptr [rbp - 24]
	mov	dword ptr [rax], ecx
	lea	rdi, [rbp - 12]
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	mov	ecx, dword ptr [rax]
	mov	rax, qword ptr [rbp - 32]
	mov	dword ptr [rax], ecx
	mov	rax, qword ptr fs:[40]
	mov	rsi, qword ptr [rbp - 8]
	cmp	rax, rsi
	jne	.LBB3_2
# %bb.1:
	add	rsp, 32
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.LBB3_2:
	.cfi_def_cfa rbp, 16
	call	__stack_chk_fail@PLT
.Lfunc_end3:
	.size	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_, .Lfunc_end3-_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.cfi_endproc
                                        # -- End function
	.text
	.p2align	4, 0x90         # -- Begin function _Z6dofuncIZ4mainE3$_0EvT_
	.type	_Z6dofuncIZ4mainE3$_0EvT_,@function
_Z6dofuncIZ4mainE3$_0EvT_:              # @"_Z6dofuncIZ4mainE3$_0EvT_"
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rbp - 8], rax
	mov	qword ptr [rbp - 24], rdi
	mov	qword ptr [rbp - 16], rsi
	lea	rdi, [rbp - 24]
	call	_ZZ4mainENK3$_0clEv
	mov	rax, qword ptr fs:[40]
	mov	rsi, qword ptr [rbp - 8]
	cmp	rax, rsi
	jne	.LBB4_2
# %bb.1:
	add	rsp, 32
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.LBB4_2:
	.cfi_def_cfa rbp, 16
	call	__stack_chk_fail@PLT
.Lfunc_end4:
	.size	_Z6dofuncIZ4mainE3$_0EvT_, .Lfunc_end4-_Z6dofuncIZ4mainE3$_0EvT_
	.cfi_endproc
                                        # -- End function
	.section	.text._ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,"axG",@progbits,_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,comdat
	.weak	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_ # -- Begin function _ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.p2align	4, 0x90
	.type	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,@function
_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_: # @_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 8], rdi
	mov	rax, qword ptr [rbp - 8]
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end5:
	.size	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_, .Lfunc_end5-_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.cfi_endproc
                                        # -- End function
	.text
	.p2align	4, 0x90         # -- Begin function _ZZ4mainENK3$_0clEv
	.type	_ZZ4mainENK3$_0clEv,@function
_ZZ4mainENK3$_0clEv:                    # @"_ZZ4mainENK3$_0clEv"
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 8], rdi
	mov	rdi, qword ptr [rbp - 8]
	mov	rax, qword ptr [rdi]
	mov	ecx, dword ptr [rax]
	mov	dword ptr [rbp - 12], ecx
	mov	rax, qword ptr [rdi + 8]
	mov	ecx, dword ptr [rax]
	mov	rax, qword ptr [rdi]
	mov	dword ptr [rax], ecx
	mov	ecx, dword ptr [rbp - 12]
	mov	rax, qword ptr [rdi + 8]
	mov	dword ptr [rax], ecx
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end6:
	.size	_ZZ4mainENK3$_0clEv, .Lfunc_end6-_ZZ4mainENK3$_0clEv
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_main.cpp
	.type	_GLOBAL__sub_I_main.cpp,@function
_GLOBAL__sub_I_main.cpp:                # @_GLOBAL__sub_I_main.cpp
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	call	__cxx_global_var_init
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end7:
	.size	_GLOBAL__sub_I_main.cpp, .Lfunc_end7-_GLOBAL__sub_I_main.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_main.cpp

	.ident	"clang version 7.0.0 (tags/RELEASE_700/final)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __cxx_global_var_init
	.addrsig_sym __cxa_atexit
	.addrsig_sym main
	.addrsig_sym _ZNSirsERi
	.addrsig_sym _Z4swapIiEvRT_S1_
	.addrsig_sym _ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.addrsig_sym _Z6dofuncIZ4mainE3$_0EvT_
	.addrsig_sym _ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.addrsig_sym _ZZ4mainENK3$_0clEv
	.addrsig_sym _GLOBAL__sub_I_main.cpp
	.addrsig_sym __stack_chk_fail
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
	.addrsig_sym _ZSt3cin
