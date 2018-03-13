#include <stdio.h>
#include "buffer.h"
#include "free-list.h"
#include "hash-queue.h"

/* Mock the Hard disk size */
#define HARD_DISK_SIZE 1024 * 1000 * 10

/* Define the number of buffers in buffer cache */
#define BUFFER_COUNT 1000
 
/* Define the number of hash queues */
#define HASH_QUEUE_COUNT 20

/* Pseudo Hard Disk  */
unsigned char HARD_DISK[HARD_DISK_SIZE];

/* The Buffer Cache */
buffer BUFFER_CACHE[BUFFER_COUNT];

/* Free List Header */
buffer *FREE_LIST;

/* Hash Queue Headers Array */
buffer *HASH_QUEUE;

int main (int argc, char **argv)
{
    // function declarations 
    buffer *getblk(unsigned int file_system_number, unsigned int block_number);
    void brelse(buffer *block);
    buffer *bread (unsigned int file_system_number, unsigned int block_number);
    buffer *breada(unsigned int file_system_number, unsigned int block_number, unsigned int afile_system_number, unsigned int ablock_number);
    void bwrite(buffer *block);

    // code 
    
	FREE_LIST  = init_free_list  (BUFFER_CACHE, BUFFER_COUNT);
	HASH_QUEUE = init_hash_queue (BUFFER_CACHE, BUFFER_COUNT, HASH_QUEUE_COUNT);
	
	/* CHECK LISTS ARE CREATED AS REQUIRED 
	
	print_free_list(FREE_LIST);
	print_hash_queue(&HASH_QUEUE[0]);
	print_hash_queue(&HASH_QUEUE[1]);
	
	/* Hash Function 
	
	printf("Hash Queue for block 2014: %d \n", hash(0, 2014));
	printf("Hash Queue for block    0: %d \n", hash(0, 0));
	printf("Hash Queue for block 2021: %d \n", hash(0, 2021));		
	
	/* Free List Function 
	
	print_free_list(FREE_LIST);
	remove_free_list(FREE_LIST);
	remove_free_list(FREE_LIST->next_Free_List);
	print_free_list(FREE_LIST);
	
	/* Set Hash Queue Test  */
	
	printf("\nHash Queue 0: ");
	print_hash_queue(&HASH_QUEUE[0]);
	printf("\nHash Queue 1: ");
	print_hash_queue(&HASH_QUEUE[1]);
	
	FREE_LIST->next_Free_List->logical_block_number = 1001;	
	set_hash_queue(FREE_LIST->next_Free_List, HASH_QUEUE);
	
	printf("\nHash Queue 0: ");
	print_hash_queue(&HASH_QUEUE[0]);
	printf("\nHash Queue 1: ");
	print_hash_queue(&HASH_QUEUE[1]);
	
	/************************************************************/
	
	printf("\n -- done -- ");
	return 0;	
}

/******************** ALGORITHMS ********************/

/*
 * getblk - get a free buffer from buffer cache 
 * input1 - logical device number / file system number
 * input2 - logical block number
 * output - locked buffer
 */
buffer *getblk(unsigned int file_system_number, unsigned int block_number)
{
    buffer *blk = NULL;
    int onHashQueue = 0;
    int hash_queue_index = hash(file_system_number, block_number);
    
    while(!blk) /* while buffer not found */
    {
        /* scan hash queue for required block */
        buffer *ptr = HASH_QUEUE[hash_queue_index].next_Hash_Queue;
        while(ptr->status != BF_DUMMY)
        {
            if(ptr->logical_block_number == block_number)
            {
                onHashQueue = 1;   
                break;
            }
            ptr = ptr->next_Hash_Queue;
        }
        
        if(onHashQueue) /* block in hash queue */
        {
            if(ptr->status & BF_LOCKED) /* scenario 5 */
            {
                /* sleep (event: buffer becomes free) */
                continue;
            }
            
            ptr->status |= BF_LOCKED; /* scenario 1 */
            remove_free_list(ptr);
            return ptr;            
        }
        
        else /* block not on hash queue */
        {
            if(FREE_LIST->next_Free_List->status & BF_DUMMY) /* scenario 4 */
            {
                /* sleep (event: any buffer becomes free) */
                continue;
            }
            
            blk = get_free_buffer(FREE_LIST);
            if(blk->status & BF_DWRITE) /* scenario 3 */
            {
                /* ASYNC bwrite() */
                continue;
            }
            
            /* scenario 2 */
            set_hash_queue(blk, HASH_QUEUE);
            return(blk);
        }        
    }
}


