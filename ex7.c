#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[30];
    int idade;
    int altura;
}Pessoa;

Pessoa pessoas[10];
Pessoa *inserir(Pessoa pessoas)

