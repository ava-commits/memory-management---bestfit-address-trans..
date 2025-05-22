1 FIRRST FIT

#include <stdio.h>

void firstFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];
    int originalBlockSizes[m]; // for calculating external fragmentation

    // Copy original block sizes
    for (int i = 0; i < m; i++) {
        originalBlockSizes[i] = blockSizes[i];
    }

    // Initialize allocation as -1 (not allocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // First Fit allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                allocation[i] = j;
                blockSizes[j] -= processSizes[i];
                break;
            }
        }
    }

    // Display allocation
    printf("\n--- First Fit Allocation ---\n");
    printf("Process No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); // Block number (1-based)
        else
            printf("Not Allocated\n");
    }

    // Display remaining memory in each block
    printf("\nRemaining Memory in Each Block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: %d\n", i + 1, blockSizes[i]);
    }

    // Calculate and display external fragmentation
    int totalFreeMemory = 0;
    for (int i = 0; i < m; i++) {
        totalFreeMemory += blockSizes[i];
    }

    int totalUnallocatedProcessSize = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1)
            totalUnallocatedProcessSize += processSizes[i];
    }

    printf("\nTotal Free Memory: %d\n", totalFreeMemory);
    printf("Total Unallocated Process Memory: %d\n", totalUnallocatedProcessSize);

    if (totalUnallocatedProcessSize > 0 && totalFreeMemory >= totalUnallocatedProcessSize)
        printf("External Fragmentation Exists.\n");
    else if (totalUnallocatedProcessSize > 0)
        printf("Process(es) could not be allocated due to insufficient contiguous space.\n");
    else
        printf("No External Fragmentation.\n");

    printf("\nNote: There is NO Internal Fragmentation in First Fit.\n");
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSizes[m];
    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSizes[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSizes[n];
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSizes[i]);
    }

    firstFit(blockSizes, m, processSizes, n);

    return 0;
}

INPUT :

Enter number of memory blocks: 5
Enter sizes of memory blocks:
100 500 200 300 600
Enter number of processes: 4
Enter sizes of processes:
212 417 112 426

2 NEXT FIT 

#include <stdio.h>

void nextFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n]; // Block allocated to each process
    int originalBlockSizes[m]; // Copy of original block sizes for reporting

    // Store original block sizes
    for (int i = 0; i < m; i++) {
        originalBlockSizes[i] = blockSizes[i];
    }

    int lastAllocated = 0;

    // Initialize allocations as -1 (not allocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Allocation using Next Fit strategy
    for (int i = 0; i < n; i++) {
        int count = 0;
        int allocated = 0;
        int index = lastAllocated;

        while (count < m) {
            if (blockSizes[index] >= processSizes[i]) {
                allocation[i] = index;
                blockSizes[index] -= processSizes[i];
                lastAllocated = index;
                allocated = 1;
                break;
            }
            index = (index + 1) % m;
            count++;
        }
    }

    // Output Allocation Results
    printf("\n--- Next Fit Allocation ---\n");
    printf("Process No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); // 1-based index
        else
            printf("Not Allocated\n");
    }

    // Output Remaining Memory in Blocks
    printf("\nRemaining Memory in Each Block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: %d\n", i + 1, blockSizes[i]);
    }

    // External Fragmentation Calculation
    int totalFree = 0;
    for (int i = 0; i < m; i++) {
        totalFree += blockSizes[i];
    }

    int totalUnallocated = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1)
            totalUnallocated += processSizes[i];
    }

    printf("\nTotal Free Memory: %d\n", totalFree);
    printf("Total Unallocated Process Memory: %d\n", totalUnallocated);

    if (totalUnallocated > 0 && totalFree >= totalUnallocated)
        printf("External Fragmentation Exists.\n");
    else if (totalUnallocated > 0)
        printf("Processes could not be allocated due to insufficient contiguous space.\n");
    else
        printf("No External Fragmentation.\n");

    printf("\nNote: There is NO Internal Fragmentation in Next Fit.\n");
}

int main() {
    int m, n;

    // Input memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSizes[m];
    printf("Enter sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSizes[i]);
    }

    // Input processes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSizes[n];
    printf("Enter sizes of the processes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSizes[i]);
    }

    nextFit(blockSizes, m, processSizes, n);
    return 0;
}
 
INPUT

Enter number of memory blocks: 5
Enter sizes of the memory blocks:
100 500 200 300 600
Enter number of processes: 4
Enter sizes of the processes:
212 417 112 426


3 BEST FIT

#include <stdio.h>
#include <limits.h> // For INT_MAX

void bestFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];          // Block allocated to each process
    int originalBlockSizes[m];  // Copy of original block sizes

    // Store original block sizes for display later
    for (int i = 0; i < m; i++) {
        originalBlockSizes[i] = blockSizes[i];
    }

    // Initialize all allocations to -1 (not allocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Allocate using Best Fit strategy
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (bestIdx == -1 || blockSizes[j] < blockSizes[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSizes[bestIdx] -= processSizes[i];
        }
    }

    // Display allocation results
    printf("\n--- Best Fit Allocation ---\n");
    printf("Process No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);  // 1-based index
        else
            printf("Not Allocated\n");
    }

    // Show remaining memory in each block
    printf("\nRemaining Memory in Each Block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: %d\n", i + 1, blockSizes[i]);
    }

    // External Fragmentation Calculation
    int totalFree = 0;
    for (int i = 0; i < m; i++) {
        totalFree += blockSizes[i];
    }

    int totalUnallocated = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1)
            totalUnallocated += processSizes[i];
    }

    printf("\nTotal Free Memory: %d\n", totalFree);
    printf("Total Unallocated Process Memory: %d\n", totalUnallocated);

    if (totalUnallocated > 0 && totalFree >= totalUnallocated)
        printf("External Fragmentation Exists.\n");
    else if (totalUnallocated > 0)
        printf("Processes could not be allocated due to insufficient contiguous space.\n");
    else
        printf("No External Fragmentation.\n");

    printf("\nNote: There is NO Internal Fragmentation in Best Fit.\n");
}

int main() {
    int m, n;

    // Input memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSizes[m];
    printf("Enter sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSizes[i]);
    }

    // Input processes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSizes[n];
    printf("Enter sizes of the processes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSizes[i]);
    }

    bestFit(blockSizes, m, processSizes, n);
    return 0;
}

INPUT:

Enter number of memory blocks: 5
Enter sizes of the memory blocks:
100 500 200 300 600
Enter number of processes: 4
Enter sizes of the processes:
212 417 112 426


4 WORST FIT

#include <stdio.h>

void worstFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];          // Block allocated to each process
    int originalBlockSizes[m];  // Copy original block sizes

    // Save original block sizes for reporting
    for (int i = 0; i < m; i++) {
        originalBlockSizes[i] = blockSizes[i];
    }

    // Initialize all allocations to -1 (not allocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Allocate memory using Worst Fit
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (worstIdx == -1 || blockSizes[j] > blockSizes[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSizes[worstIdx] -= processSizes[i];
        }
    }

    // Display allocation results
    printf("\n--- Worst Fit Allocation ---\n");
    printf("Process No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    // Show remaining memory in each block
    printf("\nRemaining Memory in Each Block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: %d\n", i + 1, blockSizes[i]);
    }

    // Calculate external fragmentation
    int totalFree = 0;
    for (int i = 0; i < m; i++) {
        totalFree += blockSizes[i];
    }

    int totalUnallocated = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1)
            totalUnallocated += processSizes[i];
    }

    printf("\nTotal Free Memory: %d\n", totalFree);
    printf("Total Unallocated Process Memory: %d\n", totalUnallocated);

    if (totalUnallocated > 0 && totalFree >= totalUnallocated)
        printf("External Fragmentation Exists.\n");
    else if (totalUnallocated > 0)
        printf("Processes could not be allocated due to insufficient contiguous space.\n");
    else
        printf("No External Fragmentation.\n");

    printf("\nNote: There is NO Internal Fragmentation in Worst Fit.\n");
}

int main() {
    int m, n;

    // Input memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSizes[m];
    printf("Enter sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSizes[i]);
    }

    // Input processes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSizes[n];
    printf("Enter sizes of the processes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSizes[i]);
    }

    worstFit(blockSizes, m, processSizes, n);
    return 0;
}

INPUT :
Enter number of memory blocks: 5
Enter sizes of the memory blocks:
100 500 200 300 600
Enter number of processes: 4
Enter sizes of the processes:
212 417 112 426
