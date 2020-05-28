#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main()
{
    initList();
    insert(1, 0);
    // printf("%d", SIZE);
    insert(2, 1);
    insert(3, 2);
    insert(4,1);
    insert(4,1);
    insert_end(5);
    removeList(SIZE-1);

    printList();

}