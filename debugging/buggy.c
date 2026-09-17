#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int sum = 0;
    
    printf("Calculating sum of array...\n");
    
    // BUG 1: Out of bounds read. We are reading 10 elements instead of 5.
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    
    printf("Total sum is: %d\n", sum);
    
    // BUG 2: Null pointer dereference (Causes Segmentation Fault)
    printf("Attempting to write to pointer...\n");
    int *ptr = NULL;
    *ptr = 100;
    
    printf("Program finished successfully!\n");
    return 0;
}
