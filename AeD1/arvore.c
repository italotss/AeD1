#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Registro{

    long chave;
} Registro;

typedef struct Nodo{

    Registro reg;
    Apontador pEsq, pDir;
} Nodo;

typedef struct Nodo * Apontador;

void Pesquisa(Registro *x, Apontador p);
void Insere(Registro x, Apontador *p);

int main(){

    
}

void Pesquisa(Registro *x, Apontador p){

    if(p == NULL){
        printf("Registro não esta na arvore.\n");
        return;
    }
    if(x->chave < p->reg.chave){
        
        Pesquisa(x,p->pEsq);
        return;
    }
    if(x->chave > p->reg.chave){

        pesquisa(x,p->pDir);
    }
    else *x = p->reg;
}

void Insere(Registro x, Apontador *p){

    if (*p == NULL){
        
        *p = (Apontador)malloc(sizeof(Nodo));
        (*p)->Reg = x;
        (*p)->pEsq = NULL;
        (*p)->pDir = NULL;
        return;
    }

    if(x.chave < (*p)->reg.chave){

        Insere(x, &(*p)->pEsq);
        return;
    }

    if (x.chave > (*p)->reg.chave){
        Insere(x, &(*p)->pDir);
    }
    else
        printf("Registro ja existe na arvore.\n");
}