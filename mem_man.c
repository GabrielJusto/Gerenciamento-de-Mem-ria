/*
------------------------------------------------------
Gabriel Bonatto Justo - gabriel.justo@acad.pucrs.br

Compilar: gcc mem_man.c -o mem_man
Rodar: ./mem_man <nome do arquivo>
------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"




void readfile(char* name, int polit/*0 = best-fit, 1= worst-fit, 2 = first-fit, 3 = next-fit*/)
{
    FILE* data = fopen(name, "r");
   
    if(data == NULL)
   {
      printf("Error! \n");   
      exit(1);             
   }
    char buff[255];
    fgets(buff, 255, data);
    char *buff_aux = buff;
    if ((*buff_aux) == 'I')//adiciona um novo processo à memória
    {
        switch (polit)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        
        default:
            break;
        }
        while (*buff_aux != '(')
            buff_aux++;
        buff_aux ++;
         printf("%c", *buff_aux); 




    }else if(*buff_aux == 'O') //remove um processo da memória
    {
        while (*buff_aux != '(')
            buff_aux++;
        buff_aux ++;



    }
    
   
    fclose(data);
}

int main(int argc, char** argv)
{
    // int polit = atoi(argv[2]);
    initList(64);
    printList();
    insert_best_fit(1,16);
    printList();
    insert_best_fit(2,17);
    printList();
    insert_best_fit(3,16);
    printList();
    removeMem(2);
    printList();
    insert_first_fit(5,1);
    printList();
    insert_first_fit(6,1);
    printList();
    insert_first_fit(7,1);
    printList();
    insert_first_fit(8,1);
    printList();
    insert_first_fit(9,12);
    removeMem(7);
    printList();
    removeMem(5);
    printList();
    removeMem(1);
    insert_next_fit(12,11);
    printList();
    insert_next_fit(10,1);
    printList();
    insert_next_fit(11,2);
    printList();
    insert_next_fit(13,4);
    // insert_next_fit(10,1);
    // insert_next_fit(10,1);




    printList();

}

