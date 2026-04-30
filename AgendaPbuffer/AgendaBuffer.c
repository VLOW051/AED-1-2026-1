#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TAMANHO DO BUFFER
#define TAM_INICIAL 1024

//OFFSETS 
#define POSITION_OPCAO_MENU 0              
#define POSITION_CONTADOR_LOOP sizeof(int)      
#define POSITION_QTD_PESSOAS (sizeof(int) * 2)

//METADADOS
#define METADADOS_SIZE (sizeof(int) *3)

// REGISTROS
#define NAME_SIZE 50
#define EMAIL_SIZE 50
#define AGE_SIZE sizeof(int)

// STRUCT
#define STRUCT_SIZE (NAME_SIZE + EMAIL_SIZE + AGE_SIZE)


void insert_Agenda(void *pBuffer);
void search_Agenda(void *pBuffer);
void list_Agenda(void *pBuffer);
void remove_Agenda(void *pBuffer);



int main (){

  void *pBuffer= malloc(TAM_INICIAL);


  do {
    
  printf("--------  Menu --------\n");
  printf("--- Escolha o comando ---\n");
  printf("1 - Adicionar(Nome, idade, email)\n");
  printf("2 - Remover\n");
  printf("3 - Listar\n");
  printf("4 - Buscar\n");
  printf("5 - Sair\n");

  scanf("%d", (int *)(pBuffer + POSITION_OPCAO_MENU));

  switch (*(int *)(pBuffer + POSITION_OPCAO_MENU))
  {
  case 1:
      insert_Agenda(pBuffer);
    break;
  case 2:
    /* Remover */
    break;
  case 3:
    /* Listar */
    break;
  case 4 :
   /* Buscar*/
   break;
  case 5 :
  /*Sair*/
  break;
  
  default:
    break;
  }

  }while(*(int *)(pBuffer + POSITION_OPCAO_MENU) != 5);

return 0;


}

void insert_Agenda(void *pBuffer){

  printf("NOME: \n");
  scanf("%s", (char *)(pBuffer + METADADOS_SIZE + 
  (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE)));

  printf("EMAIL: \n");
  scanf("%s", (char *)(pBuffer + METADADOS_SIZE + 
  (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE + NAME_SIZE)));

  printf("IDADE: \n");
  scanf("%s", (char *)(pBuffer + METADADOS_SIZE + 
  (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE + NAME_SIZE + EMAIL_SIZE)));


  (*(int *)(pBuffer + POSITION_QTD_PESSOAS))++;
}