#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




typedef struct Node
{
    struct Node* prev;
    struct Node* next;
    int data;
}Node;

struct Node* HEADER;
struct Node* TAIL;
int SIZE;
bool INITIATED = false;

void initList()
{
    if (INITIATED)
        return;
    HEADER = (Node*)malloc(sizeof(Node));
    TAIL = HEADER;
    SIZE = 0;
    INITIATED = true;
}

/*
-------------------------------------------------------
insert(int elem, int pos)

Adiciona um elemento à uma posição específica da lista
Entradas: 
    elem: Dado a ser inserido na lista
    pos: Posição onde esse dado será inserido na lista
Saida:
    se o dado foi adicionado retorna "true"
    se o dado não foi adicionado retirna "false"
-------------------------------------------------------
*/
bool insert(int elem, int pos)
{
    if (pos > SIZE) // Não adiciona caso a posição é maior que o tamanho da lista
        return false;
    
    if (SIZE == 0) // Adiciona o primeiro elemento     
    {
        HEADER -> data = elem;
        TAIL = HEADER;
        SIZE ++;
        return true;
    }
    


    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node -> data = elem;
    Node* node_aux;

    if (pos == SIZE) // Adiciona no fim da lista
    {
        node_aux = TAIL;
        TAIL = new_node;
        TAIL -> prev = node_aux;
        node_aux -> next = TAIL;
        SIZE ++;
        return true;
    }

    // adiciona no meio da lista
    node_aux = HEADER;
    for (int i = 0; i < pos; i++) // caminha até a posição
        node_aux = node_aux -> next;
    
    node_aux -> prev -> next = new_node;
    new_node -> next = node_aux;
    new_node -> prev = node_aux -> prev;
    node_aux -> prev = new_node;
    SIZE ++;
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
        printf (" %d", node_aux -> data);
        node_aux = node_aux -> next;
    }
    printf(" | \n");
    printf (" ");
    for(int i=0; i<SIZE*2 + 3; i++)
        printf("-");
    printf("\n");
}

