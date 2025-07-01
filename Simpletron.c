//Autor: Vinícius Mardegan
//Projeto: Simpletron, DEITEL, Paul; DEITEL, Harvey. C: How to Program.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#define MEMORY_SIZE 100 //tamanho da memoria
#define SENTINEL -99999 //valor para sair do programa
#define MIN -9999 //Valor minimo da instrução
#define MAX 9999 //Valor Máximo da instrução

//Operações Entrada/Saida
#define READ 10 //coloca a plaavra na memória
#define WRITE 11 //escreve uma palavra da memória no terminal

//Operações de Carregamento/ARmazenamento
#define LOAD 20 //
#define STORE 21

//Operações Aritméticas
#define ADD 30 //Soma do acumolador
#define SUBTRACT 31 //Subtrai do acumolador
#define DIVIDE 32 //Divide do acumolador
#define MULTIPLY 33 //Multiplica do acumulador

//Operações de Transferência de Controle
#define BRANCH 40 //Salta para um local da memória
#define BRANCHNEG 41 //Salta para um local da memória, se Acumulado < 0
#define BRANCHZERO 42 //salta para um local da memória, se Acumulador = 0
#define HALT 43 //Para o programa

//Funções
void Initialization();
void Dump(int memory[], int* accumulator, int* instructionCounter, int* instructionRegister, int* operationCode, int* operand);
bool AccumulatorOverflow(int accumulador);
void ProgramLoading(FILE* arquivo, int memory[], int* accumulator, int* instructionCounter, int* instructionRegister, int* operationCode, int* operand);
void InstructionExecutionCycle(int memory[], int* accumulator, int* instructionCounter, int* instructionRegister, int* operationCode, int* operand);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    char filename[100];
    FILE* arquivo;

    //Variaveis do Simpletron
    int memory[MEMORY_SIZE] = {0}; //memoria
    int accumulator = 0; //acumulador, armazenamento dos resultados
    int instructionCounter = 0; //contador de instrucao
    int operationCode = 0; //Codigo de operacao (dois digitos da esquerda)
    int operand = 0; //endereco da memoria (dois digitos da direita)
    int instructionRegister = 0; //instrucao atual
    
    printf("Digite o nome (ou diretório) do Arquivo: ");
    gets(filename);

    arquivo = fopen(filename, "r");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    Initialization();
    ProgramLoading(arquivo, memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand);
    InstructionExecutionCycle(memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand);

    fclose(arquivo);
    return 0;
}

//Mensagens de Boas Vindas
void Initialization()
{
    printf("\nBem vindo ao Simpletron!\n");
    printf("Digite uma instrução por vez.\n");
    printf("Digitarei o numero da posição e um ponto de interrogação (?)\n");
    printf("Então, digite a palavra para aquela posição.\n");
    printf("Digite o valor sentinela -99999 para encerrar.\n\n");
}

//Impressao dos registradores e da memoria do simpletron
void Dump(int memory[], int* accumulator, int* instructionCounter, int* instructionRegister, int* operationCode, int* operand)
{
    printf("\nREGISTERS:\n");
    printf("Accumulator          %+05d\n", *accumulator);
    printf("InstructionCounter      %02d\n", *instructionCounter);
    printf("InstructionRegister  %+05d\n", *instructionRegister);
    printf("OperationCode           %02d\n", *operationCode);
    printf("Operand                 %02d\n", *operand);

    //Impressao da Memoria no formato de uma tabela 10x10, com formatação de +0000
    printf("\nMEMORIA:\n");
    printf("        0      1      2      3      4      5      6      7      8      9\n");
    for(int i = 0; i < MEMORY_SIZE; i += 10)
    {
        printf("%02d", i);
        for(int j = 0; j < 10; j++)
        {
            printf("  %+05d", memory[i + j]);
        }
        printf("\n");
    }

    printf("\n");
}

//Funcao que verifica se houve overflow do acumulador, ou seja, se o valor esta fora do intervalo delimitado
bool AccumulatorOverflow(int accumulador)
{
    if(accumulador < MIN || accumulador > MAX)
    {
        return true;
    }

    return false;
}

//Carrega o Programa SML de acordo com um arquivo .txt
void ProgramLoading(FILE* arquivo, int memory[], int* accumulator, int* instructionCounter, int* instructionRegister, int* operationCode, int* operand)
{
    //enquanto a leitura nao falhar e enquanto nao sair da memoria
    while(fscanf(arquivo, "%d", &memory[*instructionCounter]) == 1 && *instructionCounter < MEMORY_SIZE)
    {
        //Impressao do programa presente no arquivo
        printf("%02d? %d\n", *instructionCounter, memory[*instructionCounter]);
        //Se o sentinela for encontraod no arquivo, voltamos a memoria naquela posicao para 0, para nao guardar o sentinela na memoria
        if(memory[*instructionCounter] == SENTINEL)
        {
            memory[*instructionCounter] = 0;
            printf("\nSentinela digitado!\n");
            printf("Carregamento do Programa Completo!\n");
            Dump(memory, accumulator, instructionCounter, instructionRegister, operationCode, operand);
            return;
        }
        //verifica se a instrucao esta no mesmo tamanho maximo da palavra
        if(memory[*instructionCounter] < MIN || memory[*instructionCounter] > MAX)
        {
            printf("Valor fora do intervalo de Instrucoes!\n");
            Dump(memory, accumulator, instructionCounter, instructionRegister, operationCode, operand);
            return;
        }

        (*instructionCounter)++;
    }
}

//Execucao do programa carregado
void InstructionExecutionCycle(int memory[], int* accumulator, int* instructionCounter, int* instructionRegister, int* operationCode, int* operand)
{
    *instructionCounter = 0;

    while (*instructionCounter < MEMORY_SIZE)
    {
        *instructionRegister = memory[*instructionCounter];
        *operationCode = *instructionRegister / 100;
        *operand = *instructionRegister % 100;

        switch(*operationCode)
        {
            case READ:
                printf("Digite um numero no endereco %02d: ", *operand); //le e coloca um inteiro na memoria
                scanf("%d", &memory[*operand]);
                break;
            case WRITE:
                printf("\nO numero em %02d: %d\n", *operand, memory[*operand]); //apresenta o numero naquela posicao da memoria
                break;
            case LOAD:
                *accumulator = memory[*operand]; 
                break;
            case STORE:
                memory[*operand] = *accumulator;
                break;
            case ADD:
                *accumulator += memory[*operand];
                break;
            case SUBTRACT:
                *accumulator -= memory[*operand];
                break;
            case DIVIDE:
                if(memory[*operand] == 0)
                {
                    printf("Erro Fatal. Divisao por 0!\n");
                    Dump(memory, accumulator, instructionCounter, instructionRegister, operationCode, operand);
                    return;
                }
                *accumulator /= memory[*operand];
                break;
            case MULTIPLY:
                *accumulator *= memory[*operand];
                break;
            case BRANCH:
                *instructionCounter = *operand;
                break;
            case BRANCHNEG:
                if(*accumulator < 0)
                {
                    *instructionCounter = *operand;
                }
                break;
            case BRANCHZERO:
                if(*accumulator == 0)
                {
                    *instructionCounter = *operand;
                }
                break;
            case HALT:
                printf("Execucao do Simpletron terminou!\n");
                Dump(memory, accumulator, instructionCounter, instructionRegister, operationCode, operand);
                return;
                break;
            default:
                printf("Erro: Instrucao Invalida!\n");
                Dump(memory, accumulator, instructionCounter, instructionRegister, operationCode, operand);
                break;

        }

        //Verifica se houve algum estouro do acumulador em alguma das operações
        if(AccumulatorOverflow(*accumulator))
        {
            printf("Erro Fatal. Estouro do Acumulador!\n");
            Dump(memory, accumulator, instructionCounter, instructionRegister, operationCode, operand);
            return;
        }

        (*instructionCounter)++;
    }
    
}