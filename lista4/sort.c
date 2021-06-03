#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int *criaVet(int *vetor, int tam);
void insertionSort(int *vetor, int tam);
void selectionSort(int *vetor, int tam);
void quickSort (int *vetor, int low, int high);
void mergeSort(int *vetor, int start, int end);
void merge (int *vetor, int start, int mid, int end);
void listar(int *vetor, int tam);
int verifica(int *vetor, int tam);
float time_diff(struct timeval *start, struct timeval *end);


int main(){

int sw = 0, *vetor , tam;
struct timeval begin, end;
srand(time(NULL));

    do{
        printf("\n1:Insertion sort\n2:Selection sort\n3:Quick sort\n4:Merge sort\n5:Sair\n\nEscolha:");
        scanf("%d",&sw);

        switch(sw){

            case 1:

                printf("\nInsira o tamanho do vetor:");
                scanf("%d",&tam);
                getchar();

                vetor = criaVet(vetor, tam);
                listar(vetor, tam);
                gettimeofday(&begin, NULL);
                insertionSort(vetor, tam);
                gettimeofday(&end, NULL);
                listar(vetor, tam);
        
                if(verifica(vetor, tam -1))
                    printf("\nVetor ta organizado\n");
                else
                    printf("\nVetor nao ta organizado\n");

                printf("\nExecucao demorou %f segundos;\n", time_diff(&begin, &end));    

            free(vetor);

            break;

            case 2:

                printf("\nInsira o tamanho do vetor:");
                scanf("%d",&tam);
                getchar();

                vetor = criaVet(vetor, tam);
                listar(vetor, tam);
                gettimeofday(&begin, NULL);
                selectionSort(vetor, tam);
                gettimeofday(&end, NULL);
                listar(vetor, tam);
        
                if(verifica(vetor, tam -1))
                    printf("\nVetor ta organizado\n");
                else
                    printf("\nVetor nao ta organizado\n");

                printf("\nExecucao demorou %f segundos;\n", time_diff(&begin, &end));    

            free(vetor);

            break;

            case 3:

                printf("\nInsira o tamanho do vetor:");
                scanf("%d",&tam);
                getchar();

                vetor = criaVet(vetor, tam);
                listar(vetor, tam);
                gettimeofday(&begin, NULL);
                quickSort(vetor, 0, tam -1);
                gettimeofday(&end, NULL);
                listar(vetor, tam);
        
                if(verifica(vetor, tam -1))
                    printf("\nVetor ta organizado\n");
                else
                    printf("\nVetor nao ta organizado\n");

                printf("\nExecucao demorou %f segundos;\n", time_diff(&begin, &end));    

            free(vetor);

            break;

            case 4:

                printf("\nInsira o tamanho do vetor:");
                scanf("%d",&tam);
                getchar();

                vetor = criaVet(vetor, tam);
                listar(vetor, tam);
                gettimeofday(&begin, NULL);
                mergeSort(vetor, 0, tam -1);
                gettimeofday(&end, NULL);
                listar(vetor, tam);
        
                if(verifica(vetor, tam -1))
                    printf("\nVetor ta organizado\n");
                else
                    printf("\nVetor nao ta organizado\n");

                printf("\nExecucao demorou %f segundos;\n", time_diff(&begin, &end));    

            free(vetor);

            break;

            case 5:

                printf("\nFechando\n");

            break;

            default:

            break;
        }
    }while(sw!=5);
}

int *criaVet(int *vetor, int tam){

    srand(time(NULL));

    //printf("\nQual o tamanho do vetor?");
    //scanf("%d",&tamanho);
    //getchar();

    vetor = malloc(sizeof(int) * tam);

    for (int i=0; i < tam; i++)
        vetor[i] = rand ();

return vetor;
}

void listar(int *vetor, int tam){

    printf("\n");
  
    for (int i = 0; i < tam; i++) 
        printf("%d ", vetor[i]);

    printf("\n");

}

void insertionSort(int *vetor, int tam){

int j, aux;

    for (int i=1; i < tam; i++) {

    j = i - 1;
    aux = vetor[i];

        while ((j >= 0) && (vetor[j] > aux)) {
            vetor[j+1] = vetor[j];
            j--;
        }

    vetor[j+1] = aux;
    }
}

void selectionSort(int *vetor, int tam){

    int i, j, menor_ele = 0,aux; 
    
    for (i = 0; i < tam-1; i++) 
    { 
       
        menor_ele = i; 
        for (j = i+1; j < tam; j++) 

            if (vetor[j] < vetor[menor_ele]) 
                menor_ele = j; 
  
        aux = vetor[menor_ele];
        vetor[menor_ele] = vetor[i];
        vetor[i] = aux;

    } 
} 

void quickSort (int *vetor, int low, int high) {

    int pivo, aux, i, j;
    i = low;
    j = high;

    pivo = vetor[ low + (rand() % ( high - low))];

    do{

        while ( vetor[i] < pivo ) {
            i++;
        }
        while (pivo < vetor[j]) {
            j--;
        }
        
        if ( i <= j) {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }

    }while (i <= j);

    if (low < j) {
        quickSort(vetor, low, j);
    }
    if (i < high) {
        quickSort (vetor, i, high);
    }
}

void mergeSort(int *vetor, int start, int end){

    if (start < end){

        int mid;

        mid = start + (end - start)/2;

        mergeSort(vetor, start, mid);
        mergeSort(vetor, mid +1, end);

        merge (vetor, start, mid, end);
    }

}

void merge (int *vetor, int start, int mid, int end){
    
    int *temp, p1, p2, tam, i, j, k;
    int end1 = 0, end2 = 0;
    tam = end-start+1;
    p1 = start;
    p2 = mid +1;

    temp = (int *)malloc(tam * sizeof(int));

    if (temp != NULL){
        for(i=0; i < tam; i++){
            if((!end1) && (!end2)){

                if (vetor[p1] < vetor[p2]){
                    temp[i] = vetor[p1++];
                }
                else{
                    temp[i] = vetor[p2++];
                }

                if(p1>mid){
                    end1=1;
                }
                if(p2>end){
                    end2=1;
                }
            }
            else{
                if(!end1){
                    temp[i] = vetor[p1++];
                }
                else{
                    temp[i] = vetor[p2++];
                }
            }
        }
        for(j=0, k=start; j < tam; j++, k++){
            vetor[k] = temp[j];
        }
    }

    free (temp);
}

int verifica(int *vetor, int tam){

    int flag = 0, i;

        for (i=0; i < tam; i++) {

            if(vetor[i] > vetor[i+1]) {
                flag++;
            }

        }
        if (flag == 0) {
            return 1;
        }
        else {
            return 0;
        }


}

float time_diff(struct timeval *start, struct timeval *end){

    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}