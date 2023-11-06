#include <stdio.h>

void firstFit(int m, int processSize[], int n)
{
    int allocation[n];
    int blockSize[] = {128, 256, 150};

    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nProcess N\tProcess Size\tBlock n\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
        {
            printf("%d", allocation[i] + 1);
        }
        else
        {
            printf("Not Allocated");
        }
        printf("\n");
    }
}

void bestFit(int m, int processSize[], int n)
{
    int allocation[n];
    int blockSize[] = {128, 256, 150};
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                {
                    bestIdx = j;
                } else if (blockSize[bestIdx] > blockSize[j])
                {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nProcess N\tProcess Size\tBlock n\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
        {
            printf("%d", allocation[i] + 1);
        }
        else
        {
            printf("Not Allocated");
        }
        printf("\n");
    }
}

void worstFit(int m, int processSize[], int n)
{
    int allocation[n];
    int blockSize[] = {128, 256, 150};
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int wstIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }

        if (wstIdx != -1)
        {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }

    printf("\nProcess N\tProcess Size\tBlock n\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
        {
            printf("%d", allocation[i] + 1);
        }
        else
        {
            printf("Not Allocated");
        }
        printf("\n");
    }
}

int main()
{
    int processSize[] = {100, 150, 200};
    int blockSize[] = {128, 256, 150};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);
    printf("Best fit :\n");
    bestFit(m, processSize, n);
    printf("First fit :\n");
    firstFit(m, processSize, n);
    printf("Worst fit :\n");
    worstFit(m, processSize, n);
    return 0;
}
