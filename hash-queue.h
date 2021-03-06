/* Doubly Circular Link List to manage hash queues of buffers in buffer cache */

#include "buffer.h"
#include <stdlib.h>

#ifndef HASH_QUEUE_H
#define HASH_QUEUE_H

int HASH_QUEUE_COUNT = 0;

/* The HASH function 
 * It returns block_number mod HASH_QUEUE_COUNT
 * input1 : file system number
 * input2 : logical block number
 * output : index of appropriate HASH_QUEUE
 */
int hash(unsigned int file_system_number, unsigned int block_number)
{
    return block_number % HASH_QUEUE_COUNT;
} 


/*  Initialize a particular hash queues with appropriate buffers  
 *  input1 : pointer to BUFFER_CACHE
 *  input2 : pointer to DUMMY HEADER of HASH QUEUE
 *  input3 : index of hash queue to initialize
 *  input4 : size of hash queue
 *  output : dummy header node for hash queue
 */
void __init_hash_queue(buffer *BUFFER_CACHE, buffer *header, int HASH_QUEUE_INDEX, int HASH_QUEUE_SIZE)
{
    /* set status to BF_DUMMY */
    header->status = BF_DUMMY;

    /* Assign both pointers of dummy header */
    header->next_Hash_Queue = &BUFFER_CACHE[(HASH_QUEUE_COUNT * 0) + HASH_QUEUE_INDEX];
    header->prev_Hash_Queue = &BUFFER_CACHE[(HASH_QUEUE_COUNT * (HASH_QUEUE_SIZE-1)) + HASH_QUEUE_INDEX];
    
    /* manually handle first buffer's pointers */ 
    BUFFER_CACHE[(HASH_QUEUE_COUNT * 0) + HASH_QUEUE_INDEX].prev_Hash_Queue = header;
    BUFFER_CACHE[(HASH_QUEUE_COUNT * 0) + HASH_QUEUE_INDEX].next_Hash_Queue = &BUFFER_CACHE[(HASH_QUEUE_COUNT * 1) + HASH_QUEUE_INDEX];
    
    /* manually handle last buffer's pointers */ 
    BUFFER_CACHE[(HASH_QUEUE_COUNT * (HASH_QUEUE_SIZE-1)) + HASH_QUEUE_INDEX].prev_Hash_Queue = &BUFFER_CACHE[(HASH_QUEUE_COUNT * (HASH_QUEUE_SIZE-2)) + HASH_QUEUE_INDEX];
    BUFFER_CACHE[(HASH_QUEUE_COUNT * (HASH_QUEUE_SIZE-1)) + HASH_QUEUE_INDEX].next_Hash_Queue = header;

    /* middle buffers are connected using loop */
    for(int i = 1; i < HASH_QUEUE_SIZE - 1; i++)
    {
        BUFFER_CACHE[(HASH_QUEUE_COUNT * i) + HASH_QUEUE_INDEX].next_Hash_Queue = &BUFFER_CACHE[(HASH_QUEUE_COUNT * (i+1)) + HASH_QUEUE_INDEX];
        BUFFER_CACHE[(HASH_QUEUE_COUNT * i) + HASH_QUEUE_INDEX].prev_Hash_Queue = &BUFFER_CACHE[(HASH_QUEUE_COUNT * (i-1)) + HASH_QUEUE_INDEX];
    }
   
}


/*  Initialize all hash queues of buffers with appropriate buffers in hash queue attached in sequence. 
 *  input1 : pointer to BUFFER_CACHE, 
 *  input2 : number of buffers in BUFFER_CACHE
 *  output : dummy header node for hash queue
 */
buffer *init_hash_queue(buffer *BUFFER_CACHE, int BUFFER_COUNT, int COUNT)
{
    int i = 0;
    HASH_QUEUE_COUNT = COUNT;
    int HASH_QUEUE_SIZE = BUFFER_COUNT / HASH_QUEUE_COUNT;
    
    /* create a dummy header for list of hash queue headers */
    buffer *dummy_head = /*(buffer *)*/ malloc(sizeof(buffer) * HASH_QUEUE_COUNT);
    
    for(i = 0; i < HASH_QUEUE_COUNT; i++)
    {
        __init_hash_queue(BUFFER_CACHE, &dummy_head[i], i, HASH_QUEUE_SIZE);
    }

	return dummy_head;
}
 
void insert_end_hash_queue(buffer *head, buffer *node)
{
	node->next_Hash_Queue = head;
	node->prev_Hash_Queue = head->prev_Hash_Queue;
	head->prev_Hash_Queue->next_Hash_Queue = node;
	head->prev_Hash_Queue = node;
}


/*
 * Remove blk from its hash queue and put it in header hash queue
 * input1 : block to shift
 * input2 : header of destination hash queue
 */
void set_hash_queue(buffer *blk, buffer *HASH_QUEUE)
{
    /* calculate hash queue number */ 
    int hash_queue = hash(blk->logical_device_number, blk->logical_block_number);
    
    /* remove from old hash queue */
    blk->prev_Hash_Queue->next_Hash_Queue = blk->next_Hash_Queue;
    blk->next_Hash_Queue->prev_Hash_Queue = blk->prev_Hash_Queue;
    
    /* insert into new hash queue */
    insert_end_hash_queue(&HASH_QUEUE[hash_queue], blk);
}

void print_hash_queue (buffer *head)
{
	buffer *ptr = head;
	while(ptr->next_Hash_Queue->status != BF_DUMMY)
	{
	    ptr = ptr->next_Hash_Queue;
		printf("%d:%d %s \t", ptr->logical_device_number, ptr->logical_block_number, ptr->data);		
	}
}

#endif
