#include <stdlib.h>
/**
 *  Allocate a given number of bytes & return a pointer to it.
 */
void *myalloc(int size)
{
    // if this is the first call
    // mmap space
    // build a linked list node inside new space, indicating size and "in use" status

    // traverse linked list (loop)
    // find first node not "in use"
    // &&
    // is big enough to hold given size + padding

    // if found
    // mark "in use"
    // return pointer to user data after linked list node (+ padding)
    return NULL;
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
    return 0;
}
