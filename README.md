# RT-Memory-Pool

Memory allocation and deallocation in real-time systems are critical operations that must be performed efficiently and deterministically to meet timing constraints. Traditional memory allocation strategies, such as dynamic memory allocation using malloc() and free(), may not always be suitable for real-time systems due to their non-deterministic behavior and potential for memory fragmentation.

A memory pool is a memory management technique that pre-allocates a fixed-size block of memory and manages memory allocation and deallocation within this fixed-size block. This approach offers deterministic memory allocation and deallocation times, making it suitable for real-time systems where predictability is crucial.

This particular memory pool implementation optimizes memory management by using a linked list structure to manage free blocks within the allocated memory block. Rather than maintaining separate data structures for tracking free and allocated memory blocks, free memory blocks are repurposed for managing the free blocks list. This minimizes memory overhead and avoids the need for additional bookkeeping data structures.

Based on Fast Efficient Fixed-Size Memory Pool No Loops and No Overhead article.
