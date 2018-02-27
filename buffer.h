#ifndef BUFFER_H
#define BUFFER_H

/* A buffer structure with 1KB of data size */

typedef struct buffer 
{
	unsigned int logical_device_number;
	unsigned int logical_block_number;
	unsigned char status;

	unsigned char data[1024];
	
	struct buffer *prev_Hash_Queue;
	struct buffer *next_Hash_Queue;
	struct buffer *prev_Free_List;
	struct buffer *next_Free_List;
} buffer;

#endif
