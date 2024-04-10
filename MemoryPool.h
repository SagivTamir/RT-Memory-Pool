#ifndef MEM_POOL_H
#define MEM_POOL_H

/**
 * allocates the number of bytes that required by memory_size and splits it into equal size blocks.
 * at the end, must be freed by user.
 * @param memory_size - total memory required.(in bytes)
 * @return pointer to the beginning of the memory which allocated, NULL if allocation failed / invalid argument passed
 */
int *memoryInit(int memory_size);
/**
 * NOTE: the function does not guaranteed to return continuous memory blocks in two following calls.
 * @return returns a block of memory which allocated previously in memoryInit().
 */
int *myMalloc();

/**
 *  deallocates the block of memory that pointed by ptr
 * @param ptr - pointer to the block that received by myMalloc()
 */
void myFree(int *ptr);








#endif //MEM_POOL_H
