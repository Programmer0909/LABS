#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_SIZE 16
#define LOGICAL_ADDRESS_BITS 16

int page_table[PAGE_TABLE_SIZE];

void createSamplePageTable()
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < PAGE_TABLE_SIZE; i++)
    {
        page_table[i] = rand() % 64;
    }
}

struct TranslationResult
{
    int physical_address;
    int frame_number;
};

struct TranslationResult translateAddress(int logical_address)
{
    int page_number = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE;
    int frame_number = -1;
    int physical_address = -1;

    for (int i = 0; i < PAGE_TABLE_SIZE; i++)
    {
        if (i == page_number)
        {
            frame_number = page_table[i];
            physical_address = (frame_number * PAGE_SIZE) + offset;
            break;
        }
    }

    struct TranslationResult result;
    result.physical_address = physical_address;
    result.frame_number = frame_number;
    return result;
}

int main()
{
    createSamplePageTable();
    int num_addresses_to_generate = 10;

    printf("Logical Address\tPhysical Address\tFrame Number\n");
    for (int i = 0; i < num_addresses_to_generate; i++)
    {
        int logical_address = rand() % (1 << LOGICAL_ADDRESS_BITS);
        struct TranslationResult result = translateAddress(logical_address);
        int physical_address = result.physical_address;
        int frame_number = result.frame_number;
        printf("%d\t\t%d\t\t\t%d\n", logical_address, physical_address, frame_number);
    }

    printf("\nPage Table Entries:\n");
    for (int i = 0; i < PAGE_TABLE_SIZE; i++)
    {
        printf("Page %d: Frame %d\n", i, page_table[i]);
    }

    return 0;
}
