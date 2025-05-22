SINGLE SINGLE CODES

Page Replacement: 
FIFO: 
#include <stdio.h> 
#define MAX_FRAMES 10 
#define MAX_PAGES 20 
void FIFO(int pages[], int numPages, int numFrames) { 
    int frames[MAX_FRAMES]; 
    int pageFaults = 0; 
    int nextFrame = 0; 
       // Initialize frames to -1, meaning empty 
    for (int i = 0; i < numFrames; i++) { 
        frames[i] = -1; 
    } 
   // Iterate over the page reference string 
    for (int i = 0; i < numPages; i++) { 
        int page = pages[i]; 
        int pageFound = 0; 
 // Check if the page is already in the frame (hit) 
        for (int j = 0; j < numFrames; j++) { 
            if (frames[j] == page) { 
                pageFound = 1; 
                break; 
            } 
        } 
      // If the page was not found in the frames, it's a page fault 
        if (!pageFound) { 
            // Replace the oldest page (FIFO) 
            frames[nextFrame] = page; 
            nextFrame = (nextFrame + 1) % numFrames; 
            pageFaults++; 
// Print the current state of the frames after replacement 
            printf("Page %d inserted, Frames: ", page); 
            for (int j = 0; j < numFrames; j++) { 
                if (frames[j] == -1) { 
                    printf("empty "); 
                } else { 
                    printf("%d ", frames[j]); 
                } 
            } 
            printf("\n"); 
        } 
    } 
printf("Total page faults: %d\n", pageFaults); 
} 
int main() { 
int pages[MAX_PAGES]; 
int numPages, numFrames; 
printf("Enter number of pages: "); 
scanf("%d", &numPages); 
printf("Enter page reference string:\n"); 
for (int i = 0; i < numPages; i++) { 
scanf("%d", &pages[i]); 
} 
printf("Enter number of frames: "); 
scanf("%d", &numFrames); 
FIFO(pages, numPages, numFrames); 
return 0; 
} 


Optimal Page replacement: 

#include <stdio.h> 
#include <stdlib.h> 
 
#define MAX_FRAMES 10 
#define MAX_PAGES 100 
 
// Function to find the index of the page that will not be used for the longest time in future 
int findOptimal(int frames[], int n, int page[], int currPos, int totalPages) { 
    int farthest = currPos; 
    int indexToReplace = -1; 
     
    // Check all pages in memory 
    for (int i = 0; i < n; i++) { 
        int j; 
        for (j = currPos; j < totalPages; j++) { 
            if (frames[i] == page[j]) { 
                if (j > farthest) { 
                    farthest = j; 
                    indexToReplace = i; 
                } 
                break; 
            } 
        } 
        // If page is not found in future, it will be replaced 
        if (j == totalPages) { 
            return i; 
        } 
    } 
     
    return indexToReplace; 
} 
 
// Function to implement Optimal page replacement 
void optimalPageReplacement(int page[], int totalPages, int n) { 
    int frames[MAX_FRAMES]; 
    int pageFaults = 0; 
    int hit = 0; 
 
    // Initialize frames as empty 
    for (int i = 0; i < n; i++) { 
        frames[i] = -1; 
    } 
 
    for (int i = 0; i < totalPages; i++) { 
        int found = 0; 
         
        // Check if page is already in frames 
        for (int j = 0; j < n; j++) { 
            if (frames[j] == page[i]) { 
                found = 1; 
                hit = 1; 
                break; 
            } 
        } 
 
        // If page is not in frames, replace a page 
        if (!found) { 
            // Find the index to replace using the Optimal strategy 
            int replaceIndex = findOptimal(frames, n, page, i + 1, totalPages); 
            frames[replaceIndex] = page[i]; 
            pageFaults++; 
        } 
 printf("Frames: "); 
        for (int j = 0; j < n; j++) { 
            if (frames[j] != -1) 
                printf("%d ", frames[j]); 
        } 
        if (!hit) { 
            printf("(Page fault!)\n"); 
        } else { 
            printf("(Page hit!)\n"); 
        } 
        hit = 0; 
    } 
 
    printf("Total page faults: %d\n", pageFaults); 
} 
 
int main() { 
    int page[MAX_PAGES], totalPages, n; 
 
    // Take the input from the user for page reference string and the number of frames 
    printf("Enter the number of frames: "); 
    scanf("%d", &n); 
 
    printf("Enter the total number of page references: "); 
    scanf("%d", &totalPages); 
 
    printf("Enter the page reference string:\n"); 
    for (int i = 0; i < totalPages; i++) { 
        scanf("%d", &page[i]); 
    } 
// Call the Optimal Page Replacement function 
optimalPageReplacement(page, totalPages, n); 
return 0; 
} 


LRU: 


#include <stdio.h> 
#define MAX_FRAMES 10 
#define MAX_PAGES 25  // Define the maximum number of pages 
// Function to simulate LRU page replacement 
void lruPageReplacement(int pages[], int numPages, int numFrames) { 
int memory[MAX_FRAMES];   // To store frames in memory 
int pageFaults = 0; 
int i, j, k; 
// Initialize memory with -1 (empty frames) 
    for (i = 0; i < numFrames; i++) { 
        memory[i] = -1; 
    } 
 
    // Iterate through the page reference string 
    for (i = 0; i < numPages; i++) { 
        int page = pages[i]; 
        int found = 0; 
 
        // Check if the page is already in memory (no page fault) 
        for (j = 0; j < numFrames; j++) { 
            if (memory[j] == page) { 
                found = 1; 
                break; 
            } 
        } 
 
        // If page is not in memory (page fault) 
        if (!found) { 
            pageFaults++; 
 
            // If memory is full, remove the least recently used page 
            for (k = 0; k < numFrames - 1; k++) { 
                memory[k] = memory[k + 1]; 
            } 
 
            // Insert the new page at the last position in memory 
            memory[numFrames - 1] = page; 
        } 
 
        // Display the current memory content after every page reference 
        printf("Memory after %d page(s): ", i + 1); 
        for (j = 0; j < numFrames; j++) { 
            if (memory[j] != -1) { 
                printf("%d ", memory[j]); 
            } 
        } 
        printf("\n"); 
    } 
 
    // Print the total page faults 
    printf("Total Page Faults: %d\n", pageFaults); 
} 
 
int main() { 
    int numPages, numFrames; 
 
    // Take input from the user for number of frames 
    printf("Enter the number of frames: "); 
    scanf("%d", &numFrames); 
    if (numFrames > MAX_FRAMES) { 
        printf("Max frames allowed are %d. Setting frames to %d.\n", MAX_FRAMES, MAX_FRAMES); 
        numFrames = MAX_FRAMES; 
    } 
 
    // Take input for the page reference string 
    printf("Enter the number of pages (max %d): ", MAX_PAGES); 
    scanf("%d", &numPages); 
    if (numPages > MAX_PAGES) { 
        printf("Max pages allowed are %d. Setting pages to %d.\n", MAX_PAGES, MAX_PAGES); 
        numPages = MAX_PAGES; 
    } 
int pages[numPages]; 
printf("Enter the page reference string (space-separated):\n"); 
for (int i = 0; i < numPages; i++) { 
scanf("%d", &pages[i]); 
} 
// Call the LRU page replacement function 
lruPageReplacement(pages, numPages, numFrames); 
return 0; 
}