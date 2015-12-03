/************************************************************************************************************************
 *  File Name     : etrans.h                                                                                            *
 *  Author        : Surya Tej Nimmakayala                                                                               *
 *  Creation Date : 04/18/2013                                                                                          * 
 *  Description   : This file contains the definitions of the structure jaddr_etrans_list used in the eager translation.*
 *                  Declaration of the pointer to first entry of the list: root                                         *
 *                  Declaration of the functions set_etrans_list_root and get_etrans_list_root that would be used in    * 
 *                  eager translation.                                                                                  *
 ***********************************************************************************************************************/

#include <stdlib.h>
#include "globals.h"
#include "globals_shared.h"

#define JADDR_STACK_DEBUG 0

// Structure of entry in the linked list holding the jump addresses
struct jaddr_etrans_list{
  app_pc jaddr; // Holds the jump address
  struct jaddr_etrans_list *next; // Pointer to next entry
};

// Structure to hold the root,head,tail of a linked list

struct jaddr_list_attr{
  struct jaddr_etrans_list *stk_top;
  struct jaddr_etrans_list *stk_bottom;
  int stk_cnt;
};


/* struct jaddr_etrans_list *root; // Pointer to first entry in the linked list */
/* struct jaddr_etrans_list *tail; // Pointer to last entry in the linked list */
/* struct jaddr_etrans_list *head; // Pointer to current entry that is to be processed next in the linked list during eager translation */
/* //struct jaddr_etrans_list *curr_list; // Pointer to next entry */
/* int l_entry_cnt; */

/* struct jaddr_etrans_list *root_etrans_list; */
/* struct jaddr_etrans_list *tail_etrans_list; */
/* struct jaddr_etrans_list *head_etrans_list; */
/* int l_etrans_entry_cnt; */

struct jaddr_list_attr *etrans_list;

//struct _instr_list_t **bb_etran_list; // To hold the instruction list of the basic block created

void push_bb_etrans_jaddr_on_top(struct jaddr_list_attr *list,app_pc new_jaddr); // Declaration of the function that adds new jump address at stack top.
void push_bb_etrans_jaddr_at_bottom(struct jaddr_list_attr *list,app_pc new_jaddr); // Declaration of the function that adds new jump address at bottom of the stack.
//void pop_bb_etrans_jaddr_from_top(struct jaddr_list_attr *list); // Declaration of the function that adds new jump address to the given list of jump addresses.
struct jaddr_etrans_list* get_jaddr_stack_top(struct jaddr_list_attr *list);  // Declaration of the function that gets or retrieves top of the stack.
//struct jaddr_etrans_list* get_jaddr_stack_bottom(struct jaddr_list_attr *list); // Declaration of the function to return the stack "bottom" pointer.
//void set_jaddr_list_head(struct jaddr_list_attr *list,struct jaddr_etrans_list *t_head); // Declaration of function to set the "curr" pointer in the given list.

int get_list_entry_count(struct jaddr_list_attr *list); // Declaration of function to get the number of entries in the given stack.
/* void append_p_req_to_etrans_list(struct jaddr_list_attr *list_etrans,struct jaddr_list_attr *list_preq); // Function to append the list of jaddrs created with the parent request to the etrans list. */
/* void reset_preq_list(void); // Function to reset the root,head,tail of the jaddr list populated while serving the parent request. */
void initialize_etrans_list(); // Function to allocate memory for etrans_list.

app_pc get_jaddr_stack_top_addr(struct jaddr_list_attr *list); // Function to fetch the addr from the stack top.

void decrement_stack_entry_cnt(struct jaddr_list_attr *list); // Function to reduce the count of the stack entries by 1.

void clear_jaddr_stack(struct jaddr_list_attr *list); // Function to clear the entries of the stack.
struct jaddr_etrans_list* pop_bb_etrans_jaddr_from_top(struct jaddr_list_attr *list); // Function to pop the stack top, precisely the entry with value 1 in the app thread.





