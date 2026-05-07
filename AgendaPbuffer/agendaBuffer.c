#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TAMANHO DO BUFFER
#define TAM_INICIAL 1024

// OFFSETS
#define POSITION_OPCAO_MENU 0
#define POSITION_CONTADOR_LOOP sizeof(int)
#define POSITION_QTD_PESSOAS (sizeof(int) * 2)

// JUMP OFFSETS
#define METADADOS_SIZE (sizeof(int) * 3)

// REGISTROS
#define NAME_SIZE 50
#define EMAIL_SIZE 50
#define AGE_SIZE sizeof(int)

// STRUCT
#define STRUCT_SIZE (NAME_SIZE + EMAIL_SIZE + AGE_SIZE)

// BUSCA
#define POSITION_BUSCA (METADADOS_SIZE)
#define BUSCA_SIZE 50

// INICIO DO REGISTRO
#define INICIO_REGISTROS (METADADOS_SIZE + BUSCA_SIZE)

// Protótipos das funções
void insert_Agenda(void *pBuffer);
void search_Agenda(void *pBuffer);
void list_Agenda(void *pBuffer);
void remove_Agenda(void *pBuffer);

int main()
{

  void *pBuffer = malloc(TAM_INICIAL);
  if (pBuffer == NULL)
    return 1;

  // Inicialização da variável para não ter lixo e não errar a contagem !!
  *(int *)(pBuffer + POSITION_QTD_PESSOAS) = 0;

  do
  {
    printf("----------------------------------\n");
    printf("-------------- MENU --------------\n");
    printf("----------------------------------\n");
    printf("1 - ADICIONAR (Nome, idade, email)\n");
    printf("2 - REMOVER\n");
    printf("3 - LISTAR\n");
    printf("4 - BUSCAR\n");
    printf("5 - SAIR\n");
    printf("----------------------------------\n");
    printf(" Escolha de [1-5] :  ");
    scanf(" %d", (int *)(pBuffer + POSITION_OPCAO_MENU));
    printf("----------------------------------\n");
    
    

    // COLOCAR UM COISA PRA OBRIGA ELE PREENCHER COM INT, CASO PREENCHA COM OUTRA COISA NÃO DEIXE AVANÇAR

    switch (*(int *)(pBuffer + POSITION_OPCAO_MENU))
    {
    case 1:
      insert_Agenda(pBuffer);
      break;
    case 2:
      remove_Agenda(pBuffer);
      break;
    case 3:
      list_Agenda(pBuffer);
      break;
    case 4:
      search_Agenda(pBuffer);
      break;
    }

  } while (*(int *)(pBuffer + POSITION_OPCAO_MENU) != 5);

  free(pBuffer);
  return 0;
}

void insert_Agenda(void *pBuffer)
{
  printf("ADICIONANDO ... \n");
  printf("----------------------------------\n");
  printf("NOME: ");
  scanf("%s", (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE)));
  printf("----------------------------------\n");
  printf("EMAIL: ");
  scanf("%s", (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE) + NAME_SIZE));
  printf("----------------------------------\n");
  printf("IDADE: ");
  scanf("%d", (int *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE) + NAME_SIZE + EMAIL_SIZE));printf("----------------------------------\n");
  printf("\n");

  (*(int *)(pBuffer + POSITION_QTD_PESSOAS))++;
}

void list_Agenda(void *pBuffer)
{

  for (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) = 0;
       *(int *)(pBuffer + POSITION_CONTADOR_LOOP) < *(int *)(pBuffer + POSITION_QTD_PESSOAS);
       (*(int *)(pBuffer + POSITION_CONTADOR_LOOP))++)
  {
    // indicie para visualização dos contatos
    printf("----------------------------------\n");
    printf("\nContato %d:\n", *(int *)(pBuffer + POSITION_CONTADOR_LOOP) + 1); 
    printf("----------------------------------\n");
    printf(" NOME: %s | EMAIL: %s | IDADE: %d\n",
           (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE)),
           (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE),
           *(int *)((char *)pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE + EMAIL_SIZE));
    printf("----------------------------------\n");
    printf("\n");
  }

}

void remove_Agenda(void *pBuffer){
    
    *(char*)(pBuffer + POSITION_BUSCA) = '\0'; 
    printf("----------------------------------\n");
    printf("Digite o nome para remover: ");
    scanf("%s", (char*)(pBuffer + POSITION_BUSCA));
    printf("----------------------------------\n");
    printf("\n--- Contatos com o nome '%s' ---\n", (char*)(pBuffer + POSITION_BUSCA));
    *(int *)(pBuffer + POSITION_OPCAO_MENU) = 0;
    printf("----------------------------------\n");
    

    // Conferência para ver se tem nomes de contatos iguais, e quantos. Se não tiver mostra mesmo assim para caso as pessoa não queria excluir mesmo assim
    
    // search_Agenda(pBuffer);

    for(*(int*)(pBuffer + POSITION_CONTADOR_LOOP) = 0 ;
        *(int*)(pBuffer + POSITION_CONTADOR_LOOP) < *(int*)(pBuffer + POSITION_QTD_PESSOAS);
        (*(int*)(pBuffer + POSITION_CONTADOR_LOOP))++){ 
      
        if (strcmp((char*)(pBuffer + POSITION_BUSCA), 
            (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE))) == 0){
        
            (*(int *)(pBuffer + POSITION_OPCAO_MENU))++; 
            
            printf("[%d] NOME: %s | EMAIL: %s | IDADE: %d\n", 
                *(int *)(pBuffer + POSITION_OPCAO_MENU),
                (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE)),
                (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE),
                *(int *)((char *)pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE + EMAIL_SIZE));
            printf("----------------------------------\n");
        }
    }

    if (*(int *)(pBuffer + POSITION_OPCAO_MENU) == 0) {
        printf("Nenhum contato encontrado com esse nome.\n");
        return;
    }


    printf("\nDigite o numero do contato para excluir ou 0 para CANCELAR: ");
    int escolha;
    scanf("%d", &escolha); 

    if (escolha <= 0) {
        printf("Operacao cancelada.\n");
        return;
    }

    
    *(int *)(pBuffer + POSITION_OPCAO_MENU) = 0; 
    
    // Conferência para ver se a opção escolhida, depois da conferência de possiveis contatos iguais, e realmente tirar o contato selecionado da lista, usando o memmove para gravar os dados posteriores por cima dos dados que serão removidos

    for(*(int*)(pBuffer + POSITION_CONTADOR_LOOP) = 0 ; 
        *(int*)(pBuffer + POSITION_CONTADOR_LOOP) < *(int*)(pBuffer + POSITION_QTD_PESSOAS);
        (*(int*)(pBuffer + POSITION_CONTADOR_LOOP))++){ 
        
        // Confere se os nomes são iguais

        if (strcmp((char*)(pBuffer + POSITION_BUSCA), 
                   (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE))) == 0){  
          
            (*(int *)(pBuffer + POSITION_OPCAO_MENU))++;

          // Confere a endereço que vai ser feita a operação, e logo depois realizada 
            
            if (*(int *)(pBuffer + POSITION_OPCAO_MENU) == escolha) {  
                
                int indiceAtual = *(int *)(pBuffer + POSITION_CONTADOR_LOOP);
                int totalPessoas = *(int *)(pBuffer + POSITION_QTD_PESSOAS);
                
                char *dest = (char *)pBuffer + INICIO_REGISTROS + (indiceAtual * STRUCT_SIZE);
                char *src  = dest + STRUCT_SIZE;
                int numElementosParaMover = totalPessoas - indiceAtual - 1;

                if (numElementosParaMover > 0) {
                    memmove(dest, src, numElementosParaMover * STRUCT_SIZE);
                }
                
                (*(int*)(pBuffer + POSITION_QTD_PESSOAS))--;
                printf("Contato removido com sucesso!\n");
                return; 
            }
        }
    }
}

void search_Agenda(void *pBuffer){
  
    // limpeza de buffer

    *(char*)(pBuffer + POSITION_BUSCA) = '\0'; 

    printf("Digite o nome que deseja buscar: ");
    scanf("%s", (char*)(pBuffer + POSITION_BUSCA));
    printf("----------------------------------\n");
    

    for(*(int*)(pBuffer + POSITION_CONTADOR_LOOP) = 0 ;
        *(int*)(pBuffer + POSITION_CONTADOR_LOOP) < *(int*)(pBuffer + POSITION_QTD_PESSOAS);
        (*(int*)(pBuffer + POSITION_CONTADOR_LOOP))++){ 
      
        if (strcmp((char*)(pBuffer + POSITION_BUSCA), 
            (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE))) == 0){
      
            printf("SEU CONTATO:\n");
            printf("----------------------------------\n");
            printf("\n");
            printf("NOME: %s | EMAIL: %s | IDADE: %d\n", 
                (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE)),
                (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE),
                *(int *)((char *)pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE + EMAIL_SIZE));
            printf("----------------------------------\n");
        }
    }

    if (*(int *)(pBuffer + POSITION_BUSCA)) {
        printf("Nenhum contato encontrado com esse nome.\n");
        return;
    }
    



}