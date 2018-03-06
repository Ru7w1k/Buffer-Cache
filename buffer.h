#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 1024

/* Buffer States */

#define BF_LOCKED 0b00000001
#define BF_VALID  0b00000010
#define BF_DWRITE 0b00000100
#define BF_INIO   0b00001000
#define BF_DEMAND 0b00010000
#define BF_DUMMY  0b11100000

/* A buffer structure with 1KB of data size */
typedef struct buffer 
{
	unsigned int logical_device_number;
	unsigned int logical_block_number;
	unsigned char status;

	unsigned char data[BUFFER_SIZE];
	
	struct buffer *prev_Hash_Queue;
	struct buffer *next_Hash_Queue;
	struct buffer *prev_Free_List;
	struct buffer *next_Free_List;
} buffer;

#endif
