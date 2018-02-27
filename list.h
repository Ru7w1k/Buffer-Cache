/* Doubly Circular Link List to manage free list and hash queues of buffers in buffer cache */

#include "buffer.h"
#include <stdlib.h>

#ifndef LIST_H
#define LIST_H

/* Initialize a free list of buffers with all available buffers in free list attached in sequence. 
*  input1 : pointer to BUFFER_CACHE, 
*  input2 : number of buffers in BUFFER_CACHE
*  output : dummy header node for free list
*/
buffer *init_free_list(buffer *BUFFER_CACHE, int BUFFER_COUNT)
{

	/* create a dummy header with status 255 */
	buffer *dummy_head = (buffer *) malloc(sizeof(buffer));
	dummy_head->status = 255;
	
	/* link first and last buffer to dummy_head */
	dummy_head->next_Free_List = BUFFER_CACHE[0];
	dummy_head->prev_Free_List = BUFFER_CACHE[BUFFER_COUNT-1];

	BUFFER_CACHE[0]->prev_Free_List = dummy_head;
	BUFFER_CACHE[0]->next_Free_List = BUFFER_CACHE[1];	

	BUFFER_CACHE[BUFFER_COUNT-1]->next_Free_List = dummy_head;
	BUFFER_CACHE[BUFFER_COUNT-1]->prev_Free_List = BUFFER_CACHE [BUFFER_COUNT-2];

	for(int i = 1 ; i < BUFFER_COUNT - 1 ; i++)
	{
		BUFFER_CACHE[i]->next_Free_List = BUFFER_CACHE[i+1];
		BUFFER_CACHE[i]->prev_Free_List = BUFFER_CACHE[i-1];	
	}
	return dummy_head;
}

void insert_head_free_list(buffer *head, buffer *node)
{
	node->next_Free_List = head->next_Free_List;
	node->prev_Free_List = head;
	head->next_Free_List->prev_FreeList = node;
	head->next_Free_List = node;
}

void insert_end_free_list(buffer *head, buffer *node)
{
	node->next_Free_List = head;
	node->prev_Free_List = head->prev_Free_List;
	head->prev_Free_List->next_Free_List = node;
	head->prev_Free_List = node;
}

void print_list (buffer *head)
{
	buffer *ptr = head;
	while(ptr->status != 255)
	{
		printf("%u:%u %s", head->logical_device_number, head->logical_block_number, head->data);
		ptr = ptr->next_Free_List;
	}
}

#endif
