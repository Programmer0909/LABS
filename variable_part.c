#include <stdio.h>
#include <stdlib.h>

#define RAM_SIZE 1024 // Size of the RAM in kilobytes

// Structure to represent a memory block
struct MemoryBlock
{
    int size;                 // Size of the block
    int is_allocated;         // Flag to indicate if the block is allocated (1) or free (0)
    struct MemoryBlock *next; // Pointer to the next memory block
};

// Function to initialize the RAM with a single free block
void initializeRAM(struct MemoryBlock *ram, int size)
{
    ram->size = size;
    ram->is_allocated = 0;
    ram->next = NULL;
}

// Function to allocate memory block
void allocateMemory(struct MemoryBlock *ram, int size)
{
    struct MemoryBlock *current = ram;

    while (current)
    {
        if (!current->is_allocated && current->size >= size)
        {
            current->is_allocated = 1;
            if (current->size > size)
            {
                struct MemoryBlock *new_block = (struct MemoryBlock *)malloc(sizeof(struct MemoryBlock));
                new_block->size = current->size - size;
                new_block->is_allocated = 0;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }
            break;
        }

        current = current->next;
    }

    if (!current)
    {
        printf("Memory allocation failed for size %d KB\n", size);
    }
}

// Function to deallocate memory block
void deallocateMemory(struct MemoryBlock *ram, int size)
{
    struct MemoryBlock *current = ram;

    while (current)
    {
        if (current->is_allocated && current->size == size)
        {
            current->is_allocated = 0;
            break;
        }

        current = current->next;
    }

    if (!current)
    {
        printf("Memory deallocation failed for size %d KB\n", size);
    }
}

// Function to print the RAM status
void printRAM(struct MemoryBlock *ram)
{
    struct MemoryBlock *current = ram;
    int block_number = 1;

    while (current)
    {
        printf("Block %d: %d KB %s\n", block_number, current->size, current->is_allocated ? "Allocated" : "Free");
        current = current->next;
        block_number++;
    }
}

int main()
{
    struct MemoryBlock *ram = (struct MemoryBlock *)malloc(sizeof(struct MemoryBlock));
    ram->next = NULL;

    initializeRAM(ram, RAM_SIZE);

    allocateMemory(ram, 256);
    allocateMemory(ram, 128);
    allocateMemory(ram, 64);

    printRAM(ram);

    deallocateMemory(ram, 128);

    printRAM(ram);

    return 0;
}
