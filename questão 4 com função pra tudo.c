#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ler(char*** str, int* indice) {
    //ponteiro triplo q aponta para a matriz

    int flag = 1;

    while (flag) {

        /*daqui até o fim da função a gente manipluna da mesma forma, a diferença é q são os ponteiros apontando para os indices da matriz*/
        (*str)[*indice] = (char*)malloc(1000 * sizeof(char));

        if ((*str)[*indice] == NULL) {
            printf("deu errado essa porra ae");
            flag = 0;
        }

        printf("digite a string: \n");

        if (fgets((*str)[*indice], 1000, stdin) != NULL) {
            if ((*str)[*indice][0] == '\n') {
                flag = 0;
            }
            
            else {
                (*str)[*indice][strcspn((*str)[*indice], "\n")] = '\0';
                (*indice)++;
                *str = realloc(*str, (*indice + 1) * sizeof(char*));

                if (*str == NULL) {
                    printf("\n deu ruim isso aí ein\n");
                    flag = 0;
                }
            }
        }
        
        else {
            flag = 0;
        }
    }
}

void mostrar(char*** str, int* indice){
    printf("\nas strings\n");
    for(int i = 0; i < *indice ; i++){
        printf("%s\n", (*str)[i]);
    }
}

void apagar(char*** str, int* indice){
    for(int i = 0; i < *indice ; i++){
        printf("apagando a strins '%s'\n", (*str)[i]);
        free((*str)[i]);
    }
    printf("apagando o resquicio da matriz\n");
    free((*str));
}


int main(){
    char** str = NULL;

    str = (char**)malloc(1 * sizeof(char*)); //malocando a quantidade de strings

    if(str == NULL){
        printf("\ndeu mto ruim saporra\n");
    }

    int indice = 0;

    ler(&str, &indice);
    
    mostrar(&str, &indice);

    apagar(&str, &indice);

    printf("\n\naté mais...\n\n");

    return 0;
}
