#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente Paciente;
typedef struct bdpaciente BDPaciente;

BDPaciente *montagem_bd();

Paciente *criar_paciente(int id, const char *nome, const char *cpf, int idade, const char *data_cadastro);

int validar_cpf(char cpf);

int validar_data(char data_cadastro);

Paciente *digitar_paciente();

#endif


