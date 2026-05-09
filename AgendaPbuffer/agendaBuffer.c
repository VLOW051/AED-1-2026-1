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
    printf("\n");
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
    printf("\n");
    
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
       printf("BUSCANDO ...\n");
       printf("----------------------------------\n");
       printf("Digite o nome para a busca: ");
       scanf(" %49[^\n]", (char *)(pBuffer + POSITION_BUSCA));
       search_Agenda(pBuffer);
      break;
    }

  } while (*(int *)(pBuffer + POSITION_OPCAO_MENU) != 5);

  free(pBuffer);
  return 0;
}

void insert_Agenda(void *pBuffer)
{

  // o scanf com o espaço está dando problema 

  printf("ADICIONANDO ... \n");
  printf("----------------------------------\n");
  printf("NOME: ");
  scanf(" %49[^\n]", (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE)));
  printf("----------------------------------\n");
  printf("EMAIL: ");
  scanf(" %49[^\n]", (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE) + NAME_SIZE));
  printf("----------------------------------\n");
  printf("IDADE: ");
  scanf("%d", (int *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_QTD_PESSOAS) * STRUCT_SIZE) + NAME_SIZE + EMAIL_SIZE));printf("----------------------------------\n");
  printf("\n");

  (*(int *)(pBuffer + POSITION_QTD_PESSOAS))++;
}

void list_Agenda(void *pBuffer)
{
    
  // verifica se a lista de contato está vazia se sim volta pro menu 

    if (*(int *)(pBuffer + POSITION_QTD_PESSOAS) == 0)
    {
        printf("----------------------------------\n");
        printf("---------- AGENDA VAZIA !! --------\n");
        printf("-----------------------------------\n");
        return; 
    }

    // um vez que tem contato eles são listados 

    for (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) = 0;
         *(int *)(pBuffer + POSITION_CONTADOR_LOOP) < *(int *)(pBuffer + POSITION_QTD_PESSOAS);
         (*(int *)(pBuffer + POSITION_CONTADOR_LOOP))++)
    {
        printf("----------------------------------\n");
        printf("Contato %d:\n", *(int *)(pBuffer + POSITION_CONTADOR_LOOP) + 1); 
        printf("----------------------------------\n");
        
        printf(" NOME: %s | EMAIL: %s | IDADE: %d\n",
               (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE)),
               (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE),
               *(int *)((char *)pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE + EMAIL_SIZE));
               
        printf("----------------------------------\n\n");
    }
}

void search_Agenda(void *pBuffer) {

      // verifica se tem contato na agenda antes de procurar

      if (*(int *)(pBuffer + POSITION_QTD_PESSOAS) == 0)
        {
            printf("----------------------------------\n");
            printf("---------- AGENDA VAZIA !! --------\n");
            printf("-----------------------------------\n");
            return; 
        }

    // zra o contador de ocorrências para a nova listagem
    *(int *)(pBuffer + POSITION_OPCAO_MENU) = 0; 

    for (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) = 0;
         *(int *)(pBuffer + POSITION_CONTADOR_LOOP) < *(int *)(pBuffer + POSITION_QTD_PESSOAS);
         (*(int *)(pBuffer + POSITION_CONTADOR_LOOP))++) {

        // cmp o nome da busca com o nome no registro atual
        if (strcmp((char *)(pBuffer + POSITION_BUSCA),
                   (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE))) == 0) {

            // incremnta contador
            (*(int *)(pBuffer + POSITION_OPCAO_MENU))++;

            // lista de contato(s) encontrado(s)

            printf("[%d] NOME: %s | EMAIL: %s | IDADE: %d\n",
                   *(int *)(pBuffer + POSITION_OPCAO_MENU), 
                   (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE)),
                   (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE),
                   *(int *)((char *)pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE) + NAME_SIZE + EMAIL_SIZE));
        }
    }

    // se não achar nada
    if (*(int *)(pBuffer + POSITION_OPCAO_MENU) == 0) {
        printf("Nenhum contato encontrado.\n");
    }
}

void remove_Agenda(void *pBuffer) {
   
  
    printf("\nDigite o nome que deseja remover: ");
    printf("-------------------------------------\n"); 

    scanf(" %49[^\n]", (char *)(pBuffer + POSITION_BUSCA));

    printf("\n------ Resultados encontrados ------\n");
    printf("--------------------------------------\n");

    // chamada da função search, para aproveitar o mecânismo de busca

    search_Agenda(pBuffer);

    if (*(int *)(pBuffer + POSITION_OPCAO_MENU) > 0) {
        
        printf("\nDigite o numero do contato para excluir (ou 0 para cancelar): ");
        scanf("%d", (int *)(pBuffer + POSITION_CONTADOR_LOOP + sizeof(int)));

        // cancelar operação

        if (*(int *)(pBuffer + POSITION_CONTADOR_LOOP + sizeof(int)) == 0) {
            printf("Operacao cancelada.\n");
            return;
        }

        // limpeza de buffer para localizar o índice real no segundo loop

        *(int *)(pBuffer + POSITION_OPCAO_MENU) = 0;

        // Conferência para ver se a opção escolhida, depois da conferência de possiveis contatos iguais, e realmente tirar o contato selecionado da lista buscada, usando o memmove para gravar os dados posteriores por cima dos dados que serão removidos, atualizando os indicies da lista de contato

        for (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) = 0;
             *(int *)(pBuffer + POSITION_CONTADOR_LOOP) < *(int *)(pBuffer + POSITION_QTD_PESSOAS);
             (*(int *)(pBuffer + POSITION_CONTADOR_LOOP))++) {

            // Compara se o registro atual com o nome buscado

            if (strcmp((char *)(pBuffer + POSITION_BUSCA),
                       (char *)(pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE))) == 0) {

                // Incrementa a contagem dos contatos iguais

                (*(int *)(pBuffer + POSITION_OPCAO_MENU))++;

                // Se esta ocorrência for a que o usuário escolheu

                if (*(int *)(pBuffer + POSITION_OPCAO_MENU) == *(int *)(pBuffer + POSITION_CONTADOR_LOOP + sizeof(int))) {
                  
                  if (*(int *)(pBuffer + POSITION_QTD_PESSOAS) - *(int *)(pBuffer + POSITION_CONTADOR_LOOP) - 1 > 0) {
                        
                      memmove(
                            (char *)pBuffer + INICIO_REGISTROS + (*(int *)(pBuffer + POSITION_CONTADOR_LOOP) * STRUCT_SIZE),
                            (char *)pBuffer + INICIO_REGISTROS + ((*(int *)(pBuffer + POSITION_CONTADOR_LOOP) + 1) * STRUCT_SIZE),
                            (*(int *)(pBuffer + POSITION_QTD_PESSOAS) - *(int *)(pBuffer + POSITION_CONTADOR_LOOP) - 1) * STRUCT_SIZE
                        );

                    }

                    // decrementa a quantidade total de pessoas

                    (*(int *)(pBuffer + POSITION_QTD_PESSOAS))--;
                    
                    printf("\n>>> Contato removido com sucesso! <<<\n");
                    return; 
            }
        }
        printf("Opcao invalida. Nenhum contato removido.\n");
      }
      
    }else {
        printf("Nenhum registro encontrado para remocao.\n");
    }
}