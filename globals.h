/* **********************************************************
 * Copyright (c) 2011-2013 Google, Inc.  All rights reserved.
 * Copyright (c) 2000-2010 VMware, Inc.  All rights reserved.
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

/*
 * globals.h - global defines and typedefs, included in all files
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_ 1

#define SN_INJ_BLKS 1357
#define SURYA_CODE_INJECT 0 // Added by Surya
#define CAPTURE_CACHE_INFO 0// Added by Surya - Flag to include the code to capture the info on cache stats, like name of cache accessed, start_pc,end_pc,cur_pc after each fragment is added to respective cache
#define SN_PRIORITIZE_PREQ 0 // Added by Surya - To include(value 1)/exclude(value 0) the code to make eager translation give priority to the urgent parent request by breaking out of the eager translation loop.
#define SN_FINE_GRAIN_LOCK_WAIT 0 // Added by Surya - To include(value 1)/exclude(value 0) the code to do the fine grain lock wait while the bb translation is done in preq or etrans threads. *** if this flag is set to 1, probably have to set SN_PRIORITY_PREQ(above) to 1 as well ***

#define SN_1A_1UR_BASE_CASE 0 // Added by Surya - To exclude(value 1)/include(value 0) the code to append the next jaddr's in the list etrans, as part of eager translation. For the base case, we are just processing the jaddr needed by app in a different thread and no eager translation is done. SN_EXEC_WITH_ETRANS would be 1 to include code in dispatch to create a new thread, push jaddr on top of stack and wait for completion of required translation and resume once its done.For execution with eager translation, this flag should be set to 0 in order for the jaddr's to be appended or pushed to bottom of the stack.

#define SN_PRTZ_APP_REQ 0 // Flag to include code to prioritize the translation of jaddr needed by the app thread in the model 1A_N_ET Threads.
#define SN_EXEC_WITH_ETRANS 0 // To include code to run the app thread with eager threads. If set to 1 , set flag SN_NO_ETRANS_THREADS to 0.

#define SN_CHECK_CURR_TRANS_ADDR 1 // Added by Surya - To include(value 1)/exclude(value 0) the code to check if the current addr to be processed in a particular preq or etrans threads is being processed currently in a different thread, where in we make the thread about to start processing to wait until the request being processed by different thread is completed and signalled accordingly to do the lookup again and skip the translation if available in the lookup.
#define SN_DEBUG_CURR_TRANS_ADDR 1 // Added by Surya - To include(value 1)/exclude(value 0) the debug statements for the code included with checking the current translation address in different threads. 
#define CAPTURE_TOTAL_COMP_TIME 1 // Added by Surya - Flag to include code to calculate the total compilation time for all fragments while executing an application through DynamoRIO
//#define NUM_COMP_THREADS 3 // Added by Surya - Macro that holds the number of compiler threads being used with the implementation(preq thread + etrans threads).
#define SURYA_THREAD_SUSPEND_PRINT 1 // Flag to include the print statements in the function thread_suspend()(in core/unix/os.c) to print the preq_cnt and etrans_cnt at the end of app execution.
#define SURYA_THREAD_SIGNAL_PRINT 1 // Flag to include the print statement in the function thread_signal()(in core/unix/os.c) to see the signal number for the thread.
#define SURYA_NOTIFY_MSG_PRINT 1 // Flag to include the print statement in the function notify()(in core/utils.c) to see the message being printed to stdout.
#define SURYA_PROC_STATS 1 // Flag to include code that captures process stats from the /proc file-system.
#define SURYA_DEBUG 0 // Flag to include the debug code(essentially print statements).
#define SURYA_DCONTEXT2 0 // Flag to indicate two contexts are needed for compiler thread and application thread.
#define SURYA_INTERFACE2_APP_WAIT 0 // Flag to include the code of interface-2 where both parent and compiler threads wait.
#define SURYA_INTERFACE3_APP_PARALLEL 0 // Flag to include the code of interface-3 where parent waits when a bb is needed from compiler, but compiler thread does eager translation.
#define SURYA_CLR_STK_AT_PREQ 0 // Flag to clear the jaddr stack each time a parent request is to be served by compiler1.
#define SN_DEADLOCK_DEBUG 0 // Flag to include code related to debugging the deadlock scenarios with locks acquired in preq,etrans comp thread 1,etrans comp thread 2.
#define SN_THREAD_SYNC_DEBUG 0 // Flag to print statements to debug the synchronization between the threads. Purpose is same as SN_DEADLOCK_DEBUG, but there are other prints prior to the 1A_N_ET thread model, so, this flag is for the new print statements in dispatch and compiler_etrans.
#define SN_NUM_ETRANS_THREADS 5 // Number of eager translation threads to be created.
#define SN_MAX_KEA_PASS_CNT 2 // Number of time the etrans threads can parse the array to process the unloaded addresses in the application address space.
#define SN_CAPTURE_BB_TIMES 1 // Flag to include code to capture the bb translation and execution times
#define SN_STK_MOD_DEBUG 0 // To print statements for debugging the proper modification of the jaddr stack etrans_list. Basically if the push/pop operations are being done properly and the entry count is being updated consistently.
#define SN_NO_ETRANS_THREADS 0 // To capture the app_start_time & app_thread_pid when no etrans threads are created. If there are threads being created, will have the SN_EXEC_WITH_ETRANS flag set to 1. If this flag is set, set SN_EXEC_WITH_ETRANS to 0
#define SN_CHECK_ETRANS_ADDR_STALL_APP 0 // To exclude/include code in compiler_etrans3 routine for checking the etrans addrs in the array and remove any translations causing error.
#define SN_PRINT_MAPS_DISPATCH 0 // To include(1)/exclude(0) the code to print the proc maps in the dispatch function. A way to get evidence on how the time taken by app thread to get into code cache and check for next target influences the number of eager translations done in the compiler thread.
#define SN_DEBUG_KNOWN_ADDRS 1 // To include(1)/exclude(0) the print statements when running the code processing the known addrs array with eager translation threads.
#define SN_INCLUDE_DIR_ADDR_ARR_ETRANS 0 // To include(1)/exclude(0) the code to process pre-populated known direct addresses in an array through eager translation threads.
#define SN_RUN_WITH_COMP_THREADS 1 // To include(1)/exclude(0) the code to create compiler threads in dispatch(). Possible configurations of runs with compiler threads are: 1) With no eager translation, each compiler thread processes the given parent request(app thread picks a compiler thread to do the translation in round-robin fashion if more than one thread created). 2) With eager translation, where each compiler thread processes an entry from a pre-populated array of direct addresses. Set macro SN_INCLUDE_DIR_ADDR_ARR_ETRANS to 1 in this file in order to include code to be run in this configuration 3) With eager translation, where the direct addresses are picked during the bb translation process and populated in a list. Each thread processes an entry from this list during the eager translation process. So, the eager translation process progressively updates the list with more addresses to process. Set macro SN_EXEC_WITH_ETRANS to 1 in this file in order to include code to be run in this configuration.

#define SN_PREQ_PROC_ONLY_ROUND_ROBIN_DEBUG 0 // To include(1)/exclude(0) debug print statements for the configuration: preq processing only in round-robin scheme

#include "configure.h"
#include <pthread.h> // Added by Surya


int sn_ethread_wait_cnt; // Holds the cnt of threads in wait state.
char *sn_thread_index[SN_NUM_ETRANS_THREADS]; // Holds the thread # of individual thread.
const char *sn_preq_lock_list[150],*sn_comp1_lock_list[150],*sn_comp2_lock_list[150]; // Added by Surya - To keep track of the list of locks acquired and released by compiler threads 1 & 2.
int sn_urgent_request; // Added by Surya - Flag to indicate presence of urgent request. 1 - Yes; 0 - No.
int sn_bb_building_cnt,sn_bb_building_cnt1,sn_bb_building_cnt2; // Added by Surya - Flag set while the basic block is being translated
int sn_bb_lock_cnt,sn_bb_lock_cnt1,sn_bb_lock_cnt2; // Added by Surya - Keep count of the locks being acquired and released during the basic block translation.
int no_etrans_now; // Added by Surya - Flag to signify that parent request is being processed and no eager translation can be done until the request is complete.
int sn_subcat4_cnt; // Added by Surya - Count of the number of times the fcache exit sub-category4 has been reached in dispatch_exit_fcache_stats
int sn_build_fragment; // Added by Surya - Flag to indicate the execution flow from build_basic_block_fragment to get_ibl_routine_ex(important in disasembly of ibl routine in code cache
int sn_get_ibl_type; // Added by Surya - Another flag used for the same purpose as sn_build_fragment
unsigned int sn_ibl_routine_length; // Added by Surya - To hold the length of the ibl routine returned for a particular cti

int sn_new_fragment; // Added by Surya - Flag to indicate creation of new fragment(bb/trace with one bb)
int sn_frag_cnt1; // Added by Surya - Keep the count of the total new fragments(bb/trace with one bb) created
int pk_is_affinity; // Should we set processor affinity
int sn_bb_cnt; // Added by Surya
int sn_disassembly_bb_cnt; // Added by Surya
int sn_start_trace,sn_end_trace,sn_extend_trace; // Added by Surya
int sn_instr_cnt; // Added by Surya
int sn_trace_cnt; // Added by Surya
int sn_trace_blk_cnt,sn_trace_instr_cnt; // Added by Surya
int sn_total_instr_exec_cnt; // Added by Surya - To track the total instructions to be printed in the dispatch function
int sn_total_branch_instr_exec_cnt; // Added by Surya - To track the total branch instructions executed that would be printed in the dispatch function
int sn_total_direct_branch_instr_exec_cnt; // Added by Surya - To track the total direct branch instructions executed that would be displayed in the dispatch function
/* int total_indirect_branch_cnt; */
/* //Added by Surya - Start */

int wait_on_trans_addr_arr_comp1,wait_on_trans_addr_arr_comp2,wait_on_trans_addr_arr_comp3; // Flags to indicate that preq,etrans compiler1 or etrans compiler2 respectively are waiting for the 
unsigned long long preq_cnt,total_bb_cnt,preq_cnt_post_dir_addrs_proc; // Added by Surya - Holds the count of number of parent requests served in compiler1.
//unsigned long long hashtable_fragment_lookup_call_cnt; // Added by Surya - Holds the number of times the function hashtable_fragment_lookup
unsigned long long etrans_cnt; // Added by Surya - Holds the count of the number of requests served with eager translation.
int etrans_instance_jaddr_cnt; // Added by Surya - Keeps track of number of direct jumps in the basic block and accordingly the number of requests to be processed in eager translation thread 1.
int etrans_instance_jaddr_cnt1; // Added by Surya - Keeps track of number of direct jumps in the basic block and accordingly the number of requests to be processed in eager translation thread 2.
long long sn_fcache_entry_cnt;
long long total_comp_time; // To hold the total compilation time for all the fragment creation during application execution under DynamoRIO(CAPTURE_TOTAL_COMP_TIME)
long total_thread_elap_time[4]; // Holds the total elapsed time for app and other compiler threads in seconds.

int sn_dispatch_call_cnt; // To hold the number of dispatch call cnt which inturn gives info on the context switches between DRIO and App context

int collect_code_cache_stats; // Flag used to execute code that collects code cache info
int collect_context_switch_stats; // Flag used to execute code that collects context switch info
int collect_compilation_time_stats; // Flag used to execute code that collects compilation time info
int print_basic_block_info; // Flag used to execute code that prints the basic blocks


/* /\* we only have a global count *\/ */
/*  int global_count; */

/* int sn_bb_instr_cnt; //Added by Surya to get the number of instructions in a bb  */
/* int sn_total_exec_branch_instr; // To hold the total number of branch instructions(direct/indirect) executed */
/* int sn_total_exec_direct_branch_instr; // To hold the total number of direct branch instructions */

/* int bbs_eflags_saved; */
/* int bbs_no_eflags_saved; */

//static app_pc prev_cache_end_pc; // To compare if the trace cache end pc is greater than previous.
//static app_pc curr_cache_end_pc; // To keep track of max cache end pc.

const char *sn_cache_name; // Stores the name of the cache into which the trace fragment is placed
const char *sn_cache_region; // Stores the name of the region in the cache where the trace is being placed.
const char *sn_bb_cache_name; // Stores the name of the cache into which the basic block is inserted
long sn_total_shared_trace_cache_size_inc; // Stores the total increment in the size of shared_trace_cache 
int sn_trace_fragment; // Flag to indicate if the fragment is a trace fragment or not: 0 means "no", 1 means "yes".
int sn_bb_fragment; // Flag to indicate if the fragment is a basic block fragment or not: 0 means "no", 1 means "yes".
//cache_pc sn_cache_start_pc; // Stores the start pc of the cache.
//cache_pc sn_cache_end_pc; // Stores the start pc of the cache.

int free_list_slot_cnt; // Stores the number of free list slots in a bucket
int fifo_entry_cnt; // Stores the number of fifo entries
int sn_private_cache; // Flag to indicate if the trace cache is a private trace cache.
int sn_shared_cache; // Flag to indicate if the trace cache is a shared trace cache.
int sn_shared_coarse_cache; // Flag to indicate if the trace cache is a shared coarse cache.

int sn_bb_private_cache; // Flag to indicate if the bb cache is a private trace cache.
int sn_bb_shared_cache; // Flag to indicate if the bb cache is a shared trace cache.
int sn_bb_shared_coarse_cache; // Flag to indicate if the bb cache is a shared coarse cache.

int shared_coarse_cache_resize; // Flag to indicate that the shared coarse trace cache has been resized.
int shared_cache_resize; // Flag to indicate that the shared trace cache has been resized.
int private_cache_resize; // Flag to indicate that the private trace cache has been resized. 

int thread_flag; // Added by Surya - Used to hold the count of compiler threads created
int trans_flag; // Added by Surya - Used in interface3 for fetching the right private context.
int trans_flag_new; // Added by Surya - Used by parent thread to signify that there is an urgent bb translation to be serviced by the compiler thread.
int sn_signal_flag; // Added by Surya - Used to signal between parent and child when required condition is met.
pthread_mutex_t trans_lock; // Added by Surya - Interface2 synchronization mechanism between parent(signalling) and compiler(waiting for translation request from parent. May not be waiting during eager translation. Probably the signal sent by parent then would be lost or not used.) threads.
pthread_mutex_t trans_lock1; // Added by Surya - Interface2 synchronization mechanism between compiler(signalling) and parent(waiting for completion of translation in compiler thread) threads.
pthread_cond_t trans_flag_cv;
pthread_cond_t trans_flag_cv1;
pthread_mutex_t compiler_create_lock,compiler_create_lock1,compiler_create_lock2,etrans_lock,etrans_lock1,preq_lock,jaddr_list_lock,jaddr_list_lock1,comp1_stop_locking,comp2_stop_locking,fine_grain_wait_lock;
pthread_mutex_t curr_trans_addr_lock; // Lock to access the array holding the currently translated addresses by the preq and etrans threads.
pthread_cond_t curr_trans_addr_cv; // Condition variable to make preq and etrans threads wait/signal on the array curr_trans_addr
pthread_cond_t compiler_create_cond,comp1_stop_lck_cv,comp2_stop_lck_cv,fine_grain_wait_cv;
pthread_cond_t compiler_create_cond1,compiler_create_cond2;
pthread_cond_t trans_flag_cv_ct1_ct2,trans_flag_cv_ct1_ct3;
pthread_cond_t trans_flag_cv_ct3_ct1,jaddr_lock_cv,jaddr_lock_cv1,preq_wait;
int done_proc_dir_addrs;
pthread_t tid,tid1,tid2; // To store thread id of the new compiler thread. Used in pthread_create
pthread_attr_t attr,attr1,attr2; // Attr parameter for the new compiler thread used in pthread_create
int app_thread_state,compiler1_thread_state,compiler2_thread_state,compiler3_thread_state,etrans_flag,etrans_flag1,have_jaddr_lock,have_jaddr_lock1,waiting_on_jaddr_lock,waiting_on_jaddr_lock1,fine_grain_wait /* used only in compiler_parent_req function */; // To hold the state of compiler thread, either waiting for compilation request from parent or doing the eager compilation. This can be used by the parent thread to appropriately signal the compiler thread if it is waiting for a signal and to skip it if the compiler is doing the eager compilation at the time parent reaches the point where the request for compilation is set. Value 1 signifies WAIT state and 0 signifies EAGER COMPILATION state.

pthread_cond_t jaddr_list_cv; // Shared variable to be used in pthread_wait* and pthread_signal* routines to make threads wait and wake them up.
pthread_cond_t sn_preq_proc_only_cthread_cvs[SN_NUM_ETRANS_THREADS]; // Array of condition variables to be used by app thread to signal/wake desired compiler thread with the thread turn variable as array index. This way the round-robin fashion of bb translation can be done by multiple compiler threads.

pthread_t sn_tid[SN_NUM_ETRANS_THREADS]; // For etrans thread creation routine pthread_create*
pthread_attr_t sn_attr[SN_NUM_ETRANS_THREADS]; // For etrans thread creation routine pthread_create*

int sn_preq_proc_only_cthread_proc_status[SN_NUM_ETRANS_THREADS]; // Array of status variables used to keep track of the wait status of different compiler threads in the configuration to just process given parent request.

unsigned long long int sn_preq_proc_only_cthread_bb_cnt[SN_NUM_ETRANS_THREADS]; // Array to hold the individual bb cnts in multiple compiler threads. Used in the configuration for compiler threads to process the given preq in a round-robin fashion.

int sn_empty_stack; // Flag to signify whether the stack etrans_list is empty or not. 1: empty; 0: not empty.

int sn_dynamo_exited; // Global to be accessed
char *sn_curr_lock_list_preq[10],*sn_curr_lock_list_et_comp1[10],*sn_curr_lock_list_et_comp2[10],*sn_curr_lock_list_app[10];
int sn_curr_lck_cnt_preq,sn_curr_lck_cnt_et_comp1,sn_curr_lck_cnt_et_comp2,sn_curr_lck_cnt_app;

int new_eaddr; // Flag to indicate a new address out of the kea array to be processed.
int sn_cthread_turn_rrobin; // Keeps track of the next thread to process the required preq in a round-robin fashion.

// Added by Surya - End



 
#ifdef WINDOWS
/* Vista SDK compiler default is to set NTDDI_VERSION to NTDDI_LONGHORN, causing
 * problems w/ new Vista-only flags like in PROCESS_ALL_ACCESS in win32/injector.c.
 * The problematic flag there, PROCESS_QUERY_LIMITED_INFORMATION, is a subset of
 * PROCESS_QUERY_INFORMATION, so we don't lose anything by not asking for it on Vista.
 * But if they add new non-subset flags in the future we'd need dynamic dispatch,
 * as earlier Windows versions give access denied on unknown flags!
 */
#define _WIN32_WINNT _WIN32_WINNT_NT4 /* ==0x0400; NTDDI_VERSION is set from this */

#  define WIN32_LEAN_AND_MEAN
/* Exclude rarely-used stuff from Windows headers */

/* Case 1167 - bumping up warning level to 4 - work in progress FIXME: */
#pragma warning( disable : 4054) //from function pointer 'void (__cdecl *)(void )' to data pointer 'unsigned char *'
#pragma warning( disable : 4100) //'envp' : unreferenced formal parameter
#pragma warning( disable : 4127) //conditional expression is constant (majority of warnings - 2078)
#pragma warning( disable : 4189) //'start_pc' : local variable is initialized but not referenced
#pragma warning( disable : 4204) //nonstandard extension used : non-constant aggregate initializer
#pragma warning( disable : 4210) //nonstandard extension used : function given file scope
#pragma warning( disable : 4505) //unreferenced local function has been removed
#pragma warning( disable : 4702) //unreachable code (should be disabled DEBUG=0, e.g. for INTERNAL_OPTION test)
#pragma warning( disable : 4324) // structure was padded due to __declspec(align())
#pragma warning( disable : 4709) // comma operator within array index expression
#pragma warning( disable : 4214) // nonstandard extension used : bit field types other than int

/**************************************************/
/* warnings on compiling with VC 8.0, all on VC or PlatformSDK header files */

/* shows up in buildtools/VC/8.0/dist/VC/include/vadefs.h
 * supposed to include identifier in the pop pragma and they don't
 */
#pragma warning( disable : 4159) // #pragma pack has popped previously pushed identifier

/* FIXME case 191729: this is coming from our own code.  We could
 * switch to the _s versions when on Windows.
 */
#pragma warning( disable : 4996) //'sscanf' was declared deprecated

/**************************************************/

#endif

#include "globals_shared.h"

/* Added by Surya - Start */
struct kea_entry{
  app_pc known_addr;
  int loaded_in_mem;
};

typedef struct kea_entry kea_entry;

kea_entry known_etrans_addrs[67000]; // Added by Surya - To hold the known addresses. The size is the max addr cnt from all the bm's.
unsigned long int max_kea_cnt; // Added by Surya - To hold the max number of addresses populated in the array known_etrans_addrs. This will help in stopping the threads when this particular index is reached in the array.
int kea_pass_cnt; // Added by Surya - To keep track of the number of times the known_etrans_addr array is being parsed by the etrans threads.
unsigned long int curr_kea_arr_ind; // Added by Surya - To keep track of the current index being processed in the array known_etrans_addrs.
app_pc curr_trans_addr[SN_NUM_ETRANS_THREADS];  // To hold the addresses currently being processed by the etrans threads.
app_pc prev_trace_end_pc; // To compare if the trace cache end pc is greater than previous.
app_pc curr_trace_end_pc; // To keep track of max cache end pc with the end pc of curr trace fragment.
app_pc curr_trace_start_pc; // start pc of trace

//struct kea_tree{
//app_pc kea;
//struct kea_tree *left_sub_tree;
//struct kea_tree *right_sub_tree;
//};

//typedef struct kea_tree kea_tree; // Holds the array of known etrans addresses in a tree. This would be used to later search if the address needed by the app thread is already there in the tree or not. If not present in tree, it is probably a new indirect target address and needs to be processedby one of the eager threads. This can be indicated by setting a flag in the app thread

//kea_tree *kea_tree_root;

/* Added by Surya - End */

/* currently we always export statistics structure */
#define DYNAMORIO_STATS_EXPORTS 1

/* we only export IR interface if CLIENT_INTERFACE is defined */
#ifdef CLIENT_INTERFACE
/* in Makefile, we define these (so that genapi.pl, etc. get them):
 *    define DYNAMORIO_IR_EXPORTS 1
 *    define CUSTOM_EXIT_STUBS 1
 *    define CUSTOM_TRACES 1
 * CUSTOM_TRACES_RET_REMOVAL is aggressive -- assumes calling convention kept
 * Only useful if custom traces are doing inlining => do not define for external
 * release, or even by default for internal since it's always on even if
 * not building custom traces!
 */
#endif /* CLIENT_INTERFACE */

#  ifdef WINDOWS
#    define DYNAMORIO_EXPORT __declspec(dllexport)
#  elif defined(USE_VISIBILITY_ATTRIBUTES)
/* PR 262804: we use "protected" instead of "default" to ensure our
 * own uses won't be preempted.  Note that for DR_APP_API in
 * lib/dr_app.h we get a link error trying to use "protected": but we
 * don't use dr_app_* internally anyway, so leaving as default.
 */
#    define DYNAMORIO_EXPORT __attribute__ ((visibility ("protected")))
#  else
/* visibility attribute not available in gcc < 3.3 (we use linker script) */
#    define DYNAMORIO_EXPORT 
#  endif

#ifdef DYNAMORIO_IR_EXPORTS
#  define DR_API DYNAMORIO_EXPORT
#else
#  define DR_API 
#endif
#ifdef UNSUPPORTED_API
#  define DR_UNS_API DR_API
#else
#  define DR_UNS_API /* nothing */
#endif

#ifdef WINDOWS
# define NOINLINE __declspec(noinline)
#else
# define NOINLINE __attribute__((noinline))
#endif

#define INLINE_ONCE inline

#include <stdlib.h>
#include <stdio.h>

#include <execinfo.h> // Added by Surya

void *stackarr[10]; // Holds stack array
size_t stack_sz; // Holds the size of the stack
size_t stk_str_itr; // Holds the iterator for the loop to print the symbol strings in the stack
char **stk_fr_strs; // Holds the symbols of the stack frames

/* N.B.: some of these typedefs and defines are duplicated in
 * lib/globals_shared.h!
 */

#ifdef WINDOWS
#include <windows.h>
typedef unsigned long ulong;
typedef unsigned short ushort;
/* We can't put this in globals_shared.h b/c it needs windows.h and
 * not all users of globals_shared.h want that included, so we
 * duplicate it here (we do have Linux file_t stuff in globals_shared.h)
 */
/* since a FILE cannot be used outside of the DLL it was created in,
 * we have to use HANDLE on Windows
 * we hide the distinction behind the file_t type
 */
typedef HANDLE file_t;
#define INVALID_FILE INVALID_HANDLE_VALUE
#define STDOUT (file_t)get_stdout_handle()
#define STDERR (file_t)get_stderr_handle()
#define STDIN  (file_t)get_stdin_handle()
#define DIRSEP '\\'
#define ALT_DIRSEP '/'

#else /* UNIX */
/* uint, ushort, and ulong are in types.h */
# ifdef MACOS
typedef unsigned long ulong;
# endif
#include <sys/types.h> /* for wait */
#include <sys/time.h> // Added by Surya - For capturing times with gettimeofday
#include <dirent.h> // Added by Surya - For getting directory information(/proc) 
#define DIRSEP '/'
#define ALT_DIRSEP DIRSEP
#endif

// Added by Surya - Start
pid_t tid_for_dcontext,tid_for_dcontext1,tid_for_dcontext2; // Added by Surya - for getting the thread id of the corresponding thread. Needs <sys/types.h> included above.
//pid_t tid_for_dcontext[SN_NUM_ETRANS_THREADS]; // Added by Surya - To hold the dcontext's created for the desired number of eager translation threads. 
pid_t app_thread_pid,compiler_etrans3_pid;
file_t app_fp,comp1_fp,comp2_fp; // Added by Surya - File descriptors for the output files of app, comp1 and comp2

DIR *dip,*dip_etrans; // Pointer to desired directory.
struct dirent *dit,*dit_etrans; // Pointer to directory entry.
char *s_sn,tmp_str[5000],tmp_str_etrans[5000],proc_fname_sn[1000],proc_fname_sn_etrans[1000]; // Holds the path to the directory entry that can be later opened and content read.

file_t proc_file_ptr,proc_file_ptr_etrans; // Holds the pointer to the file opened from the /proc file system for time stats, during the app exit.

int count_sscanf; // Holds the return value of our_sscanf function.
int idummy; // Holds the extracted data from the /proc filesystem stat file.
long ldummy,btime_u_mode, btime_s_mode,wtime_u_mode,wtime_s_mode; // Holds the extracted data from the /proc filesystem stat file.

clock_t app_start_time,app_end_time,comp_start_time[SN_NUM_ETRANS_THREADS],total_clk_tks[SN_NUM_ETRANS_THREADS+1],app_bb_exec_start_clock,app_bb_exec_end_clock,total_bb_exec_ticks,app_bb_trans_start_clock,app_bb_trans_end_clock,total_bb_trans_ticks; // To capture the start and end times

clock_t total_thread_local_trans_ticks[SN_NUM_ETRANS_THREADS];
long long int thread_local_bb_cnts[SN_NUM_ETRANS_THREADS];
// Added by Surya - End

/* FIXME: what is range of thread_id_t on linux and on win32?
 * linux routines use -1 as sentinel, right?
 * on win32, are ids only 16 bits?
 * if so, change thread_id_t to be a signed int and use -1?
 * For now, based on observation, no process on linux and no thread on windows
 * has id 0 (on windows even a new thread in its init apc has a non-0 id)
 */
#define INVALID_THREAD_ID  0

typedef unsigned char uchar;
typedef byte * cache_pc;  /* fragment cache pc */


// Added by Surya - Start

static cache_pc sn_shared_coarse_cache_start_pc; // Stores the start pc of the shared coarse cache.
static cache_pc sn_shared_coarse_cache_end_pc; // Stores the end pc of the shared coarse cache.
static cache_pc sn_shared_coarse_cache_cur_pc; // Stores the current pc of the shared coarse cache.
static cache_pc sn_shared_coarse_cache_prev_end_pc; // Stores the previous end pc of the shared coarse cache.
static cache_pc sn_shared_coarse_cache_initial_start_pc; // Initial start pc during creation of shared coarse cache
static cache_pc sn_shared_coarse_cache_initial_end_pc; // Initial end pc during creation of shared coarse cache
static cache_pc sn_shared_coarse_cache_initial_cur_pc; // Initial current pc during creation of shared coarse cache

static cache_pc sn_shared_cache_start_pc; // Stores the start pc of the shared cache
static cache_pc sn_shared_cache_end_pc; // Stores the end pc of the shared cache
static cache_pc sn_shared_cache_cur_pc; // Stores the current pc of the shared cache
static cache_pc sn_shared_cache_prev_end_pc; // Stores the previous end pc of the shared cache.
static cache_pc sn_shared_cache_initial_start_pc; // Initial start pc during creation of the shared cache
static cache_pc sn_shared_cache_initial_end_pc; // Initial end pc during creation of the shared cache
static cache_pc sn_shared_cache_initial_cur_pc; // Initial current pc during creation of the shared cache

static cache_pc sn_private_cache_start_pc; // Stores the start pc of the private trace cache.
static cache_pc sn_private_cache_end_pc; // Stores the end pc of the private trace cache.
static cache_pc sn_private_cache_cur_pc; // Stores the current pc of the private trace cache.
static cache_pc sn_private_cache_prev_end_pc; // Stores the previous end pc of the private trace cache.
static cache_pc sn_private_cache_initial_start_pc; // Initial start pc during creation of the private trace cache.
static cache_pc sn_private_cache_initial_end_pc; // Stores the end pc during creation of the private trace cache.
static cache_pc sn_private_cache_initial_cur_pc; // Stores the current pc during creation of the private trace cache.


static cache_pc sn_cache_start_pc; // Stores cache start pc and would be printed through client.
static cache_pc sn_cache_end_pc; // Stores cache end pc and would be printed through client.
static cache_pc sn_cache_cur_pc; // Stores cache current pc and would be printed through client.


static cache_pc sn_bb_shared_coarse_cache_initial_start_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_shared_coarse_cache_initial_end_pc; // Holds initial end pc of shared_coarse_cache for bb
static cache_pc sn_bb_shared_coarse_cache_initial_cur_pc; // Holds initial cur pc of shared_coarse_cache for bb
static cache_pc sn_bb_shared_cache_initial_start_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_shared_cache_initial_end_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_shared_cache_initial_cur_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_private_cache_initial_start_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_private_cache_initial_end_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_private_cache_initial_cur_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_cache_start_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_cache_end_pc; // Holds initial start pc of shared_coarse_cache for bb
static cache_pc sn_bb_cache_cur_pc; // Holds initial start pc of shared_coarse_cache for bb


// Added by Surya - End

#define SUCCESS 0
#define FAILURE 1

/* macros to make conditional compilation look prettier */
#ifdef DGC_DIAGNOSTICS
# define _IF_DGCDIAG(x) , x
# define IF_DGCDIAG_ELSE(x, y) x
#else
# define _IF_DGCDIAG(x)
# define IF_DGCDIAG_ELSE(x, y) y
#endif

/* make sure defines are consistent */
#ifndef X86
#error Must define X86, no other platforms are supported
#endif

#if defined(PAPI) && defined(WINDOWS)
# error PAPI does not work on WINDOWS
#endif

#if defined(DCONTEXT_IN_EDI) && !defined(STEAL_REGISTER)
# error Must steal register to keep dcontext in edi
#endif

#if defined(SIDELINE_COUNT_STUDY)
# if !defined(PROFILE_LINKCOUNT) || !defined(SIDELINE)
#  error SIDELINE_COUNT_STUDY requires PROFILE_LINKCOUNT and defined(SIDELINE)
# endif
#endif

#ifdef DGC_DIAGNOSTICS
# ifndef PROGRAM_SHEPHERDING
#  error DGC_DIAGNOSTICS requires PROGRAM_SHEPHERDING
# endif
# ifndef DEBUG
#  error DGC_DIAGNOSTICS requires DEBUG
# endif
#endif

#ifndef PROGRAM_SHEPHERDING
# ifdef SIMULATE_ATTACK
#  error SIMULATE_ATTACK requires PROGRAM_SHEPHERDING
# endif
#endif

/* in buildmark.c */
extern const char dynamorio_version_string[];
extern const char dynamorio_buildmark[];

struct _opnd_t;
typedef struct _opnd_t opnd_t;
struct _instr_t;
typedef struct _instr_t instr_t;
struct _instr_list_t;
struct _fragment_t;
typedef struct _fragment_t fragment_t;
struct _future_fragment_t;
typedef struct _future_fragment_t future_fragment_t;
struct _trace_t;
typedef struct _trace_t trace_t;
struct _linkstub_t;
typedef struct _linkstub_t linkstub_t;
struct _dcontext_t;
typedef struct _dcontext_t dcontext_t;
struct vm_area_vector_t;
typedef struct vm_area_vector_t vm_area_vector_t;
struct _coarse_info_t;
typedef struct _coarse_info_t coarse_info_t;
struct _coarse_freeze_info_t;
typedef struct _coarse_freeze_info_t coarse_freeze_info_t;
struct _module_data_t;

//#if SURYA_DCONTEXT2
dcontext_t *dcon_etrans[SN_NUM_ETRANS_THREADS]; // Holds pointers to the dcontext's of eager translation threads.
dcontext_t *dcon_etrans1,*dcon_etrans2; // Added by Surya. Will be used as dcontext for new compiler thread
dcontext_t *dcon_app; // Added by Surya. Will be used as dcontext for app thread
dcontext_t *dcon_global; // Added by Surya. Holds the dcontext rendered by get_thread_private_dcontext() function(both app and compiler thread).
//#endif


/* DR_API EXPORT TOFILE dr_defines.h */
/* DR_API EXPORT BEGIN */
typedef struct _instr_list_t instrlist_t;
typedef struct _module_data_t module_data_t;
/* DR_API EXPORT END */

/* DR_API EXPORT BEGIN */

/**
 * Structure written by dr_get_time() to specify the current time. 
 */
typedef struct {
    uint year;         /**< */
    uint month;        /**< */
    uint day_of_week;  /**< */
    uint day;          /**< */
    uint hour;         /**< */
    uint minute;       /**< */
    uint second;       /**< */
    uint milliseconds; /**< */
} dr_time_t;
/* DR_API EXPORT END */

#if defined(RETURN_AFTER_CALL) || defined(RCT_IND_BRANCH)
struct _rct_module_table_t;
typedef struct _rct_module_table_t rct_module_table_t;

typedef enum { 
    RCT_RAC = 0,
    RCT_RCT,
    RCT_NUM_TYPES,
} rct_type_t;
#endif

typedef struct _thread_record_t {
    thread_id_t id;   /* thread id */
#ifdef WINDOWS
    HANDLE handle;    /* win32 thread handle */
    bool retakeover;
#else
    process_id_t pid; /* thread group id */
    bool execve;      /* exiting due to execve (i#237/PR 498284) */
#endif
    uint num;         /* creation ordinal */
    bool under_dynamo_control; /* used for deciding whether to intercept events */
    dcontext_t *dcontext; /* allows other threads to see this thread's context */
    struct _thread_record_t * next;
} thread_record_t;

/* we don't include dr_api.h, that's for external use, we only need _app
 * (everything in dr_defines.h is duplicated in our own header files)
 */
#ifdef DR_APP_EXPORTS
/* we only export app interface if DR_APP_EXPORTS is defined */
# include "dr_app.h"
/* a few always-exported routines are part of the app interface */
# undef DYNAMORIO_EXPORT
# define DYNAMORIO_EXPORT DR_APP_API
#endif

#ifdef PROFILE_LINKCOUNT
#ifndef LINKCOUNT_64_BITS
typedef uint linkcount_type_t;
#else
typedef uint64 linkcount_type_t;
#endif
#endif

#include "heap.h"
#include "utils.h"
#include "options.h"
#include "os_exports.h"
#include "arch_exports.h"
#include "vmareas.h"
#include "instrlist.h"
#include "dispatch.h"

#include "dr_stats.h"


#ifdef CLIENT_INTERFACE
typedef struct _client_to_do_list_t {
    /* used to make a list of fragments to delete/replace */
    /* deletes frag at tag if ilist is null else replaces it with ilist */
    instrlist_t *ilist;
    app_pc tag;
    struct _client_to_do_list_t *next;
} client_todo_list_t;

/* Clients need a separate list to queue up flush requests from dr_flush() */
typedef struct _client_flush_req_t {
    app_pc start;
    size_t size;
    uint   flush_id; /* client supplied identifier for this flush */
    void (*flush_callback)(int);
    struct _client_flush_req_t *next;
} client_flush_req_t;

/* for -thin_client we don't allocate client_data currently, also client_data could be
 * NULL during thread startup or teardown (i.e. mutex_wait_contended_lock() usage) */
#define IS_CLIENT_THREAD(dcontext) \
    ((dcontext) != NULL && dcontext != GLOBAL_DCONTEXT && \
     (dcontext)->client_data != NULL && \
     (dcontext)->client_data->is_client_thread)

/* Client interface-specific data for dcontexts */
typedef struct _client_data_t {
    /* field for use by user via exported API */
    void *         user_field;
    client_todo_list_t * to_do;
    client_flush_req_t *flush_list;
# ifdef CLIENT_SIDELINE
    mutex_t            sideline_mutex;
# endif
    /* fields for doing release and debug build checks against erroneous API usage */
    module_data_t      *no_delete_mod_data;

    /* Client-owned threads, such as a client nudge thread, require special
     * synchronization support. is_client_thread means that the thread is currently
     * completely owned by the client.  client_thread_safe_for_sync is use to mark
     * client-owned threads that are safe for synch_with_all_threads synchronization but
     * are in dynamo/native code (such as in dr_thread_yield(), dr_sleep(),
     * dr_mutex_lock() and dr_messagebox()).  Note it does not need to be set when
     * the client is in client library code.  For dr_mutex_lock() we set client_grab_mutex
     * to the client mutex that is being locked so that we can set
     * client_thread_safe_for_sync only around the actual wait.
     * FIXME - PR 231301, we may need a way for clients that call ntdll directly to
     * mark client_thread_safe_for_synch for client-owned threads when calling out to
     * ntdll. Especially if they're calling system calls that wait or take a long time
     * to finish etc. Applies to generated code and other libraries called by the client
     * lib as well.
     */
    bool           is_client_thread; /* NOTE - use IS_CLIENT_THREAD() */
    bool           client_thread_safe_for_synch;
    bool           suspendable; /* suspend w/ synchall: PR 609569 */
    bool           left_unsuspended; /* not suspended by synchall: PR 609569 */
    uint           mutex_count; /* mutex nesting: for PR 558463 */
    void           *client_grab_mutex;
# ifdef DEBUG
    bool           is_translating;
# endif

    /* flags for asserts on linux and for getting param base right on windows */
    bool           in_pre_syscall;
    bool           in_post_syscall;
    /* flag for dr_syscall_invoke_another() */
    bool           invoke_another_syscall;
    /* flags for dr_get_mcontext (i#117/PR 395156) */
    bool           mcontext_in_dcontext;
    bool           suspended;
    priv_mcontext_t *cur_mc;
} client_data_t;
#else
# define IS_CLIENT_THREAD(dcontext) false
#endif /* CLIENT_INTERFACE */

#ifdef UNIX
/* i#61/PR 211530: nudges on Linux do not use separate threads */
typedef struct _pending_nudge_t {
    nudge_arg_t arg;
    struct _pending_nudge_t *next;
} pending_nudge_t;
#endif

/* size of each Dynamo thread-private stack */
#define DYNAMORIO_STACK_SIZE dynamo_options.stack_size

/* global flags */
extern bool automatic_startup;   /* ignore start/stop api, run entire program */
extern bool control_all_threads; /* ok for "weird" things to happen -- not all
                                    threads are under our control */
extern bool dynamo_heap_initialized;  /* has dynamo_heap been initialized? */
extern bool dynamo_initialized;  /* has dynamo been initialized? */
extern bool dynamo_exited;       /* has dynamo exited? */
extern bool dynamo_exited_and_cleaned; /* has dynamo component cleanup started? */
#ifdef DEBUG
extern bool dynamo_exited_log_and_stats; /* are stats and logfile shut down? */
#endif
extern bool dynamo_resetting;    /* in middle of global reset? */
extern bool dynamo_all_threads_synched; /* are all other threads suspended safely? */

#if defined(CLIENT_INTERFACE) || defined(STANDALONE_UNIT_TEST)
extern bool standalone_library;  /* used as standalone library */
#else
/* avoid complex ifdefs everywhere */
# define standalone_library false
#endif
#ifdef UNIX
extern bool post_execve;         /* have we performed an execve? */
/* i#237/PR 498284: vfork threads that execve need to be separately delay-freed */
extern int num_execve_threads;
#endif

/* global instance of statistics struct */
extern dr_statistics_t *stats;

/* the process-wide logfile */
extern file_t main_logfile;

/* initial stack so we don't have to use app's */
extern byte *  initstack;
extern mutex_t   initstack_mutex;
extern byte *  initstack_app_xsp;

#if defined(WINDOWS) && defined(STACK_GUARD_PAGE)
/* PR203701: separate stack for error reporting when the dstack is exhausted */
extern byte *  exception_stack;
#endif

/* keeps track of how many threads are in cleanup_and_terminate so that we know
 * if any threads could still be using shared resources even if they aren't on
 * the all_threads list */
extern int exiting_thread_count;

/* Called before a second thread is ever scheduled. */
void pre_second_thread(void);

bool is_on_initstack(byte *esp);

bool is_on_dstack(dcontext_t *dcontext, byte *esp);
bool is_currently_on_dstack(dcontext_t *dcontext);

#ifdef WINDOWS
extern bool    dr_early_injected;
extern int     dr_early_injected_location;
extern bool    dr_earliest_injected;
extern bool    dr_injected_primary_thread;
extern bool    dr_injected_secondary_thread;
extern bool    dr_late_injected_primary_thread;

#endif
#ifdef RETURN_AFTER_CALL
extern bool    dr_preinjected;
#endif
#ifdef DR_APP_EXPORTS
/* flags to indicate when DR is being initialized / exited using the API */
extern bool    dr_api_entry;
extern bool    dr_api_exit;
#endif

/* in dynamo.c */
/* 9-bit addressed hash table takes up 2K, has capacity of 512
 * we never resize, assuming won't be seeing more than a few hundred threads
 */
#define ALL_THREADS_HASH_BITS 9
extern thread_record_t **all_threads;
extern mutex_t all_threads_lock;
DYNAMORIO_EXPORT int dynamorio_app_init(void);
int dynamorio_app_exit(void);
#if defined(CLIENT_INTERFACE) || defined(STANDALONE_UNIT_TEST)
dcontext_t * standalone_init(void);
void standalone_exit(void);
#endif
thread_record_t * thread_lookup(thread_id_t tid);
void add_thread(IF_WINDOWS_ELSE_NP(HANDLE hthread, process_id_t pid),
                thread_id_t tid, bool under_dynamo_control, dcontext_t *dcontext);
bool remove_thread(IF_WINDOWS_(HANDLE hthread) thread_id_t tid);
uint get_thread_num(thread_id_t tid);
int get_num_threads(void);
bool is_last_app_thread(void);
void get_list_of_threads(thread_record_t ***list, int *num);
bool is_thread_known(thread_id_t tid);
#ifdef UNIX
void get_list_of_threads_ex(thread_record_t ***list, int *num, bool include_execve);
void mark_thread_execve(thread_record_t *tr, bool execve);
#endif
bool is_thread_initialized(void);
int dynamo_thread_init(byte *dstack_in, priv_mcontext_t *mc
                       _IF_CLIENT_INTERFACE(bool client_thread));
int dynamo_thread_exit(void);
void dynamo_thread_stack_free_and_exit(byte *stack);
int dynamo_other_thread_exit(thread_record_t *tr
                             _IF_WINDOWS(bool detach_stacked_callbacks));
void dynamo_thread_under_dynamo(dcontext_t *dcontext);
void dynamo_thread_not_under_dynamo(dcontext_t *dcontext);
/* used for synch to prevent thread creation/deletion in critical periods */
extern mutex_t thread_initexit_lock;
dcontext_t * create_new_dynamo_context(bool initial, byte *dstack_in);
void initialize_dynamo_context(dcontext_t *dcontext);
dcontext_t * create_callback_dcontext(dcontext_t *old_dcontext);
int dynamo_nullcalls_exit(void);
int dynamo_process_exit(void);
#ifdef UNIX
void dynamorio_fork_init(dcontext_t *dcontext);
#endif
void dynamorio_take_over_threads(dcontext_t *dcontext);
dr_statistics_t * get_dr_stats(void);

/* functions needed by detach */
int dynamo_shared_exit(IF_WINDOWS_(thread_record_t *toexit)
                       IF_WINDOWS_ELSE_NP(bool detach_stacked_callbacks, void));
/* perform exit tasks that require full thread data structs */
void dynamo_process_exit_with_thread_info(void);
/* thread cleanup prior to clean exit event */
void dynamo_thread_exit_pre_client(dcontext_t *dcontext, thread_id_t id);

/* enter/exit DR hooks */
void entering_dynamorio(void);
void exiting_dynamorio(void);

void handle_system_call(dcontext_t *dcontext);

/* self-protection */
void protect_data_section(uint sec, bool writable);
#ifdef DEBUG
const char *get_data_section_name(app_pc pc);
bool check_should_be_protected(uint sec);
# ifdef WINDOWS
bool data_sections_enclose_region(app_pc start, app_pc end);
# endif
#endif /* DEBUG */

/* all the locks used to protect shared data structures during multi-operation
 * sequences, exported so that micro-operations can assert that one is held 
 */
extern mutex_t bb_building_lock;
extern volatile bool bb_lock_start;
extern recursive_lock_t change_linking_lock;

/* where the current app thread's control is */
typedef enum {
    WHERE_APP=0, 
    WHERE_INTERP,
    WHERE_DISPATCH,
    WHERE_MONITOR,
    WHERE_SYSCALL_HANDLER,
    WHERE_SIGNAL_HANDLER,
    WHERE_TRAMPOLINE,
    WHERE_CONTEXT_SWITCH,
    WHERE_IBL,
    WHERE_FCACHE,
    WHERE_UNKNOWN,
#ifdef HOT_PATCHING_INTERFACE
    WHERE_HOTPATCH,
#endif
    WHERE_LAST
} where_am_i_t;

/* make args easier to read for protection change calls 
 * since only two possibilities not using new type
 */
enum {
    READONLY=false, 
    WRITABLE=true
};

/* Values for unprotected_context_t.exit_reason, stored in a ushort. */
enum {
    /* Default.  All other reasons must clear after setting. */
    EXIT_REASON_SELFMOD = 0,
    /* Floating-point state PC needs updating (i#698). */
    EXIT_REASON_FLOAT_PC_FNSAVE,
    EXIT_REASON_FLOAT_PC_FXSAVE,
    EXIT_REASON_FLOAT_PC_FXSAVE64,
    EXIT_REASON_FLOAT_PC_XSAVE,
    EXIT_REASON_FLOAT_PC_XSAVE64,
};

/* Number of nested calls into native modules that we support.  This number
 * needs to equal the number of stubs in x86.asm:back_from_native_retstubs,
 * which is checked at startup in native_exec.c.
 * FIXME: Remove this limitation if we ever need to support true mutual
 * recursion between native and non-native modules.
 */
enum { MAX_NATIVE_RETSTACK = 10 };

typedef struct _retaddr_and_retloc_t {
    app_pc retaddr;
    app_pc retloc;
} retaddr_and_retloc_t;

/* To handle TRY/EXCEPT/FINALLY setjmp */
typedef struct try_except_context_t {
    /* FIXME: we are using a local dr_jmp_buf which is relatively
     * small so minimal risk of dstack pressure.  Alternatively, we
     * can disallow nesting and have a single buffer per dcontext.
     */
    /* N.B.: offsetof(try_except_context_t, context) is hardcoded in x86.asm */
    dr_jmp_buf_t context;

    struct try_except_context_t *prev_context;
} try_except_context_t;

/* We do support TRY pre-dynamo_initialized via this global struct.
 * This, along with safe_read pc ranges, satisfies most TRY uses that
 * don't have a dcontext (i#350).
 */
typedef struct _try_except_t {
    try_except_context_t *try_except_state; /* for TRY/EXCEPT/FINALLY */
    bool unwinding_exception;   /* NYI support for TRY/FINALLY - 
                                 * marks exception until an EXCEPT handles */
} try_except_t;

extern try_except_t global_try_except;

typedef struct {
    /* WARNING: if you change the offsets of any of these fields, 
     * you must also change the offsets in <arch>/<arch.s> 
     */
    priv_mcontext_t mcontext;        /* real machine context (in arch_exports.h) */
#ifdef UNIX
    int            errno;           /* errno used for DR (no longer used for app) */
#endif
    bool at_syscall;                /* for shared deletion syscalls_synch_flush,
                                     * as well as syscalls handled from dispatch,
                                     * and for reset to identify when at syscalls
                                     */
    ushort exit_reason;             /* Allows multiplexing LINK_SPECIAL_EXIT */
    /* Above fields are padded to 8 bytes on all archs except Win x86-32. */

#ifdef CLIENT_INTERFACE
    /* Spill slots for inlined clean calls. */
    reg_t inline_spill_slots[CLEANCALL_NUM_INLINE_SLOTS];
#endif
} unprotected_context_t;

/* dynamo-specific context associated with each active app thread 
 * N.B.: make sure to update these routines as necessary if
 * you add or remove fields:
 *   create_new_dynamo_context
 *   create_callback_dcontext
 *   initialize_dynamo_context
 *   swap_dcontexts
 * if you add any pointers to data structures, make sure callback_setup()
 *   clears them to prevent stale pointers on callback return
 */
struct _dcontext_t {
    /* NOTE: For any field to survive across callback stack switches it must either
     * be indirected through a modular field or explicitly copied in
     * create_callback_dcontext() (like the modular fields are).
     */

    /* WARNING: if you change the offsets of any of these fields, up through
     * ignore_enterexit, you must also change the offsets in <arch>/<arch.s> 
     */

    /* if SELFPROT_DCONTEXT, must split dcontext into unprotected and
     * protected fields depending on whether they must be read-only
     * when in the code cache.
     * we waste sizeof(unprotected_context_t) bytes to provide runtime flexibility:
     */
    union {
        /* we use separate_upcontext if 
         *    (TEST(SELFPROT_DCONTEXT, dynamo_options.protect_mask))
         * else we use the inlined upcontext
         */
        unprotected_context_t *separate_upcontext;
        unprotected_context_t upcontext;
    } upcontext;
    /* HACK for x86.asm lack of runtime param access: this is either
     * a self-ptr (to inlined upcontext) or if we separate upcontext it points there.
     */
    unprotected_context_t *upcontext_ptr;
    
    /* The next application pc to execute.
     * Also used to store the cache pc to execute when entering the code cache,
     * and set to the sentinel value BACK_TO_NATIVE_AFTER_SYSCALL for native_exec.
     * FIXME: change to a union?
     */
    app_pc         next_tag;

    linkstub_t *     last_exit;       /* last exit from cache */
    byte *         dstack;          /* thread-private dynamo stack */

    bool           is_exiting;      /* flag for exiting thread */
#ifdef WINDOWS
# ifdef CLIENT_INTERFACE
    /* i#249: TEB field isolation */
    int            app_errno;
    void *         app_fls_data;
    void *         priv_fls_data;
    void *         app_nt_rpc;
    void *         priv_nt_rpc;
    void *         app_nls_cache;
    void *         priv_nls_cache;
#  ifdef X64
    void *         app_stack_limit;
#  endif
    /* we need this to restore ptrs for other threads on detach */
    byte *         teb_base;
# endif
    /* storage for an extra app value around sysenter system calls for the
     * case 5441 Sygate interoperability hack */
    /* FIXME - this needs to be moved into the upcontext as is written to
     * in cache by ignore/shared_syscall, ramifications? */
    app_pc         sysenter_storage;

    /* used to avoid enter/exit hooks for certain system calls (see case 4942) */
    bool           ignore_enterexit;
#endif

    /* Coarse-grain cache exits require extra state storage as they do not
     * use per-exit separate data structures
     */
    union {
        /* Indirect branches store on exit the source tag (with the type of
         * branch coming from fake linkstubs), while direct store the source unit
         */
        app_pc src_tag;
        coarse_info_t *dir_exit;
    } coarse_exit;

    /************* end of offset-crucial fields *********************/

    /* FIXME: now that we initialize a new thread's dcontext right away, and
     * a new callback's as well, we should be able to get rid of this
     */
    bool           initialized;     /* has this context been used yet? */
    thread_id_t      owning_thread;
#ifdef UNIX
    process_id_t     owning_process; /* handle shared address space w/o shared pid */
#endif
    thread_record_t   *thread_record;  /* so don't have to do a thread_lookup */
    where_am_i_t       whereami;        /* where control is at the moment */
    void *         allocated_start; /* used for cache alignment */
    fragment_t *     last_fragment;   /* cached value of linkstub_fragment(last_exit) */

    int            sys_num;         /* used for post_system_call */
#ifdef WINDOWS
    reg_t *        sys_param_base;  /* used for post_system_call */
#endif
#if defined(UNIX) || defined(X64)
    reg_t          sys_param0;      /* used for post_system_call */
    reg_t          sys_param1;      /* used for post_system_call */
    reg_t          sys_param2;      /* used for post_system_call */
    reg_t          sys_param3;      /* used for post_system_call */
#endif
#ifdef UNIX
    reg_t          sys_param4;      /* used for post_system_call i#173 */
    bool           sys_was_int;     /* was the last system call via do_int_syscall? */
    bool           sys_xbp;         /* PR 313715: store orig xbp */
# ifdef DEBUG
    bool           mprot_multi_areas; /* PR 410921: mprotect of 2 or more vmareas? */
# endif
#endif

#ifdef X64
    /* Is this thread in 32-bit (x86) or 64-bit (x64) mode?
     * Default is to decode as base platform, but we want runtime ability to
     * decode/encode 32-bit from 64-bit dynamorio.dll (we don't support the
     * other way around: PR 236203).
     */
    bool           x86_mode;
#endif

    /* to make things more modular these are void*: */
    void *         link_field;
    void *         monitor_field;
    void *         fcache_field;
    void *         fragment_field;
    void *         heap_field;
    void *         vm_areas_field;
    void *         os_field;
    void *         synch_field;
#ifdef UNIX
    void *         signal_field;
    void *         pcprofile_field;
    bool           signals_pending;
#endif
    void *         private_code;          /* various thread-private routines */

#ifdef TRACE_HEAD_CACHE_INCR
    cache_pc       trace_head_pc; /* HACK to jmp to trace head w/o a prefix */
#endif

#ifdef WINDOWS
    /* these fields used for "stack" of contexts for callbacks */
# ifdef DCONTEXT_IN_EDI
    dcontext_t *next_saved;
# endif
    dcontext_t *prev_unused;
    /* need to be able to tell which dcontexts in callback stack are valid */
    bool           valid;
    /* special slot used to deal with callback returns, where we want to
     * restore state of prior guy on callback stack, yet need current state
     * to restore native state prior to callback return interrupt/syscall.
     * Also used as temp next_tag slot for fcache_enter_indirect and cb ret.
     */
    reg_t          nonswapped_scratch;
#endif

    /* next_tag holds the do_syscall entry point, so we need another
     * slot to hold asynch targets for APCs to know next target and
     * for NtContinue and sigreturn to set next target
     */
    app_pc         asynch_target;

    /* must store post-intercepted-syscall target to allow using normal
     * dispatch() for native_exec syscalls
     */
    app_pc         native_exec_postsyscall;

    /* Stack of app return addresses and stack locations of callsites where we
     * called into a native module.
     */
    retaddr_and_retloc_t native_retstack[MAX_NATIVE_RETSTACK];
    uint native_retstack_cur;

#ifdef PROGRAM_SHEPHERDING
    bool           alloc_no_reserve; /* to implement executable_if_alloc policy */
#endif

#ifdef CUSTOM_TRACES_RET_REMOVAL
    int num_calls;
    int num_rets;
    int call_depth;
#endif

#ifdef CHECK_RETURNS_SSE2
    int            call_depth;
    void *         call_stack;
#endif

#ifdef DEBUG
    file_t                        logfile;
    thread_local_statistics_t *     thread_stats;
    bool                        expect_last_syscall_to_fail;
    /* HACK to avoid recursion on pclookup for target invoking disassembly
     * during decode_fragment() for a coarse target
     */
    bool                        in_opnd_disassemble;
#endif /* DEBUG */
#ifdef DEADLOCK_AVOIDANCE
    thread_locks_t *               thread_owned_locks;
#endif
#ifdef KSTATS
    thread_kstats_t *              thread_kstats;
#endif

#ifdef PROFILE_RDTSC
    uint64         cache_enter_time;
    uint64         start_time;     /* records start time for profiling */
    fragment_t *     prev_fragment;
    /* top ten times spent in cache */
    uint64         cache_frag_count; /* num frag execs in single cache period */
    uint64         cache_time[10];   /* top ten times spent in cache */
    uint64         cache_count[10];  /* top ten cache_frag_counts */
#endif

#ifdef CLIENT_INTERFACE
    /* client interface-specific data */
    client_data_t *client_data;
#endif

    /* FIXME trace_sysenter_exit is used to capture an exit from a trace that
     * ends in a SYSENTER and to enable trace head marking. So it's really a
     * monitor-centric variable. It's placed in the context for now so that
     * it's not shared across contexts (as the monitor data is). Cross-context
     * sharing of this field could cause inadvertent trace head marking,
     * for example, during a callback. A longer-term fix may be to move it to
     * a context-private non-shared monitor struct.
     */
    bool           trace_sysenter_exit;

    /* DR sets this field to indicate that it's forging an exception that
     * may appear to originate in DR but should be passed on to the app. */
    app_pc         forged_exception_addr;
#ifdef HOT_PATCHING_INTERFACE
    /* Fix for case 5367. */
    bool           nudge_thread;    /* True only if this is a nudge thread. */
    dr_jmp_buf_t   hotp_excpt_state;    /* To handle hot patch exceptions. */
#endif
    try_except_t   try_except; /* for TRY/EXCEPT/FINALLY */
    
#ifdef WINDOWS                    
    /* for ASLR_SHARED_CONTENT, note per callback, not per thread to
     * track properties of a syscall or a syscall pair.  Even we don't
     * expect to get APCs or callbacks while processing normal DLLs
     * this should be per dcontext.
     */
    aslr_syscall_context_t aslr_context;

    /* Initially memset to 0 in create dcontext.  If this is a nudge (or
     * internal detach) thread (as detected by start address in intercept_apc),
     * nudge_target is set to the corresponding nudge routine (currently always
     * generic_nudge_target).  We can then check this
     * value in those routines after we come out of the cache as a security
     * measure (xref case 552).  This gives us some protection against an
     * attacker leveraging our own detach routines and the like.  FIXME - if
     * the attacker is able to specify the start address for a newly created
     * thread then they can fake this. */
    void           *nudge_target;

    /* If free_app_stack is set, we free the application stack during thread exit
     * cleanup.  Used for nudge threads. */
    bool           free_app_stack;

    /* used when a nudge invokes dr_exit_process() */
    bool           nudge_terminate_process;
    uint           nudge_exit_code;
#endif /* WINDOWS */

    /* we keep an absolute address pointer to our tls state so that we
     * can access it from other threads
     */
    local_state_t *local_state;

#ifdef WINDOWS
    /* case 8721: saving the win32 start address so we can print it in the
     * ldmp.  An alternative solution is to call NtQueryInformationThread
     * with ThreadQuerySetWin32StartAddress at dump time.  According to 
     * Nebbet, however, a thread calling ZwReplyWaitReplyPort or 
     * ZwReplyWaitRecievePort will clobber the start address.
     */
    app_pc win32_start_addr;
#endif

    /* Used to abort bb building on decode faults.  Not persistent across cache. */
    void *bb_build_info;

    /* PK: is this a dedicated eager compiler thread */
  //bool is_eager_compiler_thread;

#ifdef UNIX
    pending_nudge_t *nudge_pending;
    /* frag we unlinked to expedite nudge delivery */
    fragment_t *interrupted_for_nudge;
# ifdef DEBUG
    /* i#238/PR 499179: check that libc errno hasn't changed */
    int libc_errno;
# endif
#else
# ifdef DEBUG
    bool post_syscall;
# endif
#endif
};

/* sentinel value for dcontext_t* used to indicate
 * "global rather than a particular thread" 
 */
#define GLOBAL_DCONTEXT  ((dcontext_t *)PTR_UINT_MINUS_1)

/* FIXME: why do we need to force the inline for this simple function? */
static INLINE_FORCED priv_mcontext_t *
get_mcontext(dcontext_t *dcontext)
{
    if (TEST(SELFPROT_DCONTEXT, dynamo_options.protect_mask))
        return &(dcontext->upcontext.separate_upcontext->mcontext);
    else
        return &(dcontext->upcontext.upcontext.mcontext);
}

/* A number of routines (dump_mbi*, dump_mcontext, dump_callstack, 
 * print_modules) have an argument on whether to dump in an xml friendly format
 * (for xml diagnostics files). We use these defines for readability. */
enum {
    DUMP_XML=true,
    DUMP_NOT_XML=false
};

/* io.c */
/* to avoid transparency problems we must have our own vnsprintf and sscanf */
#include <stdarg.h> /* for va_list */
int our_snprintf(char *s, size_t max, const char *fmt, ...);
int our_vsnprintf(char *s, size_t max, const char *fmt, va_list ap);
int our_snprintf_wide(wchar_t *s, size_t max, const wchar_t *fmt, ...);
int our_vsnprintf_wide(wchar_t *s, size_t max, const wchar_t *fmt, va_list ap);
#undef snprintf /* defined on macos */
#define snprintf our_snprintf
#undef _snprintf
#define _snprintf our_snprintf
#undef vsnprintf
#define vsnprintf our_vsnprintf
#define snwprintf  our_snprintf_wide
#define _snwprintf our_snprintf_wide
int our_sscanf(const char *str, const char *format, ...);
int our_vsscanf(const char *str, const char *fmt, va_list ap);
const char * parse_int(const char *sp, uint64 *res_out, uint base, uint width,
                       bool is_signed);
ssize_t
utf16_to_utf8_size(const wchar_t *src, size_t max_chars, size_t *written/*unicode chars*/);
#define sscanf our_sscanf

/* string.c */
int tolower(int c);

/* Code cleanliness rules */
#ifdef WINDOWS
#  define strcasecmp _stricmp
#  define strncasecmp _strnicmp
#  define wcscasecmp _wcsicmp
#endif

#if !defined(NOT_DYNAMORIO_CORE_PROPER) && !defined(NOT_DYNAMORIO_CORE)
#  define printf   printf_forbidden_function
#  undef sprintf /* defined on macos */
#  define sprintf  sprintf_forbidden_function
#  define swprintf swprintf_forbidden_function
#  undef vsprintf /* defined on macos */
#  define vsprintf vsprintf_forbidden_function
#  define __try    __try_forbidden_construct /* see case 4461 */

/* libc independence */
#  define mprotect     mprotect_forbidden_function
#  define mmap         mmap_forbidden_function
#  define munmap       munmap_forbidden_function
#  define getppid      getppid_forbidden_function
#  define sched_yield  sched_yield_forbidden_function
#  define dup          dup_forbidden_function
#  define sigaltstack  sigaltstack_forbidden_function
#  define setitimer    setitimer_forbidden_function
#  define _exit        _exit_forbidden_function
//#  define gettimeofday gettimeofday_forbidden_function // Commented out by Surya to allow the usage of the time() function
//#  define time         time_forbidden_function // Commented out by Surya to allow the usage of the time() function
#  define modify_ldt   modify_ldt_forbidden_function
#endif

#endif /* _GLOBALS_H_ */
