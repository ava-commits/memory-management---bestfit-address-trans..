#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void printFrames(int frames[], int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

void FIFO(int pages[], int n, int capacity) {
    printf("\n--- FIFO Page Replacement ---\n");
    int frames[capacity];
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    int index = 0, page_faults = 0;

    printf("\nRef\tFrames\t\tPage Fault\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        // Check if page is already in frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        printf("%d\t", pages[i]);
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % capacity;
            page_faults++;
            printFrames(frames, capacity);
            printf("\tPage Fault Occurred\n");
        } else {
            printFrames(frames, capacity);
            printf("\tNo Page Fault\n");
        }
    }
    printf("\nTotal Page Faults using FIFO = %d\n", page_faults);
}

int findLRU(int time[], int capacity) {
    int min = time[0], pos = 0;
    for (int i = 1; i < capacity; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void LRU(int pages[], int n, int capacity) {
    printf("\n--- LRU Page Replacement ---\n");
    int frames[capacity], time[capacity];
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    int counter = 0, page_faults = 0;

    printf("\nRef\tFrames\t\tPage Fault\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        printf("%d\t", pages[i]);
        if (!found) {
            int pos = -1;
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) pos = findLRU(time, capacity);

            frames[pos] = pages[i];
            counter++;
            time[pos] = counter;
            page_faults++;
            printFrames(frames, capacity);
            printf("\tPage Fault Occurred\n");
        } else {
            printFrames(frames, capacity);
            printf("\tNo Page Fault\n");
        }
    }
    printf("\nTotal Page Faults using LRU = %d\n", page_faults);
}

int predict(int pages[], int frames[], int n, int index, int capacity) {
    int farthest = index, res = -1;
    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void Optimal(int pages[], int n, int capacity) {
    printf("\n--- Optimal Page Replacement ---\n");
    int frames[capacity];
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    int page_faults = 0;

    printf("\nRef\tFrames\t\tPage Fault\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        printf("%d\t", pages[i]);
        if (!found) {
            int pos = -1;
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = predict(pages, frames, n, i + 1, capacity);

            frames[pos] = pages[i];
            page_faults++;
            printFrames(frames, capacity);
            printf("\tPage Fault Occurred\n");
        } else {
            printFrames(frames, capacity);
            printf("\tNo Page Fault\n");
        }
    }
    printf("\nTotal Page Faults using Optimal = %d\n", page_faults);
}

int main() {
    int n, capacity;
    int pages[MAX];

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);
    Optimal(pages, n, capacity);

    return 0;
}

OUTPUT : 
Enter number of pages in reference string: 12
Enter the reference string:
7 0 1 2 0 3 0 4 2 3 0 3
Enter number of frames: 3

--- FIFO Page Replacement ---

Ref	Frames		Page Fault
7	7 - - 
	Page Fault Occurred
0	7 0 - 
	Page Fault Occurred
1	7 0 1 
	Page Fault Occurred
2	2 0 1 
	Page Fault Occurred
0	2 0 1 
	No Page Fault
3	2 3 1 
	Page Fault Occurred
0	2 3 0 
	Page Fault Occurred
4	4 3 0 
	Page Fault Occurred
2	4 2 0 
	Page Fault Occurred
3	4 2 3 
	Page Fault Occurred
0	0 2 3 
	Page Fault Occurred
3	0 2 3 
	No Page Fault

Total Page Faults using FIFO = 10

--- LRU Page Replacement ---

Ref	Frames		Page Fault
7	7 - - 
	Page Fault Occurred
0	7 0 - 
	Page Fault Occurred
1	7 0 1 
	Page Fault Occurred
2	2 0 1 
	Page Fault Occurred
0	2 0 1 
	No Page Fault
3	2 0 3 
	Page Fault Occurred
0	2 0 3 
	No Page Fault
4	4 0 3 
	Page Fault Occurred
2	4 0 2 
	Page Fault Occurred
3	4 3 2 
	Page Fault Occurred
0	0 3 2 
	Page Fault Occurred
3	0 3 2 
	No Page Fault

Total Page Faults using LRU = 9

--- Optimal Page Replacement ---

Ref	Frames		Page Fault
7	7 - - 
	Page Fault Occurred
0	7 0 - 
	Page Fault Occurred
1	7 0 1 
	Page Fault Occurred
2	2 0 1 
	Page Fault Occurred
0	2 0 1 
	No Page Fault
3	2 0 3 
	Page Fault Occurred
0	2 0 3 
	No Page Fault
4	2 4 3 
	Page Fault Occurred
2	2 4 3 
	No Page Fault
3	2 4 3 
	No Page Fault
0	0 4 3 
	Page Fault Occurred
3	0 4 3 
	No Page Fault

Total Page Faults using Optimal = 7
