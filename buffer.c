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
	
	/* CHECK LISTS ARE CREATED AS REQUIRED */
	
	print_free_list(FREE_LIST);
	print_hash_queue(&HASH_QUEUE[0]);
	print_hash_queue(&HASH_QUEUE[1]);
	
	//**************************************/
	
	printf("\n--done--");
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

}


