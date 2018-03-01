/* Doubly Circular Link List to manage hash queues of buffers in buffer cache */

#include "buffer.h"
#include <stdlib.h>

#ifndef HASH_QUEUE_H
#define HASH_QUEUE_H

/*  Initialize a particular hash queues with appropriate buffers  
 *  input1 : pointer to BUFFER_CACHE, 
 *  input2 : pointer to DUMMY HEADER of HASH QUEUE,
 *  output : dummy header node for hash queue
 */
buffer *__init_hash_queue(buffer *BUFFER_CACHE, buffer *header)
{
    header->next_Hash_Queue = 
}


/*  Initialize all hash queues of buffers with appropriate buffers in hash queue attached in sequence. 
 *  input1 : pointer to BUFFER_CACHE, 
 *  input2 : number of buffers in BUFFER_CACHE
 *  output : dummy header node for hash queue
 */
buffer *init_hash_queue(buffer *BUFFER_CACHE, int BUFFER_COUNT, int HASH_QUEUE_COUNT)
{
    int i = 0;
    int HASH_QUEUE_SIZE = BUFFER_COUNT / HASH_QUEUE_COUNT;
    
	/* create a dummy header with status 255 for list of hash queue headers */
	buffer *dummy_head = (buffer *) malloc(sizeof(buffer) * HASH_QUEUE_COUNT);
	dummy_head->status = 255;

    for(i = 0; i < HASH_QUEUE_COUNT; i++)
    {
        __init_hash_queue(BUFFER_CACHE, dummy_head[i]);
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

void print_list (buffer *head)
{
	buffer *ptr = head;
	while(ptr->next_Free_List->status != 255)
	{
	    ptr = ptr->next_Free_List;
		printf("%d:%d %s \n", ptr->logical_device_number, ptr->logical_block_number, ptr->data);		
	}
}

#endif
