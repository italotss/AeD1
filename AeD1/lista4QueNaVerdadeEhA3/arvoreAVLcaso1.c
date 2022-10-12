#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Registro{

    long chave;

} Registro;

typedef struct Nodo *Apontador;

typedef struct Nodo{

    Registro reg;
    Apontador pEsq, pDir;
} Nodo;


void Pesquisa(Registro *x, Apontador p);
int FB(Nodo *pRaiz);
int Altura(Nodo *pRaiz);
int Balanceamento(Nodo **ppRaiz);
int Insere(Nodo **ppRaiz, Registro *x);
int verificaAVL(Nodo *pRaiz);
int BalancaEsquerda(Nodo **ppRaiz);
int BalancaDireita(Nodo **ppRaiz);
void geraRand (Registro *reg);
void listaArvore (Nodo *pRaiz);
void Libera (Nodo *pRaiz);
//int Remove(Nodo **ppRaiz, );


int main(){

    //int sw = 0, input = 0;
    
    /*do{
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
                remover(&pRaiz, input);

            break;

            case 3:

                listarArvore(pRaiz);

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

                libera(pRaiz);

        }
    }while(sw != 5); */

    int i, nodos;

    Nodo *pRaiz = NULL;

    Registro input;

    printf("Escolha o numero de nodos:");
    scanf("%d",&nodos);
    getchar();

    for (i=0; i < nodos; i++){
        
        geraRand(&input);
        Insere(&pRaiz, &input);

    }

    printf("\n");
    listaArvore(pRaiz);
    printf("\n");

    if(verificaAVL(pRaiz) == 1){

        printf("\nA arvore eh arvore AVL\n");
    }

    else {
        printf("\nNao eh arvore AVL\n");
    }

    Libera(pRaiz);

    return 0;

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

        Pesquisa(x,p->pDir);
    }
    else *x = p->reg;
}

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


int BalancaEsquerda(Nodo **ppRaiz){

int fbe = FB ((*ppRaiz)->pEsq);

    if (fbe > 0){

        RSD(ppRaiz);
        return 1;
    }

    else if (fbe < 0 ){    
                            //Rotação Dupla Direita 
        RSE(&((*ppRaiz)->pEsq));
        RSD( ppRaiz );  
                            //&(*ppRaiz)
return 1;
}
return 0;
}


int BalancaDireita(Nodo **ppRaiz){

    int fbd = FB((*ppRaiz)->pDir);

    if(fbd < 0){

        RSE(ppRaiz);
        return 1;
    }
    else if(fbd > 0){   //rotacao dupla esquerda

        RSD(&((*ppRaiz)->pDir));
        RSE(ppRaiz);
        return 1;
    }
    return 0;
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



int Insere(Nodo **ppRaiz, Registro *x){

    if (*ppRaiz == NULL){

        *ppRaiz = (Nodo*)malloc(sizeof(Nodo));
        (*ppRaiz)->reg = *x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;

    return 1;
    }

    else if ((*ppRaiz)->reg.chave > x->chave){

        if (Insere(&(*ppRaiz)->pEsq,x)){

            if (Balanceamento(ppRaiz))
            return
            0;

            else
            return 1;
        }
    }

    else if ((*ppRaiz)->reg.chave < x->chave){

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

void geraRand (Registro *input) {

    int random;
    
    random = rand()%1000;
    printf("%d, ", random);
    input->chave = random;

}

void listaArvore (Nodo *pRaiz){

    if (pRaiz != NULL) {
        printf("%d(", pRaiz->reg.chave);
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