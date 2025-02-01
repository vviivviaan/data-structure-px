#include "paciente.h"       /* Arquivo header. */ 
#include <stdio.h>          
#include <stdlib.h>         
#include <string.h>        
#include <ctype.h>          /* Biblioteca para manipular caracteres. */


/* Definição da estrutura do paciente */
struct paciente {
    int id;
    char nome[100];
    char cpf[12];
    int idade;
    char data_cadastro[11];
    struct paciente *prox;
};

/*..........................................................................................................................................*/
/* função para criar paciente*/
Paciente *criar_paciente(int id, const char *nome, const char *cpf, int idade, const char *data_cadastro){
    
    Paciente *novo_paciente = (Paciente *)malloc(sizeof(Paciente));     

    if(novo_paciente == NULL){      
        printf("Erro ao alocar a memória para o paciente\n");
        return NULL;
    }
    /* Passa os valores digitados pelo usuário para a estrutura paciente */
    novo_paciente->id = id;
    strcpy(novo_paciente->nome, nome);                                  /* Note-se que usamos "strcpy" em valores que são strings para passar os valores na estrutura */
    strcpy(novo_paciente->cpf, cpf);
    novo_paciente->idade = idade;
    strcpy(novo_paciente->data_cadastro, data_cadastro);
    novo_paciente->prox = NULL;                                         /* Como estamos inserindo o paciente na lista, o valor do próximo será NULL, indicando que é o último paciente inserido */

    return novo_paciente;
}

/*..........................................................................................................................................*/
/*Função para digitar as informações do paciente.*/
Paciente *digitar_paciente(){
    int id, idade;
    char nome[100], cpf[12], data_cadastro[11];

    printf("Digite o ID do paciente: ");
    scanf("%d", &id);

    /* While para validar o ID até ser um número positivo.*/
    while(id < 0){                 
        printf("ID não pode ser número negativo! Digite novamente:");
        scanf("%d", &id);
    }

    printf("Digite o CPF do paciente (apenas números)");
    scanf("%s", &cpf);

    /*Chama a função para validar o CPF.*/
    while((validar_cpf(cpf) != 1)){
        printf("Digite o CPF novamente: ");
        scanf("%s", &cpf);
    }

    printf("Digite o nome do paciente: ");
    getchar();                              /*Tirar a tecla 'Enter' quando o usuário aperta.*/
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';       /* Adiciona '/0' no final da entrada.*/

    printf("Digite a idade do paciente: ");
    scanf("%d", &idade);

    /*Validação de idade caso usuário digite uma idade inválida.*/
    while(idade < 1){
        printf("Idade invalida! Digite novamente: ");
        scanf("%d", &idade);
    }

    printf("Digite a data de cadastro do paciente (somente números)");
    scanf("%s", &data_cadastro);

    /*Chama a função para validar a data de cadastro do paciente.*/
    while(validar_data(data_cadastro) != 1){                                  
        printf("Digite a data de cadastro novamente: ");
        scanf("%s", &data_cadastro);
    }

    return criar_paciente(id, nome, cpf, idade, data_cadastro);
}

/*..........................................................................................................................................*/
/* Função para inserir o paciente no banco de dados */
void inserir_paciente(BDPaciente *bd, Paciente *novo){

    if(bd->inicio == NULL){                        /* Caso a lista esteja vazia, o valor inicial será o novo paciente */
        bd->inicio = novo;
    }
    
    else{
        Paciente *aux = bd->inicio;

        /*Percorrre até achar o ultimo nó da lista para inserir o novo paciente */
        while(aux->prox != NULL){                  
            aux = aux->prox;
        }
        aux->prox = novo;
    }

} 

/* Definição da estrutura para o nó da lista encadeada. */
struct bdpaciente {
    Paciente *inicio;
};

/* Função para inicializar o banco de dados. */
BDPaciente *montagem_bd(){

    BDPaciente *bd = (BDPaciente *)malloc(sizeof(BDPaciente));          

    if(bd == NULL){
        printf("Erro ao alocar a memória para o banco de dados\n");
        return NULL;
    }

    bd->inicio = NULL;     /* Começar o ponteiro inicial com valor nulo. */
    return bd;
}




/* Função para validar o CPF. */
int validar_cpf(char *cpf){

    if(strlen(cpf) != 11){                                      /* Caso o CPF seja diferente que 11, retorna 0 (ou seja não é válido). */
        printf("O CPF deve conter 11 digitos numericos.\n");
        return 0;
    }

    for(int i = 0; i < 11; i++){
        if(!isdigit(cpf[i])){                                  /*"isdigit" é usada para encontrar caracteres dentro do vetor CPF*/
            printf("CPF invalido! Deve conter apenas digitos numericos.\n");
            return 0;
        }
    }

    return 1;                                                   /*Retorna 1 caso passe das condições (ou seja, CPF válido).*/ 
}


/*Função para validar a data de cadastro.*/
int validar_data(char data_cadastro){

    if(strlen(data_cadastro) != 8){                            /*Como a data é somente digitos, não pode ser menor que 8*/                                                                       
        printf("Data de cadastro inválida!");
        return 0;
    }

    return 1;                                                   /*Retorna 1 caso passe das condições (ou seja, data válida).*/
}



/* função para formatar o CPF*/

void formatar_cpf(cpf *cpf)
{
   char cpf_block1[4];
   char cpf_block2[4];
   char cpf_block3[4];
   char cpf_block4[3];

   sscanf(s->cpf, "%3s", cpf_block1);
   sscanf(s->cpf + 3, "%3s", cpf_block2);
   sscanf(s->cpf + 6, "%3s", cpf_block3);
   sscanf(s->cpf + 9, "%2s", cpf_block4);

   printf(" CPF: %s.%s.%s-%-20s")
}


void imprimir_pacientes(BDPaciente *bd) {
    if (bd->inicio == NULL) {
        printf("\nNenhum paciente cadastrado.\n");
        return;
    }

    Paciente *aux = bd->inicio;
    printf("\nLista de Pacientes:\n");
    printf("ID | CPF | Nome | Idade | Data de Cadastro\n");
    printf("--------------------------------------------\n");
    
    while (aux != NULL) {
        printf("%d | %s | %s | %d | %s\n", aux->id, aux->cpf, aux->nome, aux->idade, aux->data_cadastro);
        aux = aux->prox;
    }
}
