#include "paciente.h"       /* Cabeçalho de funções. */ 
#include <stdio.h>          
#include <stdlib.h>         
#include <string.h>        
#include <ctype.h>          /* Biblioteca para manipular caracteres. */

/* Definição da estrutura do paciente. */
struct paciente {
    int id;
    char nome[100];
    char cpf[12];
    int idade;
    char data_cadastro[11];
    struct paciente *prox;
};

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
/* Função para criar paciente. */
Paciente *criar_paciente(int id, const char *nome, const char *cpf, int idade, const char *data_cadastro){
    
    Paciente *novo_paciente = (Paciente *)malloc(sizeof(Paciente));     

    if(novo_paciente == NULL){      
        printf("Erro ao alocar a memória para o paciente\n");
        return NULL;
    }
    /* Passa os valores digitados pelo usuário para a estrutura paciente. */
    novo_paciente->id = id;
    strcpy(novo_paciente->nome, nome);                                  /* Note-se que usamos "strcpy" em valores que são strings para passar os valores na estrutura. */
    strcpy(novo_paciente->cpf, cpf);
    novo_paciente->idade = idade;
    strcpy(novo_paciente->data_cadastro, data_cadastro);
    novo_paciente->prox = NULL;                                         /* Como estamos inserindo o paciente na lista, o valor do próximo será NULL, indicando que é o último paciente inserido. */

    return novo_paciente;
}
/* Função para digitar as informações do paciente. */
Paciente *digitar_paciente(BDPaciente *bd){
    int id, idade, validar;
    char nome[100], cpf[12], data_cadastro[11];

    do {
        printf("Digite o ID do paciente: ");
        scanf("%d", &id);

        /* While para validar o ID até ser um número positivo. */
        while(id < 0) {                 
            printf("ID não pode ser número negativo! Digite novamente:");
            scanf("%d", &id);
        }

        printf("Digite o CPF do paciente (apenas números): ");
        scanf("%s", cpf);
        /* Chama a função para validar o CPF. */
        while((validar_cpf(cpf) != 1)){
            printf("Digite o CPF novamente: ");
            scanf("%s", cpf);
        }

        /* Verifica se já existe um paciente com o mesmo ID ou CPF. */
        validar = verificar_informacao(bd,id,cpf);
        
        if(validar == 0){
            printf("Por favor, tente novamente com um ID e CPF diferentes.\n");
        }

    }while(validar == 0);

    printf("Digite o nome do paciente: ");
    getchar();                              /* Tira a tecla 'Enter' quando o usuário aperta. */
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';       /* Adiciona '/0' no final da entrada. */

    printf("Digite a idade do paciente: ");
    scanf("%d", &idade);

    /* Validação de idade caso usuário digite uma idade inválida. */
    while(idade < 1){
        printf("Idade invalida! Digite novamente: ");
        scanf("%d", &idade);
    }
    printf("Digite a data de cadastro do paciente (somente números, seguindo a ordem AAAA/MM/DD)");
    scanf("%s", data_cadastro);

    /* Chama a função para validar a data de cadastro do paciente. */
    while(validar_data(data_cadastro) != 1){                                  
        printf("Digite a data de cadastro novamente: ");
        scanf("%s", data_cadastro);
    }
    return criar_paciente(id, nome, cpf, idade, data_cadastro);
}
int verificar_informacao(BDPaciente *bd, int id, const char *cpf) {
    Paciente *aux = bd->inicio;
    while(aux != NULL) {

        /* Se tiver o mesmo ID mostra mensagem de erro e retorna 1. */
        if (aux->id == id) {
            printf("Já existe um paciente com o ID %d!\n", id);
            return 0;  
        }

        /* Compara se os CPFs são iguais. */
        if (strcmp(aux->cpf, cpf) == 0) {
            printf("Já existe um paciente com o CPF %s!\n", cpf);
            return 0;  
        }
        aux = aux->prox;
    }
    return 1;                                                      /* Retorna 1 caso esteja tudo correto. */
}
/* Função para inserir o paciente no banco de dados. */
void inserir_paciente(BDPaciente *bd, Paciente *novo){

    if(bd->inicio == NULL){                        /* Caso a lista esteja vazia, o valor inicial será o novo paciente. */
        bd->inicio = novo;
    }
    
    else{
        Paciente *aux = bd->inicio;

        /* Percorrre até achar o ultimo nó da lista para inserir o novo paciente. */
        while(aux->prox != NULL){                  
            aux = aux->prox;
        }
        aux->prox = novo;
    }
} 
/* Função para validar o CPF. */
int validar_cpf(char *cpf){

    if(strlen(cpf) != 11){                                      /* Caso o CPF seja diferente que 11, retorna 0 (ou seja não é válido). */
        printf("O CPF deve conter 11 digitos numericos.\n");
        return 0;
    }

    for(int i = 0; i < 11; i++){
        if(!isdigit(cpf[i])){                                  /* "isdigit" é usada para encontrar caracteres dentro do vetor CPF. */
            printf("CPF invalido! Deve conter apenas digitos numericos.\n");
            return 0;
        }
    }

    return 1;                                                   /* Retorna 1 caso passe das condições (ou seja, CPF válido). */ 
}
/* Função para validar a data de cadastro. */
int validar_data(char *data_cadastro){

    if(strlen(data_cadastro) != 8){                            /* Como a data é somente digitos, não pode ser menor que 8. */                                                                       
        printf("Data de cadastro inválida!");
        return 0;
    }
    return 1;                                                   /* Retorna 1 caso passe das condições (ou seja, data válida). */
}
/* Função para formatar cpf quando for imprimir. */
void formatar_cpf(char *cpf_formatado, const char *cpf) {

    sprintf(cpf_formatado, "%.3s.%.3s.%.3s-%s", cpf, cpf + 3, cpf + 6, cpf + 9);
}

/* Função para formatar a data quando for imprimir. */
void formatar_data(char *data_formatada, const char *data) {

    sprintf(data_formatada, "%.4s-%.2s-%.2s", data, data + 4, data + 6);
}
/* Função para formatar o nome em letra maiuscula. */
void formatar_nome(char *nome){
    /* Se o nome não for vazio, ele pega a primeira letra e transforma em maiuscula. */
      if (nome[0] != '\0') {
        nome[0] = toupper(nome[0]);
    }

    /* Percorre até encontrar o final (ou seja '\0'). */
    for (int i = 1; nome[i] != '\0'; i++) {

        /* Verifica se o caracter anterior é um espaço em branco. */
        if (nome[i - 1] == ' ') {

            /* Caso seja, a proxima letra fica maiuscula. */
            nome[i] = toupper(nome[i]); 
        } else {

            /* Caso o contrario, continua minuscula. */
            nome[i] = tolower(nome[i]);
        }
    }
}
/* Função para imprimir dados dos pacientes. */
void imprimir_pacientes(BDPaciente *bd) {

    if (bd == NULL || bd->inicio == NULL) {
        printf("Não há pacientes cadastrados no sistema.\n");
        return;
    }
    /* Variável para percorrer a lista sem modificar o valorr original. */
    Paciente *aux = bd->inicio;
    printf("\nLista de Pacientes:\n");
    printf("ID  | CPF             | Nome               | Idade | Data de Cadastro\n");

    while(aux != NULL) {

        /* Nova variavel para armazenar os valores formatados. */
        char cpf_formatado[15];   
        char data_formatada[11];  

        /* Chamada de funções para formatar. */
        formatar_cpf(cpf_formatado, aux->cpf);
        formatar_data(data_formatada, aux->data_cadastro);
        formatar_nome(aux->nome); 

        printf("%-3d | %-15s | %-18s | %-5d | %-10s\n",
               aux->id, cpf_formatado, aux->nome, aux->idade, data_formatada);

        aux = aux->prox;
    }
}
/* Função que ler da lista encadeada e salva no arquivo. */
void carregar_pacientes(BDPaciente *bd, FILE *file) {

    char linha[200];

    /* Ignora a primeira linha. */
    fgets(linha, sizeof(linha), file);

    /* Lê cada linha do arquivo e salva no vetor 'linha' até chegar no final. */
    while (fgets(linha, sizeof(linha), file)) {
        int id, idade;
        char nome[100], cpf[12], data_cadastro[11];

        /* Se tiver com os 5 parametros essencias, cria o novo paciente e insere na struct. */
        if (sscanf(linha, "%d,%11[^,],%99[^,],%d,%10s", &id, cpf, nome, &idade, data_cadastro) == 5) {
            printf("Lendo paciente: %d, %s, %s, %d, %s\n", id, cpf, nome, idade, data_cadastro);
            Paciente *novo = criar_paciente(id, nome, cpf, idade, data_cadastro);
            inserir_paciente(bd, novo);
        } else {
            printf("Erro ao ler linha: %s\n", linha);
        }
    }
}
/* Função para salvar os pacientes no arquivo CSV. */
void salvar_pacientes(BDPaciente *bd, FILE *file) {

    Paciente *aux = bd->inicio;

    /* Percorre a lista de paciente enquanto não for nulo. */
    while (aux != NULL) {
        fprintf(file, "%d,%s,%s,%d,%s\n", aux->id, aux->cpf, aux->nome, aux->idade, aux->data_cadastro);
        aux = aux->prox;
    }
}

/* Função para consultar paciente baseado no nome ou CPF do paciente*/
void consultar_paciente(BDPaciente *bd, const char *cpf){

    if(bd == NULL || bd->inicio == NULL) {
        printf("Não há pacientes cadastrados no sistema.\n");
        return;
    }
       
    /* Preparação para montagem da consulta do paciente. */
    int opcao;
    char busca[100];
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();                          
    
    if (opcao == 1) {
        printf("Digite o nome do paciente: ");
        fgets(busca, sizeof(busca), stdin);

        /* Adiciona /0 para quando o usuario apertar 'Enter' não contar na string. */
        busca[strcspn(busca, "\n")] = '\0'; 
    } else if (opcao == 2) {
        printf("Digite o CPF: ");
        scanf("%s", busca);
    } else {
        printf("Opção inválida!\n");
        return;
    }

    /* Variavel auxiliar para ajudar no percorrimento da lista. */
    Paciente *aux = bd->inicio;

    /* Flag para ajudar se encontrou ou não o paciente. */
    int encontrado = 0;
    printf("ID  | CPF             | Nome               | Idade | Data de Cadastro\n");

    while (aux != NULL) {

        /* De acordo com cada opção digitada pelo usuario, compara as strings para fazer a busca. */
        if ((opcao == 1 && strcasecmp(aux->nome, busca) == 0) ||
            (opcao == 2 && strcmp(aux->cpf, busca) == 0)) {
            
            char cpf_formatado[15];   
            char data_formatada[11];  

            /* Chama as funções para formatar. */
            formatar_cpf(cpf_formatado, aux->cpf);
            formatar_data(data_formatada, aux->data_cadastro);
            formatar_nome(aux->nome); 
            
            printf("%-3d | %-15s | %-18s | %-5d | %-10s\n",
                   aux->id, cpf_formatado, aux->nome, aux->idade, data_formatada);
            encontrado = 1;
        }
        aux = aux->prox;
    }

    if (encontrado != 1) {
        printf("Paciente não encontrado!\n");
    }
}

/* Função para atualizar paciente. */

void atualizar_paciente(BDPaciente *bd, const char *cpf){

    if(bd == NULL || bd->inicio == NULL) {
        printf("Não há pacientes cadastrados no sistema.\n");
        return;
    }
       
    /* Preparação para consultar paciente e, em seguida, atualizar. */
    int opcao;
    char busca[100];
    printf("Escolha o paciente que voce quer atualizar os dados:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();                           

    if (opcao == 1) {
        printf("Digite o nome do paciente: ");
        fgets(busca, sizeof(busca), stdin);

        /* Adiciona /0 para quando o usuario apertar 'Enter' não contar na string. */
        busca[strcspn(busca, "\n")] = '\0'; 
    } else if (opcao == 2) {
        printf("Digite o CPF: ");
        scanf("%s", busca);
    } else {
        printf("Opção inválida!\n");
        return;
    }

    /* Variavel auxiliar para ajudar no percorrimento da lista. */
    Paciente *aux = bd->inicio;

    /* Flag para ajudar se encontrou ou não o paciente. */
    int encontrado = 0;
    printf("ID  | CPF             | Nome               | Idade | Data de Cadastro\n");

    while (aux != NULL) {

        /* De acordo com cada opção digitada pelo usuario, compara as strings para fazer a busca. */
        if ((opcao == 1 && strcasecmp(aux->nome, busca) == 0) ||
            (opcao == 2 && strcmp(aux->cpf, busca) == 0)) {
            
            char cpf_formatado[15];   
            char data_formatada[11];  

            /* Chama as funções para formatar. */
            formatar_cpf(cpf_formatado, aux->cpf);
            formatar_data(data_formatada, aux->data_cadastro);
            formatar_nome(aux->nome); 
            
            printf("%-3d | %-15s | %-18s | %-5d | %-10s\n",
                   aux->id, cpf_formatado, aux->nome, aux->idade, data_formatada);
            encontrado = 1;

        /* Atualizar os dados do paciente. */
            printf("Digite os novos dados do paciente: \n");
            printf("Nome: ");
            fgets(aux->nome, sizeof(aux->nome), stdin);
            aux->nome[strcspn(aux->nome, "\n")] = '\0';
            
            printf("Idade: ");
            scanf("%d", &aux->idade);
            getchar();
            
            printf("CPF (apenas numeros): ");
            scanf("%s", aux->cpf);
            getchar();

            printf("Data de Cadastro (AAAA/MM/DD): ");
            scanf("%s", aux->data_cadastro);
            getchar();

            printf("Dados atualizados!");
            break;
        }
        aux = aux->prox;
    }
    if (encontrado != 1) {
        printf("Paciente não encontrado!\n");
    }
}
/* Função para remover paciente. */
void remover_pacientes(BDPaciente *bd) {

    if (bd == NULL || bd->inicio == NULL) {
        printf("Não há pacientes cadastrados no sistema.\n");
        return;
    }

    /* Imprimir lista de pacientes. */
    imprimir_pacientes(bd);

    int id;
    printf("Digite o ID do paciente antes de remover: ");
    scanf("%d", &id);
    getchar();

    /* Varriável auxiliar para ajudar percorrer. */
    Paciente *aux = bd->inicio;
    Paciente *anterior = NULL;
    int encontrado = 0;

    /* Percorre até o final da lista. */
    while (aux != NULL) {
        if (aux->id == id) {
            if (anterior == NULL) {
                bd->inicio = aux->prox;
            } else {
                anterior->prox = aux->prox;
            }

            /* Remove paciente (free). */
            free(aux);
            printf("Paciente removido!\n");
            encontrado = 1;
            break;
        }
        anterior = aux;
        aux = aux->prox;
    }
    if (encontrado != 1) {
        printf("Paciente não encontrado!\n");
    }
}