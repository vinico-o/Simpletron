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

void InstructionExecutionCycle()
{
    do
    {
        printf("%02d? ", instructionCounter);
        scanf("%d", &memory[instructionCounter]);
        instructionRegister = memory[instructionCounter];
        operationCode = instructionRegister / 100;
        operand = instructionRegister % 100;

        if(memory[instructionCounter] == SENTINEL)
        {
            printf("Sentinela digitado!\n");
            printf("Carregamento do Programa Completo!\n");
            return;
        }

        switch(operationCode)
        {
            case READ:
                printf("Digite um numero: ");
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
                accumulator += memory[operand];
                break;
            case DIVIDE:
                if(memory[operand] == 0)
                {
                    printf("Divisao por 0!\n");
                    return;
                }
                accumulator /= memory[operand];
                break;
            case MULTIPLY:
                accumulator *= memory[operand];
                break;
            //TODO: fazer operacoes de branch em breve
            case BRANCH:
                break;
            case BRANCHNEG:
                break;
            case BRANCHZERO:
                break;
            case HALT:
                break;

        }

        instructionCounter++;
    } while (memory[instructionCounter] < MEMORY_SIZE);
    
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Initialization();
    InstructionExecutionCycle();

}