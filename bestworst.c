#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

struct Block {
    int id;
    int original_size;
    int remaining_size;
    int allocated_process; // -1 means free
};

void resetBlocks(struct Block dest[], struct Block src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void printAllocation(struct Block blocks[], int n, bool process_allocated[], int m, int process[], const char* strategy) {
    printf("\n%s Allocation Result:\n", strategy);
    printf("Block ID\tOriginal Size\tRemaining\tAllocated Process\n");
    int total_free_memory = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t", blocks[i].id, blocks[i].original_size, blocks[i].remaining_size);
        if (blocks[i].allocated_process == -1)
            printf("Free\n");
        else
            printf("Process %d\n", blocks[i].allocated_process);
        total_free_memory += blocks[i].remaining_size;
    }

    printf("\nUnallocated Processes (due to external fragmentation):\n");
    bool any_unallocated = false;
    for (int i = 0; i < m; i++) {
        if (!process_allocated[i]) {
            printf("Process %d (Size %d)\n", i, process[i]);
            any_unallocated = true;
        }
    }

    if (!any_unallocated)
        printf("None\n");

    printf("\nTotal Remaining Memory: %d\n", total_free_memory);
    printf("Fragmentation Type: External (not internal, since no splitting occurs)\n");
}

void firstFit(struct Block blocks[], int n, int process[], int m, bool process_allocated[]) {
    for (int i = 0; i < m; i++) {
        process_allocated[i] = false;
        for (int j = 0; j < n; j++) {
            if (blocks[j].allocated_process == -1 && blocks[j].remaining_size >= process[i]) {
                blocks[j].allocated_process = i;
                blocks[j].remaining_size -= process[i];
                process_allocated[i] = true;
                break;
            }
        }
    }
}

void nextFit(struct Block blocks[], int n, int process[], int m, bool process_allocated[]) {
    int last_pos = 0;
    for (int i = 0; i < m; i++) {
        process_allocated[i] = false;
        int count = 0;
        int j = last_pos;
        while (count < n) {
            if (blocks[j].allocated_process == -1 && blocks[j].remaining_size >= process[i]) {
                blocks[j].allocated_process = i;
                blocks[j].remaining_size -= process[i];
                process_allocated[i] = true;
                last_pos = (j + 1) % n;
                break;
            }
            j = (j + 1) % n;
            count++;
        }
    }
}

void bestFit(struct Block blocks[], int n, int process[], int m, bool process_allocated[]) {
    for (int i = 0; i < m; i++) {
        int best_idx = -1;
        int min_remain = 999999;
        process_allocated[i] = false;
        for (int j = 0; j < n; j++) {
            if (blocks[j].allocated_process == -1 && blocks[j].remaining_size >= process[i]) {
                int remain = blocks[j].remaining_size - process[i];
                if (remain < min_remain) {
                    min_remain = remain;
                    best_idx = j;
                }
            }
        }
        if (best_idx != -1) {
            blocks[best_idx].allocated_process = i;
            blocks[best_idx].remaining_size -= process[i];
            process_allocated[i] = true;
        }
    }
}

void worstFit(struct Block blocks[], int n, int process[], int m, bool process_allocated[]) {
    for (int i = 0; i < m; i++) {
        int worst_idx = -1;
        int max_remain = -1;
        process_allocated[i] = false;
        for (int j = 0; j < n; j++) {
            if (blocks[j].allocated_process == -1 && blocks[j].remaining_size >= process[i]) {
                int remain = blocks[j].remaining_size - process[i];
                if (remain > max_remain) {
                    max_remain = remain;
                    worst_idx = j;
                }
            }
        }
        if (worst_idx != -1) {
            blocks[worst_idx].allocated_process = i;
            blocks[worst_idx].remaining_size -= process[i];
            process_allocated[i] = true;
        }
    }
}

int main() {
    int n, m;
    struct Block blocks[MAX_BLOCKS], backup_blocks[MAX_BLOCKS];
    int process[MAX_PROCESSES];
    bool process_allocated[MAX_PROCESSES];

    printf("Enter number of memory blocks: ");
    scanf("%d", &n);
    printf("Enter size of each memory block:\n");
    for (int i = 0; i < n; i++) {
        blocks[i].id = i;
        printf("Block %d: ", i);
        scanf("%d", &blocks[i].original_size);
        blocks[i].remaining_size = blocks[i].original_size;
        blocks[i].allocated_process = -1;
    }

    // Make backup
    for (int i = 0; i < n; i++)
        backup_blocks[i] = blocks[i];

    printf("Enter number of processes: ");
    scanf("%d", &m);
    printf("Enter size of each process:\n");
    for (int i = 0; i < m; i++) {
        printf("Process %d: ", i);
        scanf("%d", &process[i]);
    }

    // First Fit
    printf("\n=== First Fit ===\n");
    resetBlocks(blocks, backup_blocks, n);
    firstFit(blocks, n, process, m, process_allocated);
    printAllocation(blocks, n, process_allocated, m, process, "First Fit");

    // Next Fit
    printf("\n=== Next Fit ===\n");
    resetBlocks(blocks, backup_blocks, n);
    nextFit(blocks, n, process, m, process_allocated);
    printAllocation(blocks, n, process_allocated, m, process, "Next Fit");

    // Best Fit
    printf("\n=== Best Fit ===\n");
    resetBlocks(blocks, backup_blocks, n);
    bestFit(blocks, n, process, m, process_allocated);
    printAllocation(blocks, n, process_allocated, m, process, "Best Fit");

    // Worst Fit
    printf("\n=== Worst Fit ===\n");
    resetBlocks(blocks, backup_blocks, n);
    worstFit(blocks, n, process, m, process_allocated);
    printAllocation(blocks, n, process_allocated, m, process, "Worst Fit");

    return 0;
}

INPUT :
 Enter number of memory blocks: 5
Enter size of each memory block:
Block 0: 100
Block 1: 500
Block 2: 200
Block 3: 300
Block 4: 600
Enter number of processes: 4
Enter size of each process:
Process 0: 212
Process 1: 417
Process 2: 112
Process 3: 426