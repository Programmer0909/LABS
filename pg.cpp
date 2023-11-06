#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;

// Define the page and frame sizes
const int PAGE_SIZE = 4096; // 4KB
const int RAM_SIZE = 65536; // 64KB

// Page table entry structure
struct PageTableEntry
{
    int frame_number;
    bool valid;
};

// Process structure
struct Process
{
    int process_id;
    int size;
    vector<PageTableEntry> page_table;
};

// Function to allocate a frame to a page
void allocateFrame(Process &process, int page, int frame, map<int, bool> &free_frames)
{
    process.page_table[page].frame_number = frame;
    process.page_table[page].valid = true;
    free_frames[frame] = false;
    cout << "Allocated Frame " << frame << " to Process " << process.process_id << ", Page " << page << endl;
}

int main()
{
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    vector<Process> processes(num_processes);

    for (int i = 0; i < num_processes; i++)
    {
        cout << "Enter the size of Process " << i << " (in pages): ";
        cin >> processes[i].size;
        processes[i].process_id = i;
        processes[i].page_table.resize(processes[i].size);

        for (int j = 0; j < processes[i].size; j++)
        {
            processes[i].page_table[j].valid = false;
        }
    }

    // Create a list of free frames
    map<int, bool> free_frames;
    for (int i = 0; i < RAM_SIZE / PAGE_SIZE; i++)
    {
        free_frames[i] = true;
    }

    // Allocate pages to frames
    bool allocationPossible = true;

    while (allocationPossible)
    {
        allocationPossible = false;

        for (int i = 0; i < num_processes; i++)
        {
            if (processes[i].size == 0)
            {
                continue;
            }

            int page = rand() % processes[i].size;
            int frame = -1;

            for (auto &entry : free_frames)
            {
                if (entry.second)
                {
                    frame = entry.first;
                    break;
                }
            }

            if (frame != -1)
            {
                allocateFrame(processes[i], page, frame, free_frames);
                processes[i].size--;
                allocationPossible = true;
            }
        }
    }

    // Print page tables and frame allocation status
    for (int i = 0; i < num_processes; i++)
    {
        cout << "Process " << processes[i].process_id << " Page Table:" << endl;

        for (int j = 0; j < processes[i].size; j++)
        {
            if (processes[i].page_table[j].valid)
            {
                cout << "Page " << j << " -> Frame " << processes[i].page_table[j].frame_number << endl;
            }
            else
            {
                cout << "Page " << j << " -> Not in RAM" << endl;
            }
        }
    }

    return 0;
}
