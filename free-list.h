/* Doubly Circular Link List to manage free list of buffers in buffer cache */

#include "buffer.h"
#include <stdlib.h>

#ifndef FREE_LIST_H
#define FREE_LIST_H

/* Initialize a free list of buffers with all available buffers in free list attached in sequence. 
*  input1 : pointer to BUFFER_CACHE, 
*  input2 : number of buffers in BUFFER_CACHE
*  output : dummy header node for free list
*/
buffer *init_free_list(buffer *BUFFER_CACHE, int BUFFER_COUNT)
{
    int i = 0;

	/* create a dummy header with status BF_DUMMY */
	buffer *dummy_head = /*(buffer *)*/ malloc(sizeof(buffer));
	dummy_head->status = BF_DUMMY;
	
	/* link first and last buffer to dummy_head */
	dummy_head->next_Free_List = &BUFFER_CACHE[0];
	dummy_head->prev_Free_List = &BUFFER_CACHE[BUFFER_COUNT-1];

    /* connect all links of 1st buffer */
	BUFFER_CACHE[0].prev_Free_List = dummy_head;
	BUFFER_CACHE[0].next_Free_List = &BUFFER_CACHE[1];	
	BUFFER_CACHE[0].logical_block_number = 0;
	BUFFER_CACHE[0].status = 0;

    /* connect all links of last buffer */
	BUFFER_CACHE[BUFFER_COUNT-1].next_Free_List = dummy_head;
	BUFFER_CACHE[BUFFER_COUNT-1].prev_Free_List = &BUFFER_CACHE [BUFFER_COUNT-2];
	BUFFER_CACHE[BUFFER_COUNT-1].logical_block_number = BUFFER_COUNT-1;
	BUFFER_CACHE[BUFFER_COUNT-1].status = 0;
    
    /* connect all links of intermediate buffers */
	for(i = 1 ; i < BUFFER_COUNT - 1 ; i++)
	{
		BUFFER_CACHE[i].next_Free_List = &BUFFER_CACHE[i+1];
		BUFFER_CACHE[i].prev_Free_List = &BUFFER_CACHE[i-1];
		BUFFER_CACHE[i].logical_block_number = i;
		BUFFER_CACHE[i].status = 0;
	}
	return dummy_head;
}

void insert_head_free_list(buffer *head, buffer *node)
{
	node->next_Free_List = head->next_Free_List;
	node->prev_Free_List = head;
	head->next_Free_List->prev_Free_List = node;
	head->next_Free_List = node;
}

void insert_end_free_list(buffer *head, buffer *node)
{
	node->next_Free_List = head;
	node->prev_Free_List = head->prev_Free_List;
	head->prev_Free_List->next_Free_List = node;
	head->prev_Free_List = node;
}

void remove_free_list(buffer *node)
{
    /* if dummy header is passed, do nothing! */
    if(node->status & BF_DUMMY) return;

    node->status |= BF_LOCKED;

    node->next_Free_List->prev_Free_List = node->prev_Free_List;
    node->prev_Free_List->next_Free_List = node->next_Free_List;    
    node->prev_Free_List = NULL;
    node->next_Free_List = NULL;
}

buffer *get_free_buffer(buffer *FREE_LIST)
{
    buffer *ptr = FREE_LIST->next_Free_List;
    remove_free_list(ptr);
    return ptr;
}

void print_free_list (buffer *head)
{
	buffer *ptr = head;
	while(ptr->next_Free_List->status != BF_DUMMY)
	{
	    ptr = ptr->next_Free_List;
		printf("%d:%d %s \t", ptr->logical_device_number, ptr->logical_block_number, ptr->data);		
	}
}

#endif
