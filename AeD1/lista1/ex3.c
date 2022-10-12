#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *incluir(void *pBuffer);
void *apagar(void *pBuffer);
char *leNome(void);
void buscar(void *pBuffer);
void listar(void *pBuffer);

    int main(){
            
        void *pBuffer = NULL;
        int sw;
        pBuffer = malloc (sizeof(int));

        *(int *)pBuffer = 0;

        do{
            printf("Escolha:\n1:Incluir pessoa\n2:Apagar pessoa\n3:Listar todos os nomes\n4:Buscar info de uma pessoa\n5:Sair do programa\n");
            scanf("%d",&sw);
            getchar();
            switch (sw)
            {
            case 1:
                pBuffer = incluir(pBuffer);

                break;

            case 2:
                pBuffer = apagar(pBuffer);

                break;

            case 3:

                listar(pBuffer);

                break;

            case 4:

                buscar(pBuffer);

                break;

            case 5:   

                printf("Fechando programa\n");

                break;
            default:

                printf("Entrada invalida\n");
                break;
            }
        }while(sw != 5);

        free(pBuffer);
        return 0;
    }

void *incluir(void *pBuffer){

    pBuffer = realloc(pBuffer, sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * ((*(int*)pBuffer) + 1))); //aloca espaco dinamicamente sem afetar a cabeca
    printf("Digite o nome a ser incluido\n");

    scanf("%s",(char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)pBuffer))); // nome adicionado
    getchar();

    printf("Digite a idade a do individuo\n");
    scanf("%d",(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)pBuffer)))); // idade adicionada
    getchar();

    printf("Digite o numero do individuo\n");
    scanf("%d",(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)pBuffer)))); // telefone adicionado
    getchar();

    *(int *)(pBuffer) = *(int *)(pBuffer) + 1; //incrementa o numero de pessoas
    return pBuffer;
}    

void *apagar(void *pBuffer){

    char *nomeApagado = NULL;

    nomeApagado = leNome();

    if(*(int *)pBuffer == 0){
        printf("pBuffer ESTA VAZIO\n");

        free(nomeApagado);
        return pBuffer;
    }
    else{

        for(int i=0; i<=*(int*)pBuffer; i++){

            if (strcmp(nomeApagado, (char *)pBuffer + sizeof(int) + ((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i) == 0){  //percorre procurando o nome apagado

                strcpy((char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i), (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)(pBuffer)-1))); //coloca o ultimo nome no lugar do apagado

                *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i))) = *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)(pBuffer)-1))); //coloca a ultima idade no lugar do apagado

                *(int *)(pBuffer + sizeof(int) + ((10 * sizeof(char)) + sizeof(int)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)) = *(int *)(pBuffer + sizeof(int) + ((10 * sizeof(char)) + sizeof(int)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)(pBuffer)-1))); //coloca o ultimo numero no lugar do apagado

                *(int *)(pBuffer) = *(int *)(pBuffer) - 1;

                pBuffer = realloc(pBuffer, sizeof(int) + ((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * ((*(int*)pBuffer)));
                printf("%s removido\n", nomeApagado);

                free(nomeApagado);
                return pBuffer;  //retorna para o main apos remover o nome.
            }
        }
    }
    free(nomeApagado);
    return pBuffer;
}

void buscar(void *pBuffer){

    char *nomeBuscado = NULL;

    nomeBuscado = leNome();
    
    if(*(int *)pBuffer == 0){
        printf("pBuffer ESTA VAZIO\n");
    }
    else{

        for(int i=0; i<*(int*)pBuffer; i++){

            if (strcmp(nomeBuscado, ((char *)pBuffer + sizeof(int) + ((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)) == 0){  //percorre procurando o nome

                printf("Encontrado!\n Nome: %s\n",(char *)pBuffer + sizeof(int) + ((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i);
                printf("Idade: %d\n",*(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));
                printf("Numero: %d\n",*(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + ((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i));
        } //encontra todos com o nome buscado
    }
    free(nomeBuscado);
    }
}

char *leNome(void){

    char *nomeLido = NULL;

    nomeLido = (char*)malloc(10 * sizeof(char));

    printf("Informe o nome: ");
    scanf("%[^\n]s", nomeLido);

    getchar();

    return nomeLido;
}

void listar(void *pBuffer){

    if(*(int *)pBuffer == 0){
        printf("pBuffer ESTA VAZIO\n");
    }
    else{

        for(int i=0; i<*(int*)pBuffer; i++){

            printf("Nome: %s\n",(char *)pBuffer + sizeof(int) + ((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i);
            //printf("Idade: %d\n",*(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + ((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i));
            //printf("Numero: %d\n\n",*(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + ((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i));
        }
    }
}