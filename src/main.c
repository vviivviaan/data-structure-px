#include <stdio.h>      /*Biblioteca padrão para operações de entrada e saida do C.*/ 
#include <stdlib.h>     /*Biblioteca para alocação de memória.*/ 
#include <string.h>     /*Biblioteca para manipular strings.*/

int main() { 

    char opcao;         




    /*Do-while para fazer um loop no menu de opções.*/ 
    do {               

        printf("HealthSys\n");
        printf("1 - Consultar pacientes\n");
        printf("2 - Atualizar paciente\n");
        printf("3 - Remover paciente\n");
        printf("4 - Inserir paciente\n");
        printf("5 - Imprimir lista de pacientes\n");
        printf("Q - Sair\n");
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);                   

        
        switch (opcao) {                
            case '1':
                break;

            case '2':
                break;

            case '3':
                break;      

            case '4':
                break;

            case '5':
                imprimir_paciente();
                break;
               
            /*Caso o usuário digite 'Q' ou 'q', o sistema será encerrado.*/
            case 'Q':
            case 'q':
                printf("Saindo do sistema...\n");
                break;

            default:                        
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 'Q' && opcao != 'q');

    return 0;
}
