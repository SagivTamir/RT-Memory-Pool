#include "MemoryPool.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define SIZE_OF_BLOCK 4
#define END_OF_LINKED_LIST -1

static int *getAddressByIndex(int index);

static bool allBlocksFull();

static int getIndexBlockFromAddress(const int *ptr);

static bool isValidAddress(const int *ptr);

static bool isFreeBlock(const int *ptr);

static bool isAllBlocksInitialized();

static bool isBlockAlreadyInitialized(const int *block_to_check);


struct Memory_pool_t {
    int total_size;
    int *mem_ptr;
    int *head_ptr;
    int last_block_initialized;
    int full_blocks;
} MemPool;


int *memoryInit(int memory_size) {
    // validation check
    if (memory_size < SIZE_OF_BLOCK) { return NULL; }

    MemPool.total_size = memory_size;
    MemPool.full_blocks = 0;
    MemPool.last_block_initialized = 0;
    // allocates the total memory ptr
    int *tot_mem = malloc(memory_size * sizeof(char));
    if (tot_mem == NULL) {
        // allocation failed
        return NULL;
    }
    MemPool.mem_ptr = tot_mem;
    MemPool.head_ptr = NULL;
    return MemPool.mem_ptr;
}

int *myMalloc() {
    int *free_block_for_user;
    if (allBlocksFull()) {
        // pool is all used
        return NULL;
    } else if (!isAllBlocksInitialized()) {
        free_block_for_user = getAddressByIndex(MemPool.last_block_initialized);
        MemPool.last_block_initialized++;
    } else {
        // finding the next free block
        int next_free_block_index = *(MemPool.head_ptr);
        int *new_head = getAddressByIndex(next_free_block_index);
        free_block_for_user = MemPool.head_ptr;
        MemPool.head_ptr = new_head;
    }
    MemPool.full_blocks++;
    // check if after this malloc there are no free blocks
    if (allBlocksFull()) {
        MemPool.head_ptr = NULL;
    }
    return free_block_for_user;
}

void myFree(int *ptr) {
    if (ptr == NULL || !isValidAddress(ptr) || isFreeBlock(ptr)) { return; }
    if (allBlocksFull()) {
        // edge case
        MemPool.head_ptr = ptr;
        *(ptr) = END_OF_LINKED_LIST;
    } else {
        // there is at least 1 free block already
        int *prev_head = MemPool.head_ptr;
        MemPool.head_ptr = ptr;
        // new head store prev head index
        *(ptr) = getIndexBlockFromAddress(prev_head);
    }
    MemPool.full_blocks--;
}


static int *getAddressByIndex(int index) {
    return (int *) ((void *) MemPool.mem_ptr + (index * SIZE_OF_BLOCK));
}

static int getIndexBlockFromAddress(const int *ptr) {
    if (ptr == NULL) {
        return END_OF_LINKED_LIST;
    }
    return ((void *) ptr - (void *) MemPool.mem_ptr) / SIZE_OF_BLOCK;
}

static bool isValidAddress(const int *ptr) {
    int dist = (void *) ptr - (void *) MemPool.mem_ptr;
    return (ptr != NULL && dist >= 0 && dist < MemPool.total_size && dist % SIZE_OF_BLOCK == 0);
}


static bool allBlocksFull() {
    int number_of_blocks = MemPool.total_size / SIZE_OF_BLOCK;
    return MemPool.full_blocks == number_of_blocks;
}


static bool isFreeBlock(const int *ptr) {
    if (!isBlockAlreadyInitialized(ptr)) {
        return true;
    }
    int *curr = MemPool.head_ptr;
    if (curr == NULL) {
        return false;
    }
    while (*curr != END_OF_LINKED_LIST) {
        if (curr == ptr) {
            return true;
        }
        curr = getAddressByIndex(*curr);
    }
    // check the last ptr
    return curr == ptr;
}

static bool isAllBlocksInitialized() {
    return MemPool.last_block_initialized == (int) (MemPool.total_size / SIZE_OF_BLOCK);
}

static bool isBlockAlreadyInitialized(const int *block_to_check) {
    return (((void *) block_to_check - (void *) MemPool.mem_ptr) / SIZE_OF_BLOCK) < MemPool.last_block_initialized;
}