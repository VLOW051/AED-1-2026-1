#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TAMANHO DO BUFFER
#define TAM_INICIAL 1024

// OFFSETS 
#define POSITION_OPCAO_MENU 0               
#define POSITION_CONTADOR_LOOP sizeof(int)      
#define POSITION_QTD_PESSOAS (sizeof(int) * 2)

// JUMP OFFSETS 7
#define METADADOS_SIZE (sizeof(int) * 3) 

// REGISTROS 
#define NAME_SIZE 50
#define EMAIL_SIZE 50
#define AGE_SIZE sizeof(int)

// STRUCT 
#define STRUCT_SIZE (NAME_SIZE + EMAIL_SIZE + AGE_SIZE)

// Protótipos das funções 
void insert_Agenda(void *pBuffer);
void search_Agenda(void *pBuffer);
void list_Agenda(void *pBuffer);
void remove_Agenda(void *pBuffer);

int main () {

    void *pBuffer = malloc(TAM_INICIAL);
    if (pBuffer == NULL) return 1;


    *(int *)(pBuffer + POSITION_QTD_PESSOAS) = 0;

    do {
        printf("\n--------  Menu --------\n");
        printf("1 - Adicionar (Nome, idade, email)\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("4 - Buscar\n");
        printf("5 - Sair\n");
        printf("... : ");

      
        scanf("%d", (int *)(pBuffer + POSITION_OPCAO_MENU));

        
        switch (*(int *)(pBuffer + POSITION_OPCAO_MENU)) {
            case 1:
                insert_Agenda(pBuffer);
                break;
            case 2:
                /* remove_Agenda(pBuffer); */
                break;
            case 3:
                list_Agenda(pBuffer);
                break;
            case 4:
                /* search_Agenda(pBuffer); */
                break;
        }

    } while(*(int *)(pBuffer + POSITION_OPCAO_MENU) != 5); 

    free(pBuffer);
    return 0;
}

void insert_Agenda(void *pBuffer) {
    
    int desloc = METADADOS_SIZE + (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE);

    printf("NOME: ");
    scanf("%s", (char *)(pBuffer + desloc));

    printf("EMAIL: ");
    scanf("%s", (char *)(pBuffer + desloc + NAME_SIZE));

    printf("IDADE: ");
    scanf("%d", (int *)(pBuffer + desloc + NAME_SIZE + EMAIL_SIZE));

  
    (*(int *)(pBuffer + POSITION_QTD_PESSOAS))++;
}

void list_Agenda(void *pBuffer) {
   
    for (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) = 0; 
         *(int *)(pBuffer + POSITION_CONTADOR_LOOP) < *(int *)(pBuffer + POSITION_QTD_PESSOAS); 
         (*(int *)(pBuffer + POSITION_CONTADOR_LOOP))++) {

     
        int desloc = METADADOS_SIZE + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE);

        printf("\nContato %d:\n", *(int *)(pBuffer + POSITION_CONTADOR_LOOP) + 1);
        printf("NOME : %s\n", (char *)(pBuffer + desloc));
        printf("EMAIL: %s\n", (char *)(pBuffer + desloc + NAME_SIZE));
        printf("IDADE: %d\n", *(int *)((char *)pBuffer + desloc + NAME_SIZE + EMAIL_SIZE));
    }
}