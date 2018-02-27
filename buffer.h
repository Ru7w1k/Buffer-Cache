#ifndef BUFFER_H
#define BUFFER_H

/* A buffer structure with 1KB of data size */

typedef struct buffer 
{
	unsigned int logical_device_number;
	unsigned int logical_block_number;
	unsigned char status;

	unsigned char data[1024];
	
	buffer *prev_Hash_Queue;
	buffer *next_Hash_Queue;
	buffer *prev_Free_List;
	buffer *next_Free_List;
} buffer;

#endif
