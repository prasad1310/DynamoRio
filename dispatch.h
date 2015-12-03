/* **********************************************************
 * Copyright (c) 2000-2008 VMware, Inc.  All rights reserved.
 * **********************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of VMware, Inc. nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL VMWARE, INC. OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/* Copyright (c) 2003-2007 Determina Corp. */
/* Copyright (c) 2001-2003 Massachusetts Institute of Technology */
/* Copyright (c) 2000-2001 Hewlett-Packard Company */

/* file "dispatch.h" */

#ifndef _DISPATCH_H_
#define _DISPATCH_H_ 1

/* returns true if pc is a point at which DynamoRIO should stop interpreting */
bool
is_stopping_point(dcontext_t *dcontext, app_pc pc);

/* central hub of control flow in DynamoRIO */
void
dispatch(dcontext_t *dcontext);

void
issue_last_system_call_from_app(dcontext_t *dcontext);

void
transfer_to_dispatch(dcontext_t *dcontext, priv_mcontext_t *mc, bool full_DR_state);

DR_API
long get_total_comp_time(); // Added by Surya - Returns the total compilation time calculated during DRIO execution when exit event hookup function calls the same

DR_API
int get_dispatch_call_cnt(); // Added by Surya - Returns the dispatch function call cnt tracked during DRIO execution when exit event hookup function calls the same

DR_API
int* get_frag_instr_cnt_arr(); // Added by Surya - Returns pointer to the array having the translated instruction counts for each of the newly created fragments

// Added by Surya - Start
DR_API
void __attribute__ ((noinline)) sn_fcache_exit_syscalls_subcat1(); // Dummy function to mark the fcache exit for syscall.

DR_API
void __attribute__ ((noinline)) sn_fcache_exit_ind_br_subcat2(); // Dummy function to mark the fcache exit for indirect branch resolution.

DR_API
void __attribute__ ((noinline)) sn_fcache_exit_dir_br_subcat3(); // Dummy function to mark the fcache exit for direct branch not in cache(next fragment to be executed not yet translated).

DR_API
void __attribute__ ((noinline)) sn_fcache_exit_no_dir_link_subcat4(); // Dummy function to mark the fcache exit for no direct linking allowed between previous fragment executed and the next fragment to be executed.

DR_API
void __attribute__ ((noinline)) sn_fcache_exit_dir_syscall_subcat5(); // Dummy function to mark the fcache exit for non-ignorable direct system call.


// Added by Surya - End


/* hooks on entry/exit to/from DR */
#define NO_HOOK ((void (*)(void)) NULL)

#define HOOK_ENABLED_HELPER SELF_PROTECT_ON_CXT_SWITCH

#define HOOK_ENABLED (HOOK_ENABLED_HELPER || INTERNAL_OPTION(single_thread_in_DR))

#define ENTER_DR_HOOK (HOOK_ENABLED ? entering_dynamorio : NO_HOOK)
#define EXIT_DR_HOOK  (HOOK_ENABLED ? exiting_dynamorio : NO_HOOK)

#define ENTERING_DR() do {   \
        if (HOOK_ENABLED)    \
            ENTER_DR_HOOK(); \
    } while (0);

#define EXITING_DR() do {    \
        if (HOOK_ENABLED)    \
            EXIT_DR_HOOK();  \
    } while (0);


/* magic value to set next_tag to, to indicate a return to native_exec */
#define BACK_TO_NATIVE_AFTER_SYSCALL ((app_pc)(ptr_uint_t) -1)

#endif /* _DISPATCH_H_ */
