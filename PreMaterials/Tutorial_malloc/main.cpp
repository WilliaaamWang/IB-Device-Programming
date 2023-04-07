#include "mbed.h"

void basics()
{
    // The function malloc (memory allocation) takes as input the size in bytes you wish to allocate in memory and returns a pointer of type void *
    // which points to the first byte of memory
    void *p = malloc(10); // Allocates 10 bytes; p points to the first byte

    // Memory reallocation
    // If we have some created memory, we can grow it with the function realloc
    // Takes as input a pointer to the first byte of an existing memory allocation and a desired new size of this memory allocation
    // and returns a pointer of type void * which points to the first byte of the new memory allocation
    void *np = realloc(p, 20);
    // The new pointer np points to the first byte of this new memory allocation.
    // The old content is preserved in te new memor location
    // Old pointer p now points to an invalid memory area and is often set to NULL to signal that does no longer point to anything useful
    p = NULL;
    // This is known as a null pointer. If p was not set to NULL it would be known as a dangling pointer. These are very dangerous as any attempt to dereference
    // them or use them in any other way results in undefined beaviour

    // Freeing allocated memory
    // We will need to return the memory to system. Failing to do so means we haave introduced a memory leak.
    // To free te new pointer np we use free() and set pointer to NULL
    free(np);
    np = NULL;
}

// Checking successful malloc
// realloc() can fail to reallocate memory, e.g. due to no memory being available. It's good practice to verify that the returned pointer is NOT NULL.
// If realloc() fails then the original pointer still points to a valid memory location and will need to be freed manually.
void check()
{
    void *p = malloc(10);
    // int *p = (int *) malloc(sizeof(int)*8);
    void *np = realloc(p, 20);
    if (np == NULL) {
        free(p);
        // Insert code to handle memory allocation failure...
    }
    /*
    To use malloc in practice, it is useful to transform the pointer of type void * to something more useful.
    For example, if we want to allocate memory for storing integers then we would like the pointer to be of type int*
    We would also like the memory to be allocated so that a particular number of integers fit within the allocated memory area
    Therefore in practice to allocate memory for 8 integers we could write:
    */
    int *pp = (int *) malloc(sizeof(int)*8);
    // The sizeof() operator returns the size of type int (4bytes) which we then multiply by 8.
    // The (int ) part before malloc is known as *casting. The casting operator changes the retun type of malloc from void * (a pointer to any type)
    // to int * (a pointer to an integer)
    // Having allocated the memory and cast the returned pointer to a pointer of type int *, we can now read and write to the memory area by dereferencing the pointer:
    int *xp = pp;
    *xp = 16; // Set first integer in memory area to 16
    xp++; // Proceed to the next integer in the allocated memory area
    *xp = 32; // Set the second integer in the memory area to 32

    // We can also use array operations on our newly allocated memory area, as arrays in C/++ are essentially the same as allocated memory area
    // with a fixed type (note however that pointers to arrays cannot be modified by calling malloc, realloc and free as they are no dynamically allocated by system)
    printf("First integer: %d\r\n", pp[0]);
    printf("Second integer: %d\r\n", pp[1]);
}


int main()
{
        int *p = (int *)malloc(sizeof(int)*4);
        int *xp = p;
        *xp = 2;
        xp++;
        *xp = 4;
        xp++;
        *xp = 8;
        xp++;
        *xp = 16;

        for (int i = 0; i < 4; i++) {
                printf("[%d]: %d\r\n", i, p[i]);
        }

        int *np = (int *)realloc(p, sizeof(int)*16);
        if (np == NULL) {
                free(p);
                printf("Memory allocation failure!\r\n");
        }
        else {
                for (int i = 4; i < 16; i++) {
                        np[i] = 255;
                }
                for (int i = 0; i < 16; i++) {
                        printf("[%d]: %d\r\n", i, np[i]);
                }
                free(np);
        }
}