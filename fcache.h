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

/*
 * fcache.h - fcache exports
 */

#ifndef _FCACHE_H_
#define _FCACHE_H_ 1

/* who's in the "trace" cache? 
 * when we have private traces we put temp-private bbs there (to avoid
 * perf hit in speccpu of having separate priv bb cache that's not
 * normally used)
 */
#define IN_TRACE_CACHE(flags) \
    (TEST(FRAG_IS_TRACE, (flags)) || \
     (!DYNAMO_OPTION(shared_traces) && TEST(FRAG_TEMP_PRIVATE, (flags))))

/* Case 8647: we don't need to pad jmps for coarse-grain bbs */
#define PAD_FRAGMENT_JMPS(flags) \
    (TEST(FRAG_COARSE_GRAIN, (flags)) ? false : DYNAMO_OPTION(pad_jmps))

#define PAD_JMPS_SHIFT_START(flags) \
    (PAD_FRAGMENT_JMPS(flags) ? \
     (TEST(FRAG_IS_TRACE, (flags)) ? INTERNAL_OPTION(pad_jmps_shift_trace) : \
      INTERNAL_OPTION(pad_jmps_shift_bb)) : false)

/* control over what to reset */
enum {
    /* everything, separate since more than sum of others */
    RESET_ALL              = 0x001,
    /* NYI (case 6335): just bb caches + heap */
    RESET_BASIC_BLOCKS     = 0x002,
    /* NYI (case 6335): just trace caches + heap */
    RESET_TRACES           = 0x004,
    /* just pending deletion entries (-reset_every_nth_pending)
     * TODO OPTIMIZATION (case 7147): we could avoid suspending
     * everyone and only suspend those threads w/ low flushtimes.
     */
    RESET_PENDING_DELETION = 0x008,
};

/* protects all reset triggers: reset_pending and reset_at_nth_thread_triggered 
 * resets are not queued up -- one wins and the rest are canceled
 */
extern mutex_t reset_pending_lock;
/* indicates a call to fcache_reset_all_caches_proactively() is pending from dispatch */
extern uint reset_pending;

void fcache_init(void);
void fcache_exit(void);

bool fcache_check_option_compatibility(void);

#if defined(WINDOWS_PC_SAMPLE) && !defined(DEBUG)
/* for fast exit path */
void fcache_profile_exit(void);
#endif

#ifdef DEBUG
void fcache_stats_exit(void);
#endif

bool in_fcache(void *pc);

void fcache_thread_init(dcontext_t *dcontext);
#ifdef DEBUG
void fcache_thread_exit_stats(dcontext_t *dcontext);
#endif
void fcache_thread_exit(dcontext_t *dcontext);

void fcache_add_fragment(dcontext_t *dcontext, fragment_t *f);
void fcache_shift_start_pc(dcontext_t *dcontext, fragment_t *f, uint space);
void fcache_return_extra_space(dcontext_t *dcontext, fragment_t *f, size_t space);
void fcache_remove_fragment(dcontext_t *dcontext, fragment_t *f);

bool fcache_is_flush_pending(dcontext_t *dcontext);
bool fcache_flush_pending_units(dcontext_t *dcontext, fragment_t *was_I_flushed);
void fcache_free_pending_units(dcontext_t *dcontext, uint flushtime);
void fcache_flush_all_caches(void);

void fcache_reset_all_caches_proactively(uint target);
bool schedule_reset(uint target);

void fcache_low_on_memory(void);

/* macros to put mask check outside of function, for efficiency */
/* when NULL is passed for f then the entire fcache will be affected */
#define SELF_PROTECT_CACHE(dc, f, w) do {                    \
    if (TEST(SELFPROT_CACHE, dynamo_options.protect_mask) && \
        ((f) == NULL || (fcache_is_writable(f) != (w))))     \
        fcache_change_fragment_protection(dc, f, w);         \
} while (0);

bool fcache_is_writable(fragment_t *f);
void fcache_change_fragment_protection(dcontext_t *dcontext,
                                       fragment_t *f, bool writable);

#ifdef SIDELINE
dcontext_t * get_dcontext_for_fragment(fragment_t *f);
#endif

/* for adaptive working set */
bool fragment_lookup_deleted(dcontext_t *dcontext, app_pc tag);

/* Returns the fragment_t whose body (not cache slot) contains lookup_pc */  
fragment_t *
fcache_fragment_pclookup(dcontext_t *dcontext, cache_pc lookup_pc, fragment_t *wrapper);

void
fcache_coarse_cache_delete(dcontext_t *dcontext, coarse_info_t *info);

/* Returns the coarse info for the cache unit containing pc; if that unit
 * is not coarse, returns NULL.
 */
coarse_info_t *
get_fcache_coarse_info(cache_pc pc);

/* Returns the total size needed for the cache if info is frozen. */
size_t
coarse_frozen_cache_size(dcontext_t *dcontext, coarse_info_t *info);

void
fcache_coarse_init_frozen(dcontext_t *dcontext, coarse_info_t *info,
                          cache_pc start_pc, size_t size);

void
fcache_coarse_set_info(dcontext_t *dcontext, coarse_info_t *info);

// Added by Surya - Start

DR_API
const char* get_cache_name(); // Get the name of the cache into which the last trace was inserted into. 

DR_API
cache_pc get_initial_shared_coarse_cache_start_pc(); // Return the initial start pc of shared coarse cache.

DR_API 
cache_pc get_initial_shared_coarse_cache_end_pc(); // Return the initial end pc of shared coarse cache.

DR_API
cache_pc get_initial_shared_coarse_cache_cur_pc(); // Return the initial current pc of shared coarse cache.

DR_API
cache_pc get_initial_shared_cache_start_pc(); // Return the initial start pc of shared cache.

DR_API
cache_pc get_initial_shared_cache_end_pc(); // Return the initial end pc of shared cache.

DR_API
cache_pc get_initial_shared_cache_cur_pc(); // Return the initial current pc of shared cache.

DR_API
cache_pc get_initial_private_cache_start_pc(); // Return the initial start pc of private cache.

DR_API
cache_pc get_initial_private_cache_end_pc(); // Return the initial end pc of private cache.

DR_API
cache_pc get_initial_private_cache_cur_pc(); // Return the initial current pc of private cache.

DR_API
cache_pc get_last_trace_cache_start_pc(); // Return the start pc of the cache into which the last tarec has been emitted.
 
DR_API
cache_pc get_last_trace_cache_end_pc(); // Return the start pc of the cache into which the last trace has been emitted.

DR_API
cache_pc get_last_trace_cache_cur_pc(); // Return the start pc of the cache into which the last trace has been emitted. 

DR_API
int is_last_trace_cache_resized(); // Returns integer value corresponding to the trace cache resized. This is the cache into which the last trace has been emitted.Returns value 0 for no resize, 1 for shared coarse cache,2 for shared cache, 3 for private cache.

DR_API
cache_pc get_shared_coarse_cache_prev_end_pc(); // Return the previous end pc for shared coarse cache before resize

DR_API
cache_pc get_shared_cache_prev_end_pc(); // Return the previous end pc for shared cache before resize

DR_API
cache_pc get_private_cache_prev_end_pc(); // Return the previous end pc for private cache before resize

DR_API
void set_cache_variables_to_defaults(); // Set all cache variables to 0 as initial values

/*DR_API
void reset_shared_coarse_cache_resize_flag(); // Reset the flag(set to 0) "shared_coarse_cache_resize"

DRA_API
void reset_shared_cache_resize_flag(); // Reset the flag(set to 0) "shared_cache_resize"

DRA_API
void reset_private_cache_resize_flag(); // Reset the flag(set to 0) "private_cache_resize"
*/

// Added by Surya - Start

DR_API
const char* get_bb_cache_name(); // Get the name of the cache into which the last trace was inserted into. 

DR_API
cache_pc get_initial_bb_shared_coarse_cache_start_pc(); // Return the initial start pc of shared coarse cache.

DR_API 
cache_pc get_initial_bb_shared_coarse_cache_end_pc(); // Return the initial end pc of shared coarse cache.

DR_API
cache_pc get_initial_bb_shared_coarse_cache_cur_pc(); // Return the initial current pc of shared coarse cache.

DR_API
cache_pc get_initial_bb_shared_cache_start_pc(); // Return the initial start pc of shared cache.

DR_API
cache_pc get_initial_bb_shared_cache_end_pc(); // Return the initial end pc of shared cache.

DR_API
cache_pc get_initial_bb_shared_cache_cur_pc(); // Return the initial current pc of shared cache.

DR_API
cache_pc get_initial_bb_private_cache_start_pc(); // Return the initial start pc of private cache.

DR_API
cache_pc get_initial_bb_private_cache_end_pc(); // Return the initial end pc of private cache.

DR_API
cache_pc get_initial_bb_private_cache_cur_pc(); // Return the initial current pc of private cache.

DR_API
cache_pc get_last_bb_cache_start_pc(); // Return the start pc of the cache into which the last tarec has been emitted.
 
DR_API
cache_pc get_last_bb_cache_end_pc(); // Return the start pc of the cache into which the last trace has been emitted.

DR_API
cache_pc get_last_bb_cache_cur_pc(); // Return the start pc of the cache into which the last trace has been emitted. 




// Added by Surya - End

#endif /* _FCACHE_H_ */
