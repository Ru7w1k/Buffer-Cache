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
	FREE_LIST  = init_free_list  (BUFFER_CACHE, BUFFER_COUNT);
	HASH_QUEUE = init_hash_queue (BUFFER_CACHE, BUFFER_COUNT, HASH_QUEUE_COUNT);
	
	//print_list(FREE_LIST);
	print_hash_queue(&HASH_QUEUE[0]);
	print_hash_queue(&HASH_QUEUE[1]);
	
	printf("\n--done--");
	return 0;	
}

