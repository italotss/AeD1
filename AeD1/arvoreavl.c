#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Registro{

    long chave;

} Registro;

typedef struct Nodo{

    Registro reg;
    struct Nodo *pEsq;
    struct Nodo *pDir;


} Nodo;

//typedef struct Nodo *Apontador;

//void Pesquisa(Registro *x, Apontador p);
int Insere(Nodo **ppRaiz, int x);
int Remove(Nodo **ppRaiz, int x);
int FB(Nodo *pRaiz);
int Altura(Nodo *pRaiz);
int Balanceamento(Nodo **ppRaiz);
int BalancaEsquerda(Nodo **ppRaiz);
int BalancaDireita(Nodo **ppRaiz);
Nodo *procuraMenor (Nodo *atual);
int verificaAVL(Nodo *pRaiz);
void listaArvore (Nodo *pRaiz);
void Libera (Nodo *pRaiz);


int main(){

    int sw = 0;
    int input;

    Nodo *pRaiz = NULL;
    
    do{
        printf("\n1:Inserir elemento na arvore\n2:Remover elemento da arvore\n3:Listar arvore\n4:Testar se a arvore e AVL\n5:Sair do programa\n\nEscolha:");
        scanf("%d",&sw);

        switch(sw){

            case 1:

                printf("Digite o elemento inserido:");
                scanf("%d",&input);
                getchar();
                Insere(&pRaiz, input);

            break;

            case 2:

                printf("Digite o elemento removido:");
                scanf("%d", &input);
                getchar();
                Remove(&pRaiz, input);

            break;

            case 3:

                listaArvore(pRaiz);

            break;

            case 4:

                if(verificaAVL(pRaiz)){

                    printf("\nA arvore eh AVL\n");
                }

                else{

                    printf("\nNao eh AVL\n");
                }

            break;

            case 5:

                Libera(pRaiz);

        }
    }while(sw != 5);
}

/*void Pesquisa(Registro *x, Apontador p){

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
} */

int FB (Nodo *pRaiz){

    if (pRaiz == NULL)
    return 0;

    return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);
    }

int Altura(Nodo *pRaiz){

    int iEsq,iDir;

    if (pRaiz == NULL)
    return 0;

    iEsq = Altura(pRaiz->pEsq);
    iDir = Altura(pRaiz->pDir);

    if ( iEsq > iDir )
    return iEsq + 1;

    else
    return iDir + 1;
}


void RSE(Nodo **ppRaiz){

    Nodo *pAux;
    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}


void RSD(Nodo **ppRaiz){

    Nodo *pAux;
    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int Balanceamento(Nodo **ppRaiz){

    int fb = FB(*ppRaiz);

    if(fb > 1)
        return BalancaEsquerda(ppRaiz);

    else if(fb < -1)
        return BalancaDireita(ppRaiz);
    
    else 
        return 0;
}


int BalancaEsquerda(Nodo **ppRaiz){

    int fbe = FB ((*ppRaiz)->pEsq);

        if (fbe >= 0){

            RSD(ppRaiz);
            return 1;
        }

         else if (fbe < 0 ){    
                            
            RSE(&((*ppRaiz)->pEsq));
            RSD( ppRaiz );  
                            
    return 1;
    }
return 0;
}


int BalancaDireita(Nodo **ppRaiz){

    int fbd = FB((*ppRaiz)->pDir);

    if(fbd <= 0){

        RSE(ppRaiz);
        return 1;
    }
    else if(fbd > 0){  

        RSD(&((*ppRaiz)->pDir));
        RSE(ppRaiz);
        return 1;
    }
    return 0;
}


int Insere(Nodo **ppRaiz, int x){

    if (*ppRaiz == NULL){

        *ppRaiz = (Nodo*)malloc(sizeof(Nodo));
        (*ppRaiz)->reg.chave = x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;

    return 1;
    }

    else if ((*ppRaiz)->reg.chave > x){

        if (Insere(&(*ppRaiz)->pEsq,x)){

            if (Balanceamento(ppRaiz))
            return
            0;

            else
            return 1;
        }
    }

    else if ((*ppRaiz)->reg.chave < x){

        if(Insere(&(*ppRaiz)->pDir,x)){

            if(Balanceamento(ppRaiz))
                return 0;
            
            else
                return 1;
        }

        else 
            return 0;
    }
    else
        return 0;

    return 0;     
}


int Remove (Nodo **ppRaiz, int x){

    int resposta;
    if (*ppRaiz == NULL){ 

        printf("\nArvore esta vazia;\n");
        return 0;

    }

    if ( x < (*ppRaiz)->reg.chave){
        if ((resposta = Remove (&(*ppRaiz)->pEsq, x)) == 1){ 
            
            Balanceamento(ppRaiz);

        }
    }
    
    if (( x > (*ppRaiz)->reg.chave)){
        if ((resposta = Remove ( &(*ppRaiz)->pDir, x)) == 1){ 

            Balanceamento(ppRaiz);

        }
    }
    if ((x == (*ppRaiz)->reg.chave)){
        if ((*ppRaiz)->pEsq == NULL || (*ppRaiz)->pDir == NULL){
            Nodo *oldNode = (*ppRaiz);
            if ((*ppRaiz)->pEsq != NULL){
                *ppRaiz = (*ppRaiz)->pEsq;
            }
            else{
                *ppRaiz = (*ppRaiz)->pDir;
            }
            free(oldNode);
        }
        else{

            Nodo *temp = procuraMenor((*ppRaiz)->pDir);
            (*ppRaiz)->reg.chave = temp->reg.chave;
            Remove(&(*ppRaiz)->pDir, (*ppRaiz)->reg.chave);
            Balanceamento(ppRaiz);
            
        }
        return 1;
    }
    return resposta;
}


int verificaAVL(Nodo* pRaiz){

    int fb;

    if (pRaiz == NULL)
        return 1;

    if (!verificaAVL(pRaiz->pEsq))
        return 0;

    if (!verificaAVL(pRaiz->pDir))
        return 0;

    fb = FB (pRaiz);

    if (( fb > 1 ) || ( fb <-1))
        return 0;

    else
        return 1;
}


void listaArvore (Nodo *pRaiz){

    if (pRaiz != NULL) {
        printf("%ld(", pRaiz->reg.chave);
        listaArvore(pRaiz->pEsq);
        listaArvore(pRaiz->pDir);
        printf(")");
    }

}

void Libera (Nodo *pRaiz){

    if (pRaiz == NULL) 
        return;
    
    Libera(pRaiz->pEsq);
    Libera(pRaiz->pDir);

    free(pRaiz);
}


Nodo *procuraMenor (Nodo *atual){

    Nodo *no1 = atual;
    Nodo *no2 = atual->pEsq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->pEsq;
    }
    return no1;
}