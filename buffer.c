#include <stdio.h>
#include "buffer.h"
#include "list.h"

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

int main (int argc, char **argv)
{
	buffer *FREE_LIST = init_free_list(BUFFER_CACHE, BUFFER_COUNT);
	print_list(FREE_LIST);
	printf("--done--");
	return 0;	
}

