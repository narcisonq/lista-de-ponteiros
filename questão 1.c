#include <stdio.h>
#include <stdlib.h>

int main(){
    char c = 'a';
    char* pc = &c;

    printf("o endereço de ''c'' em hex: %p\no valor guardado em c é: %c\n\n", pc, c);

    printf("O valor que pc armazena e o valor guardado no endereço apontado por ele é: %p e ''%c''\n\n", pc, *pc);

    printf("o endereço de pc é: %p\n\n", &pc);

    printf("O endereço do valor guardado no endereço apontado por pc: %p \ne o valor guardado no endereço de pc: %p\n\n\n", &*pc, *&pc);

    /*eles são iguais por o *pc é a desreferencia do ponteiro pc, assim a gente vê para o q ele de fato ta apontando
    o &pc nos dá o endereço da variável pc
    pc -> c (apontando literalmente kkkk)
    &*pc -> &c
    &*pc = o endereço da variável q pc está apontando
    
    
    no caso do *&pc temos algo mais ou menos assim
    
    &pc = endereço q o valor de pc está guardado
    *&pc = o valor apontado pelo endereco de pc = c

    pois pois &pc obtém o endereço de pc e * obtém o valor armazenado nesse endereço, que é c

    isso é uma capoeira mental
    */
    return 0;
}
