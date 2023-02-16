#include <stdlib.h>   // NULL
#include <sys/mman.h> // mmap()
#include <stdbool.h>  // bool
#include <stdio.h>    // printf

struct block
{
    struct block *next;
    int size;   // bytes
    int in_use; // boolean
};

/**
 *  Allocate a given number of bytes & return a pointer to it.
 */
void *myalloc(int size)
{
    void *heap;
    bool is_first_call = 0;

    if (is_first_call)
    {
        // mmap space
        heap = mmap(
            NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

        // build a linked list node inside new space, indicating size and "in use" status
    }

    // traverse (loop over) linked list
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

void print_data(void)
{
    struct block *b = head;

    if (b == NULL)
    {
        printf("[empty]\n");
        return;
    }

    while (b != NULL)
    {
        // Uncomment the following line if you want to see the pointer values
        printf("[%p:%d,%s]", b, b->size, b->in_use ? "used" : "free");
        // printf("[%d,%s]", b->size, b->in_use ? "used" : "free");
        if (b->next != NULL)
        {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

int main(int argc, char const *argv[])
{
    // allocate space for 5 ints
    int *p = myalloc(sizeof(int) * 5);
    printf("%p\n", p);

    return 0;
}
