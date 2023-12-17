#include <stdio.h>

int main(){
    int vet[5] = {1,2,3,4,5};
    int* p = vet;

    printf("endereço (inicial de vet) e endereço guardado em p: %p, %p\n\n\n", &vet, p);

    printf("os valores de vet são: ");

    for(int i = 0; i < 5 ; i ++){
        printf(" %d", *(p+i));
    }
    printf("\ne \n");
    for(int i = 0; i < 5 ; i ++){
        printf(" %d", p[i]);
    }
    printf("\n\n");
    for(int i = 0; i < 5 ; i ++){
        printf(" %d", vet[i]);
    }
    printf("\n\n");
    for(int i = 0; i < 5 ; i ++){
        printf(" %d", *(vet+i));
    }

    printf("\n\n");
    return 0 ;
}
