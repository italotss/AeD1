#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *inserir(char *listaNomes); //funcoes usadas no codigo
char *leString(void);
char *remover(char *listaNomes);
void listar(char *listaNomes);

int main(){

    char *listaNomes = NULL; //cria a lista
    int opcao;

    do{
        printf("1.Inserir\n2.Remover\n3.Listar\n4.Sair\n"); 
        scanf("%d", &opcao);
        getchar();

        switch (opcao){ 

            case 1: listaNomes = inserir(listaNomes);
                break; 

            case 2: listaNomes = remover(listaNomes);
                break;

            case 3: listar(listaNomes);

            case 4: break;       
        }
    } while(opcao != 4);

    free (listaNomes);
    return 0;

}

char *inserir (char *listaNomes) {

    int tamanhoNome = 0, tamanhoLista = 0; char *novoNome = NULL;

    novoNome = leString();  //le o nome com uma funcao auxiliar

    if(!listaNomes){ //caso seja o primeiro nome da lista

        tamanhoNome = strlen(novoNome) + 1; //espaco para ;

        listaNomes = (char*)malloc ((tamanhoNome + 1) * sizeof(char));  
        strcpy(listaNomes,novoNome);
        strcat(listaNomes,";");
    }
    
    else{  //para nomes subsequentes

        tamanhoNome = strlen(novoNome) + 1; //espaco para ;
        tamanhoLista = strlen(listaNomes);

        listaNomes = (char*)realloc(listaNomes, (tamanhoLista + tamanhoNome + 1) * sizeof(char));
        strcat(listaNomes,novoNome);
        strcat(listaNomes,";");
    }

    free(novoNome);
    return listaNomes;
}

char *remover (char *listaNomes){  

    if(listaNomes == NULL){
        printf("Nao ha nomes para remover\n");

        return NULL;
    }

    else{

        char *nomeRemovido = NULL, *listaNomesAux = NULL, nomeAtual[20];
        int tamanhoNovo = 0,tamanhoNomeAtual = 0, tamanhoLista = strlen(listaNomes), tamanhoListaAux = 0, i = 0, j = 0;  //cria uma string auxiliar

        nomeRemovido = leString();

            for(i=0; i <tamanhoLista ; i++){ //percorre palavra por palavra
                j=0;

            while(listaNomes[i] != ';'){
                nomeAtual[j++] = listaNomes[i++]; //salva em dois vetores para comparar as palavras
            }
                nomeAtual[j] = '\0'; // coloca fim na string
                
                tamanhoNomeAtual = strlen(nomeAtual) + 1; //inclui '\0'
                
            if (strcmp(nomeAtual,nomeRemovido) != 0){ // usa a mesma logica da funcao de inserir parar criar uma lista diferente sem o nome removido

                if(listaNomesAux == NULL){

                    tamanhoNovo = tamanhoNomeAtual + 1;
                    listaNomesAux = (char*)malloc ((tamanhoNomeAtual + 1) * sizeof(char));
                    strcpy(listaNomesAux,nomeAtual);
                    strcat(listaNomesAux,";");

                }
                else{
                    
                    tamanhoNovo = tamanhoListaAux + tamanhoNomeAtual + 1; //inclui espaco para;
                    listaNomesAux = (char*)realloc (listaNomesAux, (tamanhoListaAux + tamanhoNomeAtual) * sizeof(char));
                    strcat(listaNomesAux,nomeAtual);
                    strcat(listaNomesAux,";");

                }
            }
            tamanhoListaAux = tamanhoNovo;  //atualiza o tamanho da lista auxiliar
                
            }
            free(listaNomes);
            free(nomeRemovido);

            return listaNomesAux; //retorna a lista nova
        }
}

void listar(char *listaNomes) {

    if(listaNomes == NULL){
            printf("Nao ha nomes para listar\n");
        }

        else{

            while(*listaNomes) {
                if (*listaNomes != ';') 
                    printf("%c", *listaNomes++);
                else {
                    printf("\n");
                    listaNomes++;
                     }
                }
            }
}

char *leString(void) {
    char *novoNome = NULL;

    novoNome = (char*)malloc(20 * sizeof(char));

    printf("Informe um nome: ");
    scanf("%[^\n]s", novoNome);

    getchar();

    return novoNome;
}
