#include "paciente.h"       /* Cabeçalho de funções */
#include <stdio.h>
#include <stdlib.h>

int main() {

    char opcao;
    FILE *file = fopen("bd_paciente.csv", "r+");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    /* Cria banco de dados */
    BDPaciente *bd = montagem_bd();

    /* Carrega pacientes do arquivo CSV */
    carregar_pacientes(bd, file);
    fclose(file);

    /* Menu do sistema */
    do {
        printf("\nHealthSys\n");
        printf("1 - Consultar paciente\n");
        printf("2 - Atualizar paciente\n");
        printf("3 - Remover paciente\n");
        printf("4 - Inserir paciente\n");
        printf("5 - Imprimir lista de pacientes\n");
        printf("Q - Sair\n");
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                consultar_paciente(bd, NULL);
                break;
            case '2':
                atualizar_paciente(bd, NULL);
                break;
            case '3':
                remover_pacientes(bd);
                break;
            case '4': {
                /* Cria novo paciente e insere no banco de dados */
                Paciente *novo = digitar_paciente(bd);
                inserir_paciente(bd, novo);
                break;
            }
            case '5':
                imprimir_pacientes(bd);
                break;

            /* Fecha o sistema caso o usuário tecle 'Q' ou 'q' */    
            case 'Q':
            case 'q':
                printf("Salvando dados do sistema\n");

                /* Salva os dados no arquivo CSV */
                file = fopen("bd_paciente.csv", "w"); 
                if (file == NULL) {
                    printf("Erro ao abrir o arquivo para o salvamento.\n");
                    break;
                }
                salvar_pacientes(bd, file);
                fclose(file);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 'Q' && opcao != 'q');

    return 0;
}
