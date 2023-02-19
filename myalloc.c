#include "myalloc.h"

struct block *head = NULL;

/**
 *  Allocate a given number of bytes & return a pointer to it.
 */
void *myalloc(int size)
{
    int padded_block_size = PADDED_SIZE(sizeof(struct block));

    // init memory space
    if (head == NULL)
    {
        // mmap space, building a linked list node inside new space
        head = mmap(
            NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        head->next = NULL;
        head->size = 1024 - padded_block_size;
        head->in_use = 0;
    }

    struct block *b = head;

    while (b != NULL) // traverse linked list
    {
        // "first fit" is a node that's not in use & is big enough to hold the padded size
        if (!b->in_use && (b->size >= PADDED_SIZE(size)))
        {
            // found!
            b->in_use = 1;           // mark as "in use"
            return PTR_OFFSET(b, 0); // return pointer to data following node + padding
        }
        b = b->next;
    }
    return NULL; // insufficient memory space
}

/**
 * Free allocated memory of a given pointer.
 */
void myfree(void *p)
{
    return;
}

/**
 * Print allocated memory address space.
 */
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
        // printf("[%p:%d,%s]", b, b->size, b->in_use ? "used" : "free");
        printf("[%d,%s]", b->size, b->in_use ? "used" : "free");
        if (b->next != NULL)
        {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

/**
 * Program entrypoint.
 */
int main(void)
{
    void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);

    return 0;
}
