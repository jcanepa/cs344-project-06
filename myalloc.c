#include <stdlib.h>   // NULL
#include <sys/mman.h> // mmap()
#include <stdbool.h>  // bool
#include <stdio.h>    // printf

#define ALIGNMENT 16 // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x)-1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))

struct block
{
    struct block *next;
    int size;   // bytes
    int in_use; // boolean
};

struct block *head = NULL;

/**
 *  Allocate a given number of bytes & return a pointer to it.
 */
void *myalloc(int size)
{
    if (head == NULL)
    {
        // mmap space
        head = mmap(
            NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

        // build a linked list node inside new space, indicating size and "in use" status
        head->next = NULL;
        head->size = 1024 - PADDED_SIZE(sizeof(struct block));
        head->in_use = 0;
    }

    // traverse linked list
    struct block *node = head;

    while (node != NULL)
    {
        node = node->next;

        if (node->in_use || node->size < size)
            continue;

        // find "first fit":
        // a node that's not "in use" && big enough to hold padded size
        // then
        // mark "in use" &&
        // return pointer to user data after linked list node (+ padding)
        node->in_use = 1;
        return node + sizeof node;
    }

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
