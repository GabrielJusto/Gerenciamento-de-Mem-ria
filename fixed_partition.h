
#include<stdlib.h>
#include<stdio.h>

struct Partition
{
    int data;
    bool free;
};

struct Partition *MEMORY;
int FREE_SLOTS, PARTITIONS, PART_SIZE;

void init_memory(int memory_size, int partition_size)
{
    PART_SIZE = partition_size;
    PARTITIONS = memory_size/partition_size;
    MEMORY = (struct Partition*)malloc(sizeof(struct Partition)*PARTITIONS);
    FREE_SLOTS = PARTITIONS;

    struct Partition* part_aux = MEMORY;
    for (int i = 0; i < PARTITIONS; i++)
    {
        part_aux->data = 0;
        part_aux->free = true;
        part_aux ++;
    }

}

bool insert_memory(int elem, int size)
{
    if (FREE_SLOTS == 0 || size > PART_SIZE)
    {
         printf("ESPAÇO INSUFICIENTE DE MEMÓRIA ao tentar adicionar o processo %d \n", elem);
         return false;
    }
    struct Partition* part_aux = MEMORY;
    for (int i = 0; i < PARTITIONS; i++)
    {
        if(part_aux->free)
            break;
        part_aux++;
    }
    
    part_aux->free = false;
    part_aux->data = elem;
    return true;
}

void remove_mem(int elem)
{
    struct Partition* part_aux = MEMORY;
    for (int i = 0; i < PARTITIONS; i++)
    {
        if(part_aux->data == elem)
        {
            part_aux->free = false;
            part_aux->data = 0;
        }
        part_aux++;
    }
}

void print_mem()
{
    struct Partition* part_aux = MEMORY;
    printf("\n | ");
    for (int i = 0; i < PARTITIONS; i++)
    {
        if(part_aux->data == 0)
        {
            printf("{%d} ", PART_SIZE);
        }
        else
        {
            printf("%d ", part_aux->data);
        }
        part_aux++;
    }
    printf("| \n");
}