#include <stdlib.h>   // NULL
#include <sys/mman.h> // mmap()
#include <stdbool.h>  // bool
#include <stdio.h>    // printf

#define ALIGNMENT 16 // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x)-1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void *)((char *)(p) + (offset)))

struct block
{
    struct block *next;
    int size;   // bytes
    int in_use; // boolean
};

struct block *head = NULL;
padded_block_size = PADDED_SIZE(sizeof(struct block));

/**
 *  Allocate a given number of bytes & return a pointer to it.
 */
void *myalloc(int size)
{
    struct block *b = head;

    // initial call
    if (b == NULL)
    {
        // mmap space
        head = mmap(
            NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

        // build a linked list node inside new space
        head->next = NULL;
        head->size = 1024 - padded_block_size;
        head->in_use = 0;
    }

    // traverse linked list
    // find "first fit":
    // a current that's not "in use" && is big enough to hold padded size
    // then...
    // mark current as "in use" &&
    // return pointer to user data after linked list current (+ padding)
    while (b != NULL)
    {
        b = b->next;

        if (b->next == NULL)
            continue;

        if (b->in_use || b->size < size)
            continue;

        b->in_use = 1;
        return PTR_OFFSET(b, padded_block_size);
    }

    // no room
    return NULL;
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

int main(int argc, char const *argv[])
{
    void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);

    return 0;
}
