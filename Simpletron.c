#include <stdio.h>
#include <locale.h>

#define MEMORY_SIZE 100 //tamanho da memoria
#define SENTINEL -99999 //valor para sair do programa

//Operações Entrada/Saida
#define READ 10 //coloca a plaavra na memória
#define WRITE 11 //escreve uma palavra da memória no terminal

//Operações de Carregamento/ARmazenamento
#define LOAD 20 //
#define STORE 21

//Operações Aritméticas
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

//Operações de Transferência de Controle
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

int memory[MEMORY_SIZE] = {0}; //memoria
int accumulator = 0; //acumulador, armazenamento dos resultados
int instructionCounter = 0; //contador de instrucao
int operationCode = 0; //Codigo de operacao (dois digitos da esquerda)
int operand = 0; //endereco da memoria (dois digitos da direita)
int instructionRegister = 0; //instrucao atual

void Initialization()
{
    printf("Bem vindo ao Simpletron!\n");
    printf("Digite uma instrução por vez.\n");
    printf("Digitarei o numero da posição e um ponto de interrogação (?)\n");
    printf("Então, digite a palavra para aquela posição.\n");
    printf("Digite o valor sentinela -99999 para encerrar.\n\n");
}

void Dump()
{
    printf("\nREGISTERS:\n");
    printf("Accumulator          %+05d\n", accumulator);
    printf("InstructionCounter      %02d\n", instructionCounter);
    printf("InstructionRegister  %+05d\n", instructionRegister);
    printf("OperationCode           %02d\n", operationCode);
    printf("Operand                 %02d\n", operand);

    printf("\nMEMORIA:\n");
    printf("         0       1       2       3       4       5       6       7       8       9\n");
    for(int i = 0; i < MEMORY_SIZE; i+= 10)
    {
        printf("%02d", i);
        for(int j = 0; j < 10; j++)
        {
            printf("  %+06d", memory[i + j]);
        }
        printf("\n");
    }
}

void ProgramLoading()
{
    do
    {
        printf("%02d? ", instructionCounter);
        scanf("%d", &memory[instructionCounter]);

        if(memory[instructionCounter] == SENTINEL)
        {
            printf("Sentinela digitado!\n");
            printf("Carregamento do Programa Completo!\n");
            Dump();
            return;
        }

        instructionCounter++;
    } while (instructionCounter < MEMORY_SIZE);
}

void InstructionExecutionCycle()
{
    instructionCounter = 0;

    while (instructionCounter < MEMORY_SIZE)
    {
        instructionRegister = memory[instructionCounter];
        operationCode = instructionRegister / 100;
        operand = instructionRegister % 100;

        switch(operationCode)
        {
            case READ:
                printf("\nDigite um numero: ");
                scanf("%d", &memory[operand]);
                break;
            case WRITE:
                printf("O numero em %02d: %d\n", operand, memory[operand]);
                break;
            case LOAD:
                accumulator = memory[operand];
                break;
            case STORE:
                memory[operand] = accumulator;
                break;
            case ADD:
                accumulator += memory[operand];
                break;
            case SUBTRACT:
                accumulator -= memory[operand];
                break;
            case DIVIDE:
                if(memory[operand] == 0)
                {
                    printf("Divisao por 0!\n");
                    Dump();
                    return;
                }
                accumulator /= memory[operand];
                break;
            case MULTIPLY:
                accumulator *= memory[operand];
                break;
            case BRANCH:
                instructionCounter = operand;
                break;
            case BRANCHNEG:
                if(accumulator < 0)
                {
                    instructionCounter = operand;
                }
                break;
            case BRANCHZERO:
                if(accumulator == 0)
                {
                    instructionCounter = operand;
                }
                break;
            case HALT:
                printf("Execucao do Simpletron terminou!\n");
                Dump();
                return;
                break;
            default:
                printf("Erro: Instrucao Invalida!\n");
                Dump();
                break;

        }

        instructionCounter++;
    }
    
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Initialization();
    ProgramLoading();
    InstructionExecutionCycle();

    return 0;
}