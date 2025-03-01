# HealthSys

O trabalho apresentado em linguagem C visa simular um sistema simplificado de gerenciamento de dados de pacientes de uma clínica, que consiste na manipulação das infomações dos pacientes registrados.

## Sistema de gerenciamento

Representação do sistema de gerenciamento de dados dos pacientes.

![Image](https://github.com/user-attachments/assets/d51968f4-07ec-4113-9f9f-63471afb4144)

### Detalhamento da simulação
A lógica da simulação poderá ser encontrada na arquivo [main.c](main.c).
  
    I. Inicialização do sistema
        Aparecerão 6 opções para usuário, sendo:
            1 - Consultar paciente
            2 - Atualizar paciente
            3 - Remover paciente
            4 - Inserir paciente
            5 - Imprimir lista de pacientes
            Q - Sair
        e o usuário deverá escolher uma opção. 

    II. Consultar paciente: assim que selecionada a opção 1, referente à consulta de pacientes.
        Permite buscar informações de um paciente pelo nome ou CPF, exibindo os resultados encontrados.

    III. Atualizar paciente:
        selecionada a opção 2, será solicitado ao usuário que escolha o paciente que quer atualizar os dados, podendo escolher a opção 1 - por nome, 2 - por cpf ou 3 - retornar ao menu principal. Após informado algum dos dados (nome ou cpf), retorna todos os dados da paciente e o usuário vai digitando os dados que desejo atualizar, caso não queira modificar algum, é só repetir conforme os dados retornados. As alterações serão salvas no registro do paciente.
    
    IV. Remover paciente:
        Selecionando a 3ª opção, o sistema permite excluir um paciente do registro, solicitando confirmação antes da remoção.

    V. Inserir paciente:
       Já na opção 4, adiciona um novo paciente ao sistema garantindo a integridade dos dados e solicitando a confirmação da inserção.

    VI. Imprimir lista de pacientes:
        Ao escolher a opção 5 o sistema exibe a lista contendo todos os pacientes cadastrados no sistema, bem como seus dados.

    VII. Sair
        E a última opção do painel é de sair, selecionando a opção "Q" o usuário finaliza a sessão no sistema da clínica.

## Sistema de gerenciamento

*[Gcc](https://gcc.gnu.org/), para compilar o codigo em C.

## Execução 

### Compilação

Depois de baixar o repositório ou baixar o projeto:

```
$ cd ./data-structure-px
$ make
```
Fará com que execute o Makefile.

### Testar código
A execução do código pode ser feita por esses seguintes comandos:

```
$ make run
```
ou se preferir, após compilar:
```
$ ./main	
```

# Arquivos

Nesta parte, é explicado o conteúdo dos arquivos e as respectivas funções.

## Paciente

Manipulação realacionada aos pacientes, que contém:

**Paciente:**

## Variáveis 

|Variável| Tipo | Finalidade |
|-|-|-|
|[id](src/paciente.c?#L10)|Inteiro |Identificador do paciente.|
|[nome](src/paciente.c?#L11)|Char|Nome do paciente.|
|[cpf](src/paciente.c?#L12)|Char|CPF do paciente.|
|[idade](src/paciente.c?#L13)|Inteiro|Idade do paciente.|
|[data_cadastro](src/paciente.c?#L14)|Char|Data do cadastro.|
|[paciente *prox](src/paciente.c?#L15)|Struct|Ponteiro para o próximo paciente.|


**BDPaciente:**

## Variáveis

|Variável| Tipo | Finalidade |
|- |-|-|
|[inicio](src/paciente.c?#L20)|Struct |Ponteiro para o primeiro paciente.|

## Funções 

|Função|Recebe|Execução|Retorna|
| ------------- |:-------------:|-|-|
|[montagem_bd(...)](src/paciente.c?#L24)||Aloca e define banco de dados pacientes para o gerenciamento da lista.|BDPaciente*|
|[criar_paciente(...)](src/paciente.c?#L38)|int id, const char *nome, const char *cpf, int idade, const char *data_cadastro|Aloca e inicializa novo paciente na memória.|Paciente*|
|[digitar_paciente(...)](src/paciente.c?#L59)|BDPaciente *bd|Digitar as informações do paciente para a criação.|Paciente*| 
|[verificar_informacao(...)](src/paciente.c?#L117)|BDPaciente *bd, int id, const char *cpf|Verifica se o ID ou o CPF já existe.|Inteiro|
|[inserir_paciente(...)](src/paciente.c?#L142)|BDPaciente *bd, Paciente *novo|Insere paciente novo na lista do banco de dados.||
|[validar_cpf(...)](src/paciente.c?#L161)|char *cpf|Valida se o CPF contém letras ou se é menor ou maior que 11 números.|Inteiro|
|[validar_data(...](src/paciente.c?#L180))|char *data_cadastro|Valida se a data de cadastro é menor que 11 números.|Inteiro|
|[formatar_cpf(...)](src/paciente.c?#L191)|char *cpf_formatado, const char *cpf|Função para formatar CPF com pontos e traço.||
|[formatar_data(...)](src/paciente.c?#L197)|char *data_formatada, const char *data|Função para formatar a data com traços.||
|[formatar_nome(...)](src/paciente.c?#L203)|char *nome|Formatar nome e sobrenome com letra maiúscula.||
|[imprimir_pacientes(...)](src/paciente.c?#L227)|BDPaciente *bd|Imprimir todos os pacientes existentes.||
|[carregar_pacientes(...)](src/paciente.c?#L259)|BDPaciente *bd, FILE *file|Carrega pacientes do banco de dados para a lista.||
|[salvar_pacientes(...)](src/paciente.c?#L283)|BDPaciente *bd, FILE *file|Salva pacientes da lista para o banco de dados.||
|[consultar_paciente(...)](src/paciente.c?#L295)|BDPaciente *bd, const char *cpf|Consultar informações de acordo com o nome ou CPF do paciente.||
|[atualizar_paciente(...)](src/paciente.c?#L363)|BDPaciente *bd, const char *cpf|Atualizar dados do paciente.||
|[remover_pacientes(...)](src/paciente.c?#L456)|BDPaciente *bd|Remove o paciente de acordo com seu ID||


