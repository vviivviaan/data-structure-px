
# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall

# Bibliotecas
LIBS = -lm # math library

# Diretório dos arquivos fonte
SRC_DIR = src

# Diretório dos arquivos de cabeçalho
INC_DIR = include

# Nome do executável
TARGET = main

# Arquivo principal
MAIN = main.c

# Arquivos-fonte: todos os arquivos .c no diretório de código-fonte mais o arquivo principal
SRCS = $(wildcard $(SRC_DIR)/*.c) $(MAIN)

# Arquivos-objeto: substitui .c por .o
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Alvo explícito de compilação
# Por padrão, o primeiro alvo (este) será executado se nenhum outro for especificado
compile: $(TARGET)

# Executar o programa: depende do programa alvo
run: $(TARGET)
	./$(TARGET)

# Compilar e executar o programa
all: compile run

# Limpeza: remove os arquivos-objeto e o executável
clean:
	rm -f $(OBJS) $(TARGET)

# Compilar cada arquivo-fonte em um arquivo-objeto: <arquivo>.o depende de <arquivo>.c
%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Compilar arquivos-fonte no diretório de código-fonte para arquivos-objeto: <src_dir>/<arquivo>.o depende de <src_dir>/<arquivo>.c
# Esta regra tem prioridade maior do que a anterior porque é mais específica
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Regra para ligar os arquivos-objeto e criar o executável (alvo): depende de todos os arquivos-objeto
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)


# Alvos fictícios: alvos que não são arquivos
.PHONY: all compile run clean
