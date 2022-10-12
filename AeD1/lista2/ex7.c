#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[30];
    int idade;
    int altura;
}Pessoa;

Pessoa pessoas[10]; // vetor global

void *incluir(void *pBuffer, int *nPessoas);
void *apagar(void *pBuffer, int *nPessoas, int *flag, int *i, char *nomeAux);
void buscar(void *pBuffer,int *nPessoas, int *flag, int *i, char*nomeAux);
void listar(void *pBuffer,int *nPessoas, int *i);

int main(){

    int *nPessoas, *flag, *i, *sw; //ponteiros que apontarao para os enderecos dentro do pBuffer
    char *nomeAux;

    void *pBuffer = NULL;

    pBuffer = malloc((4 * sizeof(int)) + (30 *sizeof(char))); //em ordem, o numero de pessoas,  flag,  index,  switch, e um espaco auxiliar para nome

    *(int *)(pBuffer) = 0;

    nPessoas = (int *)(pBuffer); //faz os ponteiros apontarem para suas posicoes no pbuffer e os inicializa em 0
    *nPessoas = 0;

    flag = (int *)(pBuffer + sizeof(int));
    *flag = 0;

    i = (int *)(pBuffer + sizeof(int) + sizeof(int));
    *i = 0;

    sw = (int *)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int));
    *sw = 0;

    nomeAux = (char *)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (30 * sizeof(char)));

    do{
            printf("Escolha:\n1:Incluir pessoa\n2:Apagar pessoa\n3:Buscar info de uma pessoa\n4:Listar todos os nomes\n5:Sair do programa\n");
            scanf("%d",sw);
            getchar();
            switch (*sw)
            {
            case 1:

                incluir(pBuffer, nPessoas);

                break;

            case 2:

                apagar(pBuffer, nPessoas, flag, i, nomeAux);

                break;

            case 3:

                buscar(pBuffer, nPessoas, flag, i, nomeAux);

                break;

            case 4:

                listar(pBuffer, nPessoas, i);

                break;

            case 5:   

                printf("Fechando programa.\n");

                break;
            default:

                printf("Entrada invalida.\n");
                break;
            }
        }while(*sw != 5);

        free(pBuffer);
        return 0;
}


 void *incluir(void *pBuffer, int *nPessoas){

    if(*nPessoas <= 10){ //verifica se ha espaco na lista

        printf("Informe o nome:\n");
        scanf("%s", pessoas[*nPessoas].nome);
        getchar();

        printf("Informe a idade:\n");
        scanf("%d", &pessoas[*nPessoas].idade);
        getchar();

        printf("Informe a altura:\n");
        scanf("%d", &pessoas[*nPessoas].altura);
        getchar();

    *nPessoas=(*nPessoas + 1);
    return 0;
    }
    else{
        printf("O vetor esta cheio.\n");
        return 0;
    }
 }

void *apagar(void *pBuffer, int *nPessoas, int *flag, int *i, char *nomeAux){

    if(*nPessoas == 0){
        printf("Nao ha ninguem para ser removido.\n");
    }
    else{

        printf("Informe o nome: \n");
        scanf("%s", nomeAux);
        getchar();
        for(*i=0;*i<*nPessoas;*i=(*i+1)){ //for comparando a iteracao do i com o numero total
            
            if(strcmp((char*)nomeAux, pessoas[*i].nome) == 0){

                *flag = 1;

                strcpy(pessoas[*i].nome, pessoas[*nPessoas -1].nome); // -1 pq o nPessoas e sempre 1 maior que o vetor
                pessoas[*i].idade = pessoas[*nPessoas -1].idade;
                pessoas[*i].altura = pessoas[*nPessoas -1].altura; // copia a info do ultimo usuario e coloca no lugar do removido

                pessoas[*nPessoas -1].nome[0] ='\0'; // apaga o ultimo nome
                pessoas[*nPessoas -1].idade = 0;
                pessoas[*nPessoas -1].altura = 0;

                printf("Nome removido.\n");
                *nPessoas=(*nPessoas - 1);
            }
        }
        if(*flag == 0){

            printf("O nome nao estava na lista.\n");
        }
    *flag = 0;    
    }
return 0;    
}

void buscar(void *pBuffer,int *nPessoas, int *flag, int *i, char*nomeAux){
 
    if(*nPessoas == 0){
        printf("Nao ha ninguem na lista\n");
    }
    else{
        
        printf("Informe o nome para buscar: \n");
        scanf("%s", nomeAux);
        getchar();
        for(*i = 0;*i<*nPessoas && *flag == 0;*i=(*i+1)){ //for comparando a iteracao do i com o numero total. tambem usa a flag pra sair do for cedo
            
            if(strcmp((char*)nomeAux, pessoas[*i].nome) == 0){

                *flag = 1;
                printf("\nUsuario encontrado.\nNome:%s\nIdade:%d\nAltura:%d\n\n", pessoas[*i].nome, pessoas[*i].idade, pessoas[*i].altura);
            } 
        }
        if(*flag == 0){
            printf("O nome nao estava na lista.\n");
        }
    }
    *flag = 0;
}

void listar(void *pBuffer, int *nPessoas, int *i){

    if(*nPessoas == 0){
        printf("Nao ha ninguem na lista\n");
    }
    else{
        
        printf("Listando:\n\n");
        for(*i=0;*i<*nPessoas;*i=*i+1){
            printf("Nome:%s\n\n", pessoas[*i].nome);
        }
    }
}