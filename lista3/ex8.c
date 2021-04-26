#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Dados { // formato da info das pessoas
        char nome[10];
        int idade, numero;
} Dados;

typedef struct Nodo { // nodo usado para formar a lista
        Dados info;
        struct Nodo *prox;
        struct Nodo *ant;
} Nodo;

typedef struct Base { // sentinela da lista
        Nodo *start;
        Nodo *end;
} Base;

#define menorTamanho *(int*)(pBuffer)
#define sw *(int*)(pBuffer + sizeof(int))
#define i *(int*)(pBuffer + sizeof(int) * 2)
#define flag *(int*)(pBuffer + sizeof(int) * 3)
#define nomeAux (char*)(pBuffer + sizeof(int) * 4)
#define maiorTamanho *(int*)(pBuffer + (sizeof(int) * 4) + (10 * sizeof(char)))

Base *constroi(void);
void inserir(Base *lista, void *pBuffer);
void remover(Base *lista, void *pBuffer);
void listar(Base *lista, void *pBuffer);
void listaraux(Base *lista, void *pBuffer);
void buscar(Base *lista, void *pBuffer);
void liberar(Base *lista);
void ordenaIdade(Base *lista, void *pBuffer);
void ordenaNum(Base *lista, void *pBuffer);
void push (Base *lista, Nodo *recebido, void *pBuffer);
void pop (Nodo *listado);


int main () {

    void *pBuffer = NULL;
    Base *lista = NULL;
    pBuffer = malloc((sizeof(int) * 4) + (10 * sizeof(char)) + sizeof(int)); // numero de pessoas, seletor, i, flag, nomes
    flag = 0;

    lista = constroi();

    do{

    printf("Escolha:\n1:Inserir na lista\n2:Remover da lista\n3:Buscar pessoa\n4:Listar\n5:Listar ordenadamente\n6:Sair\n");
    scanf("%d", &sw);
    getchar();

        switch(sw){

            case 1:

                inserir(lista, pBuffer);
            break;

            case 2:

                remover(lista, pBuffer);
            break;

            case 3:

                buscar(lista, pBuffer);
            break;

            case 4:

                listar(lista, pBuffer);
            break;  

            case 5:

                printf("\nDeseja ordenar por:\n1:Idade\n2:Numero\n");
                scanf("%d", &sw);
                getchar();

                    if(sw == 1){
                        ordenaIdade(lista, pBuffer);
                    }
                    else if(sw == 2){
                       ordenaNum(lista, pBuffer);
                    }
            break;  

            case 6:

                printf("Fechando programa.\n");
                liberar(lista);
                free(pBuffer);

            return 0;

            default:
                printf("Comando invalido.\n");
            break;
        }
    }while(sw != 6);
}

Base *constroi(void){

    Base *lista;
    lista = (Base*)malloc(sizeof(Base));

    lista->start = NULL;
    lista->end = NULL;

    return lista;
}

void inserir(Base *lista, void *pBuffer){

    Nodo *novo = NULL;

    novo = (Nodo*)malloc(sizeof(Nodo));

    novo->prox = NULL;
    novo->ant = NULL;

    if (lista->start == NULL) { // verifica se eh o primeiro nome da lista
            lista->start = novo;

        }
        else {
            
            novo->ant = lista->end;
            lista->end->prox = novo;
        }

    printf("Escolha o nome do inserido \n");
    scanf("%s", novo->info.nome);
    printf("Escolha a idade do inserido \n");
    scanf("%d", &novo->info.idade);
    printf("Escolha o numero do inserido \n");
    scanf("%d", &novo->info.numero);

    lista->end = novo;
}

void remover(Base *lista, void *pBuffer){


    if (lista->start == NULL) {

        printf("\nLista vazia.\n\n");

        return;
    }

    else{

        Nodo *removido = lista->start;

        printf("Escolha o nome do removido \n");
        scanf("%s",nomeAux);
        getchar();

        for(removido = lista->start ;removido != NULL; removido = removido->prox){

            if(strcmp(removido->info.nome,nomeAux) == 0){

                if(removido->ant == NULL && removido->prox == NULL){ //testa se for o unico da lista

                    lista->start = NULL;
                    lista->end = NULL;

                    free(removido);
                    return;
                }

                else if(removido->ant == NULL){ // se for o primeiro da lista

                    removido->prox->ant = NULL;
                    lista->start = removido->prox;

                    free(removido);
                    return;

                } 

                if(removido->ant != NULL && removido->prox != NULL){ // se estiver no meio da lista

                    removido->ant->prox = removido->prox;
                    removido->prox->ant = removido->ant;

                    free(removido);
                    return;
                }

                else if(removido->ant != NULL && removido ->prox == NULL){ // se for o ultimo da lista

                    lista->end = removido->ant;
                    removido->ant->prox = NULL;
                    
                    free(removido);
                    return;
                }
            }
        }
    }
}

void listar(Base *lista, void *pBuffer){

    if (lista->start == NULL) {

        printf("\nLista vazia.\n\n");

        return;
    }

    Nodo *listando = lista->start;
    printf("Mostrando todos os usuarios:\n\n");

    for(listando = lista->start ; listando != NULL; listando=listando->prox){

        printf("Nome:%s \n",listando->info.nome);

    }
    printf("\nListagem completa.\n\n");
    free(listando);
    return;
}

void buscar(Base *lista, void *pBuffer){

    if (lista->start == NULL) {

        printf("\nLista vazia.\n\n");

        return;
    }

    Nodo *buscado = lista->start;
    printf("Quem esta procurando? \n");
    scanf("%s", nomeAux);
    getchar();

    for(buscado = lista->start ; buscado != NULL && flag == 0 ; buscado = buscado->prox ){ //percorre a lista procurando o nome. se encontrar ativa a flag e printa o nome

        if(strcmp(nomeAux, buscado->info.nome) == 0){

            printf("\nEncontrado.\nNome: %s\nIdade: %d\nNumero: %d\n\n", buscado->info.nome, buscado->info.idade, buscado->info.numero);
            flag = 1;
        }
    }

    if(flag == 1){ //testa se o nome foi encontrado antes de retornar

        flag = 0;
        return;

    }

    else{

        printf("\nNome nao encontrado na lista.\n\n");
        return;
    }
}

void ordenaIdade(Base *lista, void *pBuffer){

    Base *ordenada = NULL;
    ordenada = constroi();

    Nodo *auxA, *auxB, *auxC;

    menorTamanho = -1;

    for(auxA = lista->start; auxA != NULL; auxA = auxA->prox){

        maiorTamanho = 2147483647;

        for(auxB = lista->start; auxB != NULL; auxB = auxB->prox){

            if (auxB->info.idade > menorTamanho && auxB->info.idade < maiorTamanho){
                    maiorTamanho = auxB->info.idade;
            }
        }

        menorTamanho = maiorTamanho; // modifica para a proxima iteracao
    
        for(auxC = lista->start ; auxC != NULL ; auxC = auxC->prox){

            if(auxC->info.idade == menorTamanho){

                push(ordenada,auxC,pBuffer);
            }
        }
    }
    listaraux(ordenada,pBuffer);
}

void ordenaNum(Base *lista, void *pBuffer){

    Base *ordenada = NULL;
    ordenada = constroi();

    Nodo *auxA, *auxB, *auxC;

    menorTamanho = -1;

    for(auxA = lista->start; auxA != NULL; auxA = auxA->prox){

        maiorTamanho = 2147483647;

        for(auxB = lista->start; auxB != NULL; auxB = auxB->prox){

            if (auxB->info.numero > menorTamanho && auxB->info.numero < maiorTamanho){
                    maiorTamanho = auxB->info.numero;
            }
        }

        menorTamanho = maiorTamanho; // modifica para a proxima iteracao
    
        for(auxC = lista->start ; auxC != NULL ; auxC = auxC->prox){

            if(auxC->info.numero == menorTamanho){

                push(ordenada,auxC,pBuffer);
            }
        }
    }
    listaraux(ordenada,pBuffer);

}




void push(Base *lista, Nodo *recebido, void *pBuffer){

    Nodo *novo;
    novo = (Nodo*)malloc(sizeof(Nodo));
    novo->prox = NULL;
    novo->ant = NULL;

    strcpy(novo->info.nome, recebido->info.nome);
        novo->info.idade = recebido->info.idade;
        novo->info.numero = recebido->info.numero;

    if (lista->start == NULL) {
        lista->start = novo;
    }
    else {
        novo->ant = lista->end;
        lista->end->prox = novo;
    }
    lista->end = novo;
}

void listaraux(Base *lista, void *pBuffer){

    if (lista->start == NULL) {

        printf("\nLista vazia.\n\n");
        
    }

    else{

        Nodo *listado = lista->start, *aux;
    
        while(listado != NULL) {

            aux = listado->prox;
            pop(listado);
            listado = aux;

        }
        free(lista);
    }

}

void pop(Nodo *listado) {

    printf("\nNome: %s\n", listado->info.nome);
    printf("Idade: %d\n", listado->info.idade);
    printf("Telefone %d\n\n", listado->info.numero);
    free(listado);
    
}

void liberar(Base *lista){

    Nodo *aux, *aux2;
    aux = lista->start;

    while(aux != NULL){

        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(lista);
    return;
}