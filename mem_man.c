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
#include "fixed_partition.h"
#include <string.h>




void readfile(char* name, int polit/*0 = best-fit, 1= worst-fit, 2 = first-fit, 3 = next-fit*/)
{
    FILE* data = fopen(name, "r");
    
    if(data == NULL)
    {
        printf("Error! \n");   
        exit(1);             
    }

    int proc;
    bool (*insert_function)(int, int);
    char buff[255];
    fgets(buff, 255, data);
    char *buff_aux = buff;
    if ((*buff_aux) == 'I')//adiciona um novo processo à memória
    {
        switch (polit)
        {
        case 0:
            insert_function = &insert_best_fit;
        case 1:
            insert_function = &insert_worst_fit;
        case 2:
            insert_function = &insert_first_fit;
        case 3:
            insert_function = &insert_next_fit;
            break;
        default:
            break;
        }
        while (*buff_aux != '(')
            buff_aux++;
        buff_aux ++;
        proc = (int)*buff_aux;
        buff_aux +=2;
        char char_size[4];
        int i = 0;
        while (1)
        {
            buff_aux ++;
            if(*buff_aux == ')')
                break;
            char_size[i] = *buff_aux;
            i++;
            
        }
        printf("%s \n", char_size);
        

        




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
    int poli = atoi(argv[2]);
    readfile(argv[1], poli);

}

