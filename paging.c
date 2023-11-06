// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// // Define the page and frame sizes
// const int PAGE_SIZE = 4096; // 4KB
// const int RAM_SIZE = 65536; // 64KB

// // Page table entry structure
// struct PageTableEntry {
//     int frame_number;
//     int valid;
// };

// // Process structure
// struct Process {
//     int process_id;
//     int size;
//     struct PageTableEntry *page_table;
// };

// // Function to allocate a frame to a page
// void allocateFrame(struct Process *process, int page, int frame, int *free_frames) {
//     process->page_table[page].frame_number = frame;
//     process->page_table[page].valid = 1;
//     free_frames[frame] = 0;
//     printf("Allocated Frame %d to Process %d, Page %d\n", frame, process->process_id, page);
// }

// int main() {
//     int num_processes;
//     printf("Enter the number of processes: ");
//     scanf("%d", &num_processes);
//     struct Process *processes = (struct Process *)malloc(num_processes * sizeof(struct Process));

//     for (int i = 0; i < num_processes; i++) {
//         printf("Enter the size of Process %d (in pages): ", i);
//         scanf("%d", &processes[i].size);
//         processes[i].process_id = i;
//         processes[i].page_table = (struct PageTableEntry *)malloc(processes[i].size * sizeof(struct PageTableEntry));

//         for (int j = 0; j < processes[i].size; j++) {
//             processes[i].page_table[j].valid = 0;
//         }
//     }

//     // Create an array of free frames
//     int *free_frames = (int *)malloc(RAM_SIZE / PAGE_SIZE * sizeof(int));
//     for (int i = 0; i < RAM_SIZE / PAGE_SIZE; i++) {
//         free_frames[i] = 1;
//     }

//     // Allocate pages to frames
//     int allocationPossible = 1;

//     while (allocationPossible) {
//         allocationPossible = 0;

//         for (int i = 0; i < num_processes; i++) {
//             if (processes[i].size == 0) {
//                 continue;
//             }

//             int page = rand() % processes[i].size;
//             int frame = -1;

//             for (int j = 0; j < RAM_SIZE / PAGE_SIZE; j++) {
//                 if (free_frames[j]) {
//                     frame = j;
//                     break;
//                 }
//             }

//             if (frame != -1) {
//                 allocateFrame(&processes[i], page, frame, free_frames);
//                 processes[i].size--;
//                 allocationPossible = 1;
//             }
//         }
//     }

//     // Print page tables and frame allocation status
//     for (int i = 0; i < num_processes; i++) {
//         printf("Process %d Page Table:\n", processes[i].process_id);

//         for (int j = 0; j < processes[i].size; j++) {
//             if (processes[i].page_table[j].valid) {
//                 printf("Page %d -> Frame %d\n", j, processes[i].page_table[j].frame_number);
//             } else {
//                 printf("Page %d -> Not in RAM\n", j);
//             }
//         }
//     }

//     // Free allocated memory
//     for (int i = 0; i < num_processes; i++) {
//         free(processes[i].page_table);
//     }
//     free(processes);
//     free(free_frames);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the page and frame sizes
const int PAGE_SIZE = 4096; // 4KB
const int RAM_SIZE = 65536; // 64KB

// Page table entry structure
struct PageTableEntry
{
    int frame_number;
    int valid;
};

// Process structure
struct Process
{
    int process_id;
    int size;
    struct PageTableEntry *page_table;
};

// Function to allocate a frame to a page
void allocateFrame(struct Process *process, int page, int frame, int *free_frames)
{
    process->page_table[page].frame_number = frame;
    process->page_table[page].valid = 1;
    free_frames[frame] = 0;
    printf("Allocated Frame %d to Process %d, Page %d\n", frame, process->process_id, page);
}

int main()
{
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    struct Process *processes = (struct Process *)malloc(num_processes * sizeof(struct Process));

    for (int i = 0; i < num_processes; i++)
    {
        printf("Enter the size of Process %d (in pages): ", i);
        scanf("%d", &processes[i].size);
        processes[i].process_id = i;
        processes[i].page_table = (struct PageTableEntry *)malloc(processes[i].size * sizeof(struct PageTableEntry));

        for (int j = 0; j < processes[i].size; j++)
        {
            processes[i].page_table[j].valid = 0;
        }
    }

    // Create an array of free frames
    int *free_frames = (int *)malloc(RAM_SIZE / PAGE_SIZE * sizeof(int));
    for (int i = 0; i < RAM_SIZE / PAGE_SIZE; i++)
    {
        free_frames[i] = 1;
    }

    // Allocate pages to frames
    int allocationPossible = 1;

    while (allocationPossible)
    {
        allocationPossible = 0;

        for (int i = 0; i < num_processes; i++)
        {
            if (processes[i].size == 0)
            {
                continue;
            }

            int page = rand() % processes[i].size;
            int frame = -1;

            for (int j = 0; j < RAM_SIZE / PAGE_SIZE; j++)
            {
                if (free_frames[j])
                {
                    frame = j;
                    break;
                }
            }

            if (frame != -1)
            {
                allocateFrame(&processes[i], page, frame, free_frames);
                processes[i].size--;
                allocationPossible = 1;
            }
        }
    }

    // Print page tables and frame allocation status
    for (int i = 0; i < num_processes; i++)
    {
        printf("Process %d Page Table:\n", processes[i].process_id);

        for (int j = 0; j < processes[i].size; j++)
        {
            if (processes[i].page_table[j].valid)
            {
                printf("Page %d -> Frame %d\n", j, processes[i].page_table[j].frame_number);
            }
            else
            {
                printf("Page %d -> Not in RAM\n", j);
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i < num_processes; i++)
    {
        free(processes[i].page_table);
    }
    free(processes);
    free(free_frames);

    return 0;
}
