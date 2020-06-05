/*
------------------------------------------------------
Gabriel Bonatto Justo - gabriel.justo@acad.pucrs.br
Gabriel Pereira Paiz - gabriel.paiz@edu.pucrs.br
------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




typedef struct Node
{
    struct Node* prev;
    struct Node* next;
    int size;
    int data;
    bool free;
}Node;

struct Node* HEADER;//Inicio da lista
struct Node* TAIL;//Fim da lista
struct Node* NEXT_FIT_PT;
int NEXT_COUNT;
int SIZE; //Tamanho da Lista
bool INITIATED = false; //Evita que a lista seja iniciada mais de uma vez
int FREE_SPACE; //total de espaço livre na memória


/*
----------------------------------------------
initList()
Inicia a lista
Entradas:
    size: Tamanho da memória
Saída:
    se a lista foi criada retirna "true"
    se a lista não foi criada retorna "false"
----------------------------------------------
*/
bool initList(int size)
{
    if (INITIATED) 
        return false;
    HEADER = (Node*)malloc(sizeof(Node));
    HEADER->size = size;
    HEADER->free = true;
    TAIL = HEADER;
    SIZE = 1;
    INITIATED = true;
    FREE_SPACE = size;
    NEXT_FIT_PT = HEADER;
    NEXT_COUNT = 0;
    return true;
}


bool insert_mem(struct Node *node_free, struct Node *new_node, int pos)
{
    
    int size = new_node->size;
    int elem = new_node->data;
     if(pos == -1)//não encontrou nenhum espaço
    {
        printf("foi aqui \n");
        // printf("elem %d, size %d, aux %d, aux_size %d \n", elem, size,node_aux->data, node_aux->size);
        printf("ESPAÇO INSUFICIENTE DE MEMÓRIA ao tentar adicionar o processo %d \n", elem);
        return false;
    }

    if(pos == 0 && HEADER->size == size)
    {       
        new_node->next = HEADER->next;
        HEADER->next->prev = new_node;
        HEADER = new_node;
        FREE_SPACE -= size;
        HEADER->free = false;
        node_free->free = false;
        return true;
    }
    
     if (pos == SIZE-1)
    {

        if (node_free->size - size != 0)
            TAIL->size -= new_node->size;
               
        new_node->prev = TAIL;
        TAIL->next = new_node;
        TAIL = new_node;
        TAIL->free = false;


        SIZE ++;
        FREE_SPACE -= size;
        printf("eh tail \n");
        return true;
    }

    if (node_free->size - size == 0)
    {
        node_free->data = new_node->data;
        node_free->free = false;
        FREE_SPACE -= size;
        return true;
    }

    
    new_node->next = node_free->next;
    new_node->prev = node_free;
    node_free->next = new_node;
    new_node->next->prev = new_node;
    node_free->size -= new_node->size;
    
    SIZE++;
    FREE_SPACE -= size;

   return true;
}

bool insert_next_fit(int elem, int size)
{
    if (size > FREE_SPACE)
    {
        printf("ESPAÇO INSUFICIENTE DE MEMÓRIA ao tentar adicionar o processo %d \n", elem);
        return false;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->size = size;
    new_node->free = false;
    new_node->data = elem;

    if (SIZE == 1)
    {
        new_node->prev = HEADER;
        HEADER->next = new_node;
        HEADER->size -= new_node->size;
        TAIL = new_node;
        SIZE++;
        FREE_SPACE -= size;
        return true;        
    }

    struct Node* node_aux = NEXT_FIT_PT;
    int count = -1;
    for (int i = 0; i < SIZE-1; i++)
    {   
        // printf("next: %d, count: %d, next->free %d, next->size %d \n", NEXT_FIT_PT->data, NEXT_COUNT, NEXT_FIT_PT->free, NEXT_FIT_PT->size);
        // printf("aux: %d, count: %d, aux->free %d, aux->size %d \n", node_aux->data, NEXT_COUNT, node_aux->free, node_aux->size);
        // printf("SIZE %d \n", SIZE);
        // printf("size %d \n", size);
        // printf("i %d \n", i);

        if (node_aux->free && node_aux->size >= size)
        {
            
            NEXT_FIT_PT = node_aux;
            count = NEXT_COUNT;
            break;
        }
        
        
        if (NEXT_COUNT == SIZE-1)
        {
            // printf("entrei qui %d \n", NEXT_COUNT);
            node_aux = HEADER;
            NEXT_COUNT = 0;
        }else
        {
            node_aux = node_aux->next;
            NEXT_COUNT ++;     
        }  
         
    
    }
    printf("passei do if\n");
    insert_mem(NEXT_FIT_PT, new_node, count);

}
bool insert_first_fit(int elem, int size)
{
    if (size > FREE_SPACE)
    {
        printf("ESPAÇO INSUFICIENTE DE MEMÓRIA ao tentar adicionar o processo %d \n", elem);
        return false;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->size = size;
    new_node->free = false;
    new_node->data = elem;

    if (SIZE == 1)
    {
        new_node->prev = HEADER;
        HEADER->next = new_node;
        HEADER->size -= new_node->size;
        TAIL = new_node;
        SIZE++;
        FREE_SPACE -= size;
        return true;        
    }

    struct Node* node_aux = HEADER;
    struct Node* first_node = node_aux;

    int count = -1;
    for (int i = 0; i < SIZE-1; i++)
    {   
        if (node_aux->free && node_aux->size >= size)
        {
            first_node = node_aux;
            count = i;
            break;
        }
        node_aux = node_aux->next;     
    }

    insert_mem(first_node, new_node, count);  
}







bool insert_worst_fit(int elem, int size)
{
    if (size > FREE_SPACE)
    {
        printf("ESPAÇO INSUFICIENTE DE MEMÓRIA ao tentar adicionar o processo %d \n", elem);
        return false;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->size = size;
    new_node->free = false;
    new_node->data = elem;

    if (SIZE == 1)
    {
        new_node->prev = HEADER;
        HEADER->next = new_node;
        HEADER->size -= new_node->size;
        TAIL = new_node;
        SIZE++;
        FREE_SPACE -= size;
        return true;        
    }

    struct Node* node_aux = HEADER;
    struct Node* worst_node = node_aux;

    while (!worst_node->free)//caminha até o primeiro nodo livre
        worst_node = worst_node->next;
    node_aux = worst_node;

    int count = -1;
    for (int i = 0; i < SIZE-1; i++)
    {   
        if (node_aux->free && node_aux->size - size >= worst_node->size - size && node_aux->size >= size)
        {
            worst_node = node_aux;
            count = i;
        }
        node_aux = node_aux->next;     
    }  

    return insert_mem(worst_node, new_node, count);
}

/*
-------------------------------------------------------
insert(int elem)

Adiciona um elemento na ultima posição da lista
Entradas: 
    elem: Dado a ser inserido na lista
    size: tamanho que o novo nodo ocupará na memória
-------------------------------------------------------
*/
bool insert_best_fit(int elem, int size)
{
    
    if (size > FREE_SPACE)
    {
        printf("ESPAÇO INSUFICIENTE DE MEMÓRIA ao tentar adicionar o processo %d \n", elem);
        return false;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->size = size;
    new_node->free = false;
    new_node->data = elem;
    if (SIZE == 1)
    {
        new_node->prev = HEADER;
        HEADER->next = new_node;
        HEADER->size -= new_node->size;
        TAIL = new_node;
        SIZE++;
        FREE_SPACE -= size;
        return true;        
    }
    
    struct Node* node_aux = HEADER;
    struct Node* best_node = node_aux;

    while (!best_node->free)//caminha até o primeiro nodo livre
        best_node = best_node->next;
    node_aux = best_node;
    
    
    int count = -1;
    for (int i = 0; i < SIZE-1; i++)
    {   
        if (node_aux->free && node_aux->size - size <= best_node->size - size && node_aux->size - size >= 0 && node_aux->size >= size)
        {
            best_node = node_aux;
            count = i;
        }
        node_aux = node_aux->next;     
    }
    insert_mem(best_node, new_node, count);
}


/*
----------------------------------------------------------
removeList(int pos)
Remove um elemento da lista
Entradas: 
    pos: Posição do elemento que será removido da lista
Saída:
    se o elemento foi removido retorna "true"
    se o elemeto não foi removido retirna "false"
----------------------------------------------------------
*/
bool removeMem(int elem)
{
    struct Node* node_aux = HEADER;
    
    while (node_aux->data != elem)//caminha ate o processo que será removido
        node_aux = node_aux->next;
    FREE_SPACE+= node_aux->size;

    if (node_aux->data == HEADER->data)
    {
        if (node_aux->next->free)
        {
            node_aux->next->size += node_aux->size;
            HEADER = node_aux;
            SIZE--;
        }else
        {
            node_aux->free = true;
        }
        return true;
    }
    
    if (node_aux->data == TAIL->data)
    {
        if (node_aux->prev->free)
        {
            node_aux->prev->size += node_aux->size;
            TAIL = node_aux;
            SIZE--;
        }else
        {
            node_aux->free = true;
            node_aux->data = 0;
        }
        return true;
    }


    if (node_aux->prev->free)
    {
        if (node_aux->next->free)
        {
            node_aux->prev->size += node_aux->size;
            node_aux->prev->size += node_aux->next->size;
            node_aux->prev->next = node_aux->next->next;
            free(node_aux->next);
            SIZE -= 2;
        }else
        {
            node_aux -> prev -> next = node_aux -> next;
            node_aux -> next -> prev = node_aux -> prev;
            node_aux -> prev -> size += node_aux -> size;
            SIZE--;
        }
        
        }else if (node_aux -> next -> free)
        {
            node_aux -> prev -> next = node_aux -> next;
            node_aux -> next -> prev = node_aux -> prev;
            node_aux -> next -> size += node_aux -> size;
            SIZE--;
        }else
        {
            node_aux->free = true;
            node_aux->data = 0;
        }
    
    


    // free(node_aux);
    return true;
    
}

/*
------------------------------
printList()

imprime os elementos da lista
------------------------------
*/
void printList()
{
    Node* node_aux = HEADER;
    printf (" ");
    for(int i=0; i<SIZE*2 + 3; i++)
        printf("-");
    printf("\n |");
    for(int i=0; i<SIZE; i++)
    {
        if (node_aux->free)
        {
            printf (" {%d}", node_aux -> size);
        }else
        {
            printf (" %d", node_aux -> data);
        }
        node_aux = node_aux -> next;
    }
    printf(" | \n");
    printf (" ");
    for(int i=0; i<SIZE*2 + 3; i++)
        printf("-");
    printf("\n");
}

