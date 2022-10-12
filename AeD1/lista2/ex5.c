#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[30];
    int idade;
    int altura;
}Pessoa;

Pessoa *inserir(Pessoa *lista, int tam);

int main(){

    int sw, tam = 0;
    Pessoa *lista = NULL;

    do{

        printf("Deseja adicionar alguem na lista ou sair do programa?\n1:Adicionar\n2:Sair\n");
        scanf("%d",&sw);
        getchar();

            switch(sw){

                case 1:

                    lista = inserir(lista, tam);
                    tam++;

                break;

                case 2:

                    printf("Fechando programa.\nAs pessoas salvas na lista sao as seguintes:\n");

                    for(int i=0;i<tam;i++){

                    printf("Numero: %d\nNome: %s\nIdade: %d\nAltura: %d\n\n",(i+1),lista[i].nome,lista[i].idade,lista[i].altura);

                    }

                break;

                default:

                    printf("Comando invalido\n");

                break;
            }
    }while(sw != 2);

    free(lista);
}

Pessoa *inserir(Pessoa *lista, int tam){

    if(lista == NULL){

        lista = malloc(sizeof(Pessoa));

    }

    else{

        lista = realloc(lista, ((tam + 1) * sizeof(Pessoa)));
    }

    printf("Digite o nome da pessoa\n");
        scanf("%s",lista[tam].nome);
        getchar();
        printf("Digite a idade da pessoa\n");
        scanf("%d",&lista[tam].idade);
        getchar();
        printf("Digite a altura da pessoa\n");
        scanf("%d",&lista[tam].altura); 
        getchar();   

    return lista;
}

