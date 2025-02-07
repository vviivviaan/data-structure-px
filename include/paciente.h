#ifndef PACIENTE_H
#define PACIENTE_H
#include <stdio.h>

typedef struct paciente Paciente;
typedef struct bdpaciente BDPaciente;

/* Função para inicializar o banco de dados. */
BDPaciente *montagem_bd();

/* Função para criar um novo paciente. */
Paciente *criar_paciente(int id, const char *nome, const char *cpf, int idade, const char *data_cadastro);

/* Função para digitar as informações do paciente. */
Paciente *digitar_paciente(BDPaciente *bd);

/* Função para inserir um paciente no banco de dados. */
void inserir_paciente(BDPaciente *bd, Paciente *novo);

/* Função para validar o CPF. */
int validar_cpf(char *cpf);

/* Função para validar a data de cadastro. */
int validar_data(char *data_cadastro);

/* Função para verificar se um paciente com o mesmo ID ou CPF já existe. */
int verificar_informacao(BDPaciente *bd, int id, const char *cpf);

/* Função para formatar CPF. */
void formatar_cpf(char *cpf_formatado, const char *cpf);

/* Função para formatar a data de cadastro. */
void formatar_data(char *data_formatada, const char *data);

/* Função para formatar o nome do paciente. */
void formatar_nome(char *nome);

/* Função para imprimir a lista de pacientes. */
void imprimir_pacientes(BDPaciente *bd);

/* Função para carregar os pacientes de um arquivo CSV. */
void carregar_pacientes(BDPaciente *bd, FILE *file);

/* Função para salvar os pacientes no arquivo CSV. */
void salvar_pacientes(BDPaciente *bd, FILE *file);

/* Função para consultar paciente baseado no nome ou CPF do paciente*/
void consultar_paciente(BDPaciente *bd, const char *cpf);

void atualizar_paciente(BDPaciente *bd, const char *cpf);

void remover_pacientes(BDPaciente *bd);

#endif
