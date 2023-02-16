#include <stdlib.h>   // NULL
#include <sys/mman.h> // mmap()
/**
 *  Allocate a given number of bytes & return a pointer to it.
 */
void *myalloc(int size)
{
    void *heap;

    // if this is the first call
    // mmap space
    // build a linked list node inside new space, indicating size and "in use" status
    if (0)
        heap = mmap(
            NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    // traverse linked list (loop)
    // find first node not "in use"
    // &&
    // big enough to hold given size + padding

    // if found
    // mark "in use"
    // return pointer to user data after linked list node (+ padding)

    // else return NULL
    return ((void *)0);
}

/**
 * Free allocated memory of a given pointer.
 */
void myfree(void *p)
{
    return;
}

int main(int argc, char const *argv[])
{
    // allocate space for 5 ints
    int *p = myalloc(sizeof(int) * 5);
    return 0;
}
