#include <stdio.h>
#include <locale.h>

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

void Initialization()
{
    printf("Bem vindo ao Simpletron!\n");
    printf("Digite uma instrução por vez.\n");
    printf("Digitarei o numero da posição e um ponto de interrogação (?)\n");
    printf("Então, digite a palavra para aquela posição.\n");
    printf("Digite o valor sentinela -99999 para encerrar.\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Initialization();
}