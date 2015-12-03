/*********************************************************************************************************************
 *  File Name     : etrans.c                                                                                         *
 *  Author        : Surya Tej Nimmakayala                                                                            *
 *  Creation Date : 04/18/2013                                                                                       * 
 *  Description   : This file contains the definitions of the functions that would be used in the eager translation. *
 *                  These functions basically manipulate the pointer to the root of the linked list which holds the  *
 *                  jump addresses of type "struct jaddr_etrans_list" typedef to "jaddr_etrans_list"                 *
 *                  (defined in core/globals.h)   
 ********************************************************************************************************************/


#include "etrans.h"
#include "./x86/instrument.h"

// Returns the top of the jaddr stack(list). As the pointer to stack top is modified as well, it is equivalent to pop operation, so the stk_cnt member of the etrans_list structure should be decremented.

struct jaddr_etrans_list* get_jaddr_stack_top(struct jaddr_list_attr *list){
  struct jaddr_etrans_list *temp_jlist;

  if((list->stk_top != NULL) && ((list->stk_top->jaddr == (app_pc)0)||(list->stk_top->jaddr == (app_pc)1))){ // 
    return list->stk_top;
  }
  
  
  if(list->stk_top != NULL){
    temp_jlist=list->stk_top; // Store top in temp
    (list->stk_cnt)-=1; // Decrement the stack entry count.
#if JADDR_STACK_DEBUG
    dr_fprintf(STDOUT,"\nget_jaddr_stack_top: Decremented list->stk_cnt to %d\n",list->stk_cnt);
#endif
    if((list->stk_cnt == 0) && (list->stk_top->next == NULL)){
      list->stk_top=NULL; // Set stack top to NULL as no more entries in the list.
      list->stk_bottom=NULL; // Set bottom to NULL as well as list is empty.
#if JADDR_STACK_DEBUG
      dr_fprintf(STDOUT,"\nget_jaddr_stack_top: No more entries in the stack. top and bottom set to NULL.\n");
#endif
    }
    else{
      list->stk_top=list->stk_top->next;
#if JADDR_STACK_DEBUG
      dr_fprintf(STDOUT,"\nget_jaddr_stack_top: Top set to next entry\n");
#endif
    }
    return temp_jlist; // Return the top to be processed. This way the etrans thread can free the entry and doesn't end up popping a different stack top, in case it has been modified by the parent thread or set to NULL before processing the next parent request.
  }
  else
    return NULL;
}

// Returns the addr in the top of the jaddr stack(list)
app_pc get_jaddr_stack_top_addr(struct jaddr_list_attr *list){
  if(list->stk_top != NULL) // Condition to be checked as the compiler thread can be accessing the top even before any entry has been pushed by the app thread or any other compiler thread.
    return list->stk_top->jaddr;
  else
    return NULL;
}

// To return the "tail" pointer of the jaddr list.

/* struct jaddr_etrans_list* get_jaddr_list_tail(struct jaddr_list_attr *list) */
/* { */
/*   return list->tail; */
/* } */


// Add a new entry to the stack top
void push_bb_etrans_jaddr_on_top(struct jaddr_list_attr *list,app_pc new_jaddr)
{
  struct jaddr_etrans_list *temp_jlist;

  if(list->stk_top == NULL)
    {
      list->stk_top=(struct jaddr_etrans_list *)malloc(sizeof(struct jaddr_etrans_list));
      list->stk_top->jaddr=new_jaddr;
      list->stk_top->next=NULL;
      (list->stk_cnt)+=1;
#if JADDR_STACK_DEBUG
      dr_fprintf(STDOUT,"\npush_bb_etrans_jaddr_on_top: New top created. list->stk_cnt - %d\n",list->stk_cnt);
#endif
      if(list->stk_bottom == NULL){
	list->stk_bottom=list->stk_top; // As the pop happens from the top, if the stack is empty, both top and bottom of stack would be set to NULL. For this reason, we are setting the bottom to the top when there is only one entry. So, we don't have to include this code when pushing at stack bottom as the bottom is already set when top is set with one single entry in stack.
#if JADDR_STACK_DEBUG
	dr_fprintf(STDOUT,"\npush_bb_etrans_jaddr_on_top: bottom set to top\n");
#endif
      }
    }
  else
    {
      (list->stk_cnt)+=1;
      //if(list->stk_cnt == 2) // Forming the link between the top and bottom, as next of both top and bottom are NULL and also top and bottom are one and the same until this point. Now as the entries are more than 1, link between top and bottom is to be made top->bottom, to make sure all addresses inserted at top and bottom belong to the same stack chain and do not form a different strand starting at same address.
	  //list->stk_top->next=list->stk_bottom;
      // Looks like the commented case list->stk_cnt == 2 is not needed afterall, as at this point top=bottom, so, setting new top->next as current top is equivalent to setting new top->next to current bottom.
      temp_jlist=(struct jaddr_etrans_list *)malloc(sizeof(struct jaddr_etrans_list));
      temp_jlist->jaddr=new_jaddr;
      temp_jlist->next=list->stk_top;
      list->stk_top=temp_jlist;
#if JADDR_STACK_DEBUG
      dr_fprintf(STDOUT,"\npush_bb_etrans_jaddr_on_top: New entry pushed on top. list->stk_cnt - %d\n",list->stk_cnt);
#endif
    }
}


// Add a new entry to the stack top
void push_bb_etrans_jaddr_at_bottom(struct jaddr_list_attr *list,app_pc new_jaddr)
{
  struct jaddr_etrans_list *temp_jlist;

  if(list->stk_bottom == NULL){
    list->stk_bottom=(struct jaddr_etrans_list *)malloc(sizeof(struct jaddr_etrans_list));
    list->stk_bottom->jaddr=new_jaddr;
    list->stk_bottom->next=NULL;
    (list->stk_cnt)+=1;
#if JADDR_STACK_DEBUG
    dr_fprintf(STDOUT,"\npush_bb_etrans_jaddr_at_bottom: New bottom created. list->stk_cnt - %d\n",list->stk_cnt);
#endif
    if(list->stk_top == NULL){
      list->stk_top=list->stk_bottom;
#if JADDR_STACK_DEBUG
      dr_fprintf(STDOUT,"\npush_bb_etrans_jaddr_at_bottom: top set to bottom\n");
#endif
    }
  }
  else{
    (list->stk_cnt)+=1;
    // Not doing a check on list->stk_cnt==2 as until this point only one entry is in stack and top=bottom. Updating bottom->next implicitly implies top->next modified as well and hence the link between the current top and the new bottom. However, case is different when the second entry is added to the top and link between new top and current bottom is to made to form the chain of entries in stack.
    temp_jlist=(struct jaddr_etrans_list *)malloc(sizeof(struct jaddr_etrans_list));
    temp_jlist->jaddr=new_jaddr;
    temp_jlist->next=NULL;
    list->stk_bottom->next=temp_jlist;
    list->stk_bottom=temp_jlist;
#if JADDR_STACK_DEBUG
    dr_fprintf(STDOUT,"\npush_bb_etrans_jaddr_at_bottom: New entry added to bottom. list->stk_cnt - %d\n",list->stk_cnt);
#endif
  }
}


// To release the dynamic memory allocated for each jaddr list entry
//void release_jaddr_list_entry(struct jaddr_etrans_list *curr)
//{
// free(curr);
//}



struct jaddr_etrans_list* pop_bb_etrans_jaddr_from_top(struct jaddr_list_attr *list){

struct jaddr_etrans_list *temp_jlist;

 if(list->stk_top != NULL){
   temp_jlist=list->stk_top; // Store top in temp
   list->stk_top=list->stk_top->next; // Point top to the next entry
   //   free(temp_jlist); // Free the top in temp
   (list->stk_cnt)-=1; // Reduce the entry cnt
   return temp_jlist;
 }

}

// To set the "curr" pointer, which is the next entry of the jaddr list to be processed in the eager translation
/* void set_jaddr_list_head(struct jaddr_list_attr *list,struct jaddr_etrans_list *t_head) */
/* { */
/*   list->head=t_head; */
/*   list->l_entry_cnt=list->l_entry_cnt - 1; */
/* #if SURYA_DEBUG */
/*   dr_fprintf(STDOUT,"Compiler2: jaddr list head has been set and current list entry cnt - %d\n",list->l_entry_cnt); // Function called form etrans code which is in compiler 2 */
/* #endif */
/* } */


// To get the number of entries in the jaddr list stored in the global variable l_entry_cnt

int get_list_entry_count(struct jaddr_list_attr *list)
{
  return list->stk_cnt;
}


// Function to append the list of jaddr's gathered with parent request to the etrans list.

/* void append_p_req_to_etrans_list(struct jaddr_list_attr *list_etrans,struct jaddr_list_attr *list_preq){ */

/*   struct jaddr_etrans_list *tmp,*tmp1; */
/*   tmp=list_preq->head; */
/*   // Use the l_entry_cnt in the parent req list to do the copy in a loop. Make sure to reset the parent req list with every service to teh parent request, inorder for this logic to work. */
/*   for(int i=0;(i<(list_preq->l_entry_cnt)) && (tmp != NULL);i++){ */
/*     add_bb_etrans_jaddr(list_etrans,tmp->jaddr); */
/*     tmp=tmp->next; */
/*   } */

/* #if SURYA_DEBUG */
/*   dr_fprintf(STDOUT,"\nappend_p_req_to_etrans_list: %d Jaddr's from parent_req_list have been appended to  etrans_list\n",list_preq->l_entry_cnt); */
/* #endif */
/* } */


  // Function to reset to the root, head and tail of the jaddr list populated while serving the parent request.

/* void reset_preq_list(void){ */

/*   if(parent_req_list == NULL) // Allocate memory to the list of jaddr's populated(for first time) while processing parent request. */
/*     { */
/*       parent_req_list=(struct jaddr_list_attr *)malloc(sizeof(struct jaddr_list_attr)); */
/*     } */
/*   parent_req_list->root=NULL; */
/*   parent_req_list->head=NULL; */
/*   parent_req_list->tail=NULL; */
/*   parent_req_list->l_entry_cnt=0; */
/* #if SURYA_DEBUG */
/*   dr_fprintf(STDOUT,"\nreset_preq_list: parent_req_list entries have been reset\n"); */
/* #endif */
/* } */

void initialize_etrans_list(){
  etrans_list=(struct jaddr_list_attr *)malloc(sizeof(struct jaddr_list_attr));
  etrans_list->stk_top=NULL;
  etrans_list->stk_bottom=NULL;
  etrans_list->stk_cnt=0;
}

void decrement_stack_entry_cnt(struct jaddr_list_attr *list){
  (list->stk_cnt)-=1; // Reduce the entry cnt
}

void clear_jaddr_stack(struct jaddr_list_attr *list){

  struct jaddr_etrans_list *temp_jlist;
  
  while(list->stk_top != NULL){
    temp_jlist=list->stk_top; // Store the top in temp pointer
    list->stk_top=list->stk_top->next; // Set the top to the next entry in the stack
    free(temp_jlist); // Free the entry in the temp pointer
    (list->stk_cnt)-=1; // Reduce the entry cnt
  }
}
