/*
------------------------------------------------------
Gabriel Bonatto Justo - gabriel.justo@acad.pucrs.br

Compilar: gcc mem_man.c -o mem_man
Rodar: ./mem_man <nome do arquivo> <tipo de partição> <política/número de partições> <tamanho da memória>
------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "fixed_partition.h"
#include <string.h>




void readfile(char* name,int partic /*0 = particao fixa, 1 = particao variavel*/ , int polit/*0 = best-fit, 1= worst-fit, 2 = first-fit, 3 = next-fit*/)
{
    FILE* data = fopen(name, "r");
    
    if(data == NULL)
    {
        printf("Error! \n");   
        exit(1);             
    }

    int proc;
    bool (* insert_function)(int, int);
    void (* print_func)();
    bool (* remove_function)(int);
    char buff[255];

    if(partic == 0)
    {
        print_func = print_fixed_part;
        insert_function = insert_fixed_part;
        remove_function = remove_fixed_part;
        printf("Memória com partição fixa criada \n Tamanho da memória: %d \n Número de partções: %d \n", PARTITIONS*PART_SIZE, PARTITIONS);
    }
    else if(partic == 1)
    {
        print_func = print_mem;
        remove_function = remove_mem;
        switch (polit)
        {
            case 0:
                insert_function = &insert_best_fit;
                break;
            case 1:
                insert_function = &insert_worst_fit;
                break;
            case 2:
                insert_function = &insert_first_fit;
                break;
            case 3:
                insert_function = &insert_next_fit;
                break;
            default:
                break;
        }
    }else
    {
        printf("Error! \n");
        exit(1);
    }
    
    

    
    while (fgets(buff, 255, data) != NULL)
    {
        char *buff_aux = buff;
        if ((*buff_aux) == 'I')//adiciona um novo processo à memória
        {
            

            while (*buff_aux != '(')
                buff_aux++;
            buff_aux ++;
            proc = (int)*buff_aux;
            buff_aux +=2;
            char char_size[4] = {};
            int i = 0;
            while (1)
            {
                buff_aux ++;
                if(*buff_aux == ')')
                    break;
                char_size[i] = *buff_aux;
                i++;
                
            }
            int proc_size = atoi(char_size);
            printf("Adicionou processo %c com tamanho %d \n",proc, proc_size);
            insert_function(proc, proc_size);
            
            


        }else if(*buff_aux == 'O') //remove um processo da memória
        {
            while (*buff_aux != '(')
                buff_aux++;
            buff_aux ++;
            proc = (int)*buff_aux;
            printf("Removeu processo %c \n",proc);
            remove_function(proc);



        }

        print_func();
    }


    
    
   
    fclose(data);
}

int main(int argc, char** argv)
{
    int poli = atoi(argv[3]);
    int partic = atoi(argv[2]);
    int mem_size = atoi(argv[4]);
    initList(mem_size);
    init_memory(mem_size, poli);
    readfile(argv[1],partic, poli);
    // printList();

}

