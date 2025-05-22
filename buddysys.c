#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_PROCESSES 100
#define MAX_NAME_LEN 20

typedef struct Node {
    int size;
    int isFree;
    char processName[MAX_NAME_LEN];
    struct Node* left;
    struct Node* right;
} Node;

Node* root = NULL;

// Create a node with given size and mark it free
Node* createNode(int size) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->size = size;
    node->isFree = 1;
    strcpy(node->processName, "-");
    node->left = node->right = NULL;
    return node;
}

// Initialize root
void initBuddySystem(int size) {
    root = createNode(size);
}

// Print the tree recursively
void printTree(Node* node, int level) {
    if (node == NULL) return;

    for (int i = 0; i < level; i++) printf("   ");
    printf("|-- Size: %d, Status: %s", node->size, node->isFree ? "Free" : node->processName);
    if (!node->isFree && strcmp(node->processName, "-") != 0) {
        printf(", Internal Frag: %d", node->size - atoi(node->processName + 1));
    }
    printf("\n");

    printTree(node->left, level + 1);
    printTree(node->right, level + 1);
}

// Check if size is power of 2
int isPowerOfTwo(int n) {
    return (n && !(n & (n - 1)));
}

// Round up to next power of 2
int nextPowerOfTwo(int n) {
    int power = 1;
    while (power < n) power <<= 1;
    return power;
}

// Try to allocate process in the buddy tree
int allocate(Node* node, int reqSize, char* pname) {
    if (node == NULL || !node->isFree || node->size < reqSize)
        return 0;

    if (node->size == reqSize) {
        node->isFree = 0;
        strcpy(node->processName, pname);
        return 1;
    }

    // If node is free but larger, split
    if (node->left == NULL && node->right == NULL) {
        node->left = createNode(node->size / 2);
        node->right = createNode(node->size / 2);
    }

    if (allocate(node->left, reqSize, pname) || allocate(node->right, reqSize, pname)) {
        node->isFree = 0;
        return 1;
    }

    return 0;
}

// Recheck and merge buddies if both are free
void tryMerge(Node* node) {
    if (!node || !node->left || !node->right)
        return;

    tryMerge(node->left);
    tryMerge(node->right);

    if (node->left->isFree && node->right->isFree) {
        free(node->left);
        free(node->right);
        node->left = node->right = NULL;
        node->isFree = 1;
        strcpy(node->processName, "-");
    }
}

// Deallocate process by name
int deallocate(Node* node, char* pname) {
    if (node == NULL)
        return 0;

    if (!node->isFree && strcmp(node->processName, pname) == 0) {
        node->isFree = 1;
        strcpy(node->processName, "-");
        return 1;
    }

    int found = deallocate(node->left, pname) || deallocate(node->right, pname);
    if (found)
        tryMerge(node);

    return found;
}

// Main function
int main() {
    int totalSize, choice;
    char pname[MAX_NAME_LEN];
    int reqSize;

    printf("Enter total memory size (power of 2): ");
    scanf("%d", &totalSize);

    if (!isPowerOfTwo(totalSize)) {
        printf("Size must be power of 2.\n");
        return 1;
    }

    initBuddySystem(totalSize);

    while (1) {
        printf("\n1. Allocate Memory\n2. Deallocate Memory\n3. Show Memory Tree\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter process name (e.g., P128 for 128 bytes): ");
            scanf("%s", pname);
            sscanf(pname + 1, "%d", &reqSize);
            reqSize = nextPowerOfTwo(reqSize);
            if (allocate(root, reqSize, pname))
                printf("Process %s allocated %d bytes.\n", pname, reqSize);
            else
                printf("Allocation failed for %s.\n", pname);
            break;
        case 2:
            printf("Enter process name to deallocate: ");
            scanf("%s", pname);
            if (deallocate(root, pname))
                printf("Process %s deallocated.\n", pname);
            else
                printf("Deallocation failed. Process not found.\n");
            break;
        case 3:
            printf("\nMemory Tree:\n");
            printTree(root, 0);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}


INPUT : Enter total memory size (power of 2): 128

1. Allocate Memory
2. Deallocate Memory
3. Show Memory Tree
4. Exit
Enter your choice: 1
Enter process name (e.g., P128 for 128 bytes): P50
Process P50 allocated 64 bytes.

1. Allocate Memory
2. Deallocate Memory
3. Show Memory Tree
4. Exit
Enter your choice: 