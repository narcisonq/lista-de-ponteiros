#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char raca[50];
    int idade;
    float salario;
    char CPF[12];
} Pessoa;

typedef struct {
    char nome[50];
    int codigo; //código único que identifica cada cidade
    Pessoa* cidadaos;
    int capacidade;
} Cidade;

Cidade* NovaCidade(Cidade* censo, int* tam){
    
    char nome[50];
    int codigo;
    printf("\ndigite o nome da cidade: ");
    scanf("%s", nome);
    printf("digite o codigo da cidade: ");
    scanf("%d", &codigo);

    censo = realloc(censo, (*tam + 1) * sizeof(Cidade));

    strcpy(censo[*tam].nome, nome);
    censo[*tam].codigo = codigo;
    censo[*tam].cidadaos = NULL; // inicializando o vetor dinamico de cidadãos
    censo[*tam].capacidade = 0; // inicializando a variável que conta a população

    (*tam)++; // aumentando a variável do numero de cidades

    return censo;
}


void InserirOuAtualizar(Cidade* censo, int tam){
    int idade;
    float salario;
    char nome[50];
    char raca[50];
    char cpf[12];
    printf("\ndigite as informações da pessoa (idade, salario, nome, raca, cpf): ");
    scanf("%d %f", &idade, &salario);
    scanf("%s %s %s", nome, raca, cpf);

    int codigo;
    printf("\ndigite o codigo da cidade que essa pessoa reside: ");
    scanf("%d", codigo);

    int flag = 0;
    for(int i = 0; i < tam; i++){
        if(codigo == censo[i].codigo){
            for(int j = 0; j < censo[i].capacidade && flag != 1; j++){
                if(strcmp(cpf, censo[i].cidadaos[j].CPF) == 0){
                    printf("essa pessoa já foi cadastrada, então atualizamos os dados dela");

                    /*atribuindo as informações da nova pessoa*/

                    strcpy(censo[i].cidadaos[j].nome, nome);
                    strcpy(censo[i].cidadaos[j].raca, raca);
                    censo[i].cidadaos[j].idade = idade;
                    censo[i].cidadaos[j].salario = salario;
                    strcpy(censo[i].cidadaos[j].CPF, cpf);
                    flag = 1; //atualizou os dados, sai do loop
                    
                }

            }

            if(flag == 0){ 
                    //não achou no banco de dados, cria a pessoa do 0
                    printf("essa pessoa está sendo cadastrada no banco de dados");
                    censo[i].cidadaos = realloc(censo[i].cidadaos, (censo[i].capacidade + 1) * sizeof(Pessoa)); //realloc para caber mais 1

                    // atribuindo os valores
                    strcpy(censo[i].cidadaos[censo[i].capacidade].nome, nome);
                    strcpy(censo[i].cidadaos[censo[i].capacidade].raca, raca);
                    censo[i].cidadaos[censo[i].capacidade].idade = idade;
                    censo[i].cidadaos[censo[i].capacidade].salario = salario;
                    strcpy(censo[i].cidadaos[censo[i].capacidade].CPF, cpf);

                    censo[i].capacidade++;  // aumentando a população
                }
            }
        }
    }



void Remover(Cidade* censo, int tam){
    int codigo;
    char CPF[12];

    printf("\ndigite o codigo da cidade que a pessoa que vc quer eliminar mora: ");
    scanf("%d", &codigo);
    printf("\ndigite o cpf que será cancelado: ");
    scanf("%s", CPF);

    int flag = 0;

    for(int i = 0; i < tam ; i++){
        for(int j = 0 ; j < censo[i].capacidade && flag != 1; j++){
            if(strcmp(CPF, censo[i].cidadaos[j].CPF) == 0 ){
                printf("\na pessoa %s será eliminada...\n", censo[i].cidadaos[j].nome);
                free(censo[i].cidadaos[j].nome);
                free(censo[i].cidadaos[j].CPF);
                free(censo[i].cidadaos[j].raca);

                //tapando o buraco deixado pela pessoa no banco de dados
                for (int k = j; k < censo[i].capacidade - 1; k++) {
                    censo[i].cidadaos[k] = censo[i].cidadaos[k + 1];
                }

                censo[i].capacidade--;
                flag = 1;
            }

            else{
                printf("\nnão achei essa pessoa");
            }
        }
    }
}

void Procura(Cidade* censo, int tam){
    int codigo;
    char CPF[12];

    printf("\ndigite o codigo da cidade que a pessoa que vc quer achar mora: ");
    scanf("%d", &codigo);
    printf("\ndigite o cpf do procurado: ");
    scanf("%s", CPF);

    int flag = 0;

    for(int i = 0; i < tam ; i++){
        for(int j = 0 ; j < censo[i].capacidade && flag != 1; j++){
            if(strcmp(CPF, censo[i].cidadaos[j].CPF) == 0 ){

                printf("a pessoa se chama: %s\n é da etnia %s\ntem %d anos\nganha %.2f de salário\n", censo[i].cidadaos[j].nome,
                censo[i].cidadaos[j].raca, 
                censo[i].cidadaos[j].idade, 
                censo[i].cidadaos[j].salario);
                
                flag = 1;
            }

        }
    }

     if (flag == 0) {
        printf("\nNão achei essa pessoa nessa cidade.\n");
    }
}

void ViewTable(Cidade* censo, int tam){

    for(int i = 0; i < tam ; i++){
        printf("pessoas da cidade %s de codigo %d\n", censo[i].nome, censo[i].codigo);

        for(int j = 0 ; j < censo[i].capacidade ; j++){

                printf("a pessoa se chama: %s\n é da etnia %s\ntem %d anos\nganha %.2f de salário\n", censo[i].cidadaos[j].nome,
                censo[i].cidadaos[j].raca, 
                censo[i].cidadaos[j].idade, 
                censo[i].cidadaos[j].salario);
                
                
            }

    }
}


void Desaloca(Cidade* censo, int tam){
    printf("eliminando todos os dados, até mais...\n\n");
    for(int i = 0; i < tam ; i++){
        for(int j = 0 ; j < censo[i].capacidade; j++){      
            //eliminando os vetores de cada cidadão da cidade      
            free(censo[i].cidadaos[j].nome);
            free(censo[i].cidadaos[j].CPF);
            free(censo[i].cidadaos[j].raca);           
        }

        free(censo[i].cidadaos); //eliminando o vetor do cidadão
        
        censo[i].cidadaos = NULL; //eliminando a cidade

    }
}

int main(){

    int acao = 0;

    int tam = 0;

    Cidade* censo = NULL;

    while(acao != 6){
        printf("digite 1 para botar uma nova cidade no mapa\ndigite 2 para inserir as informações de alguém\ndigite 3 para remover alguém\n4 para procurar alguém\n5 para ver todo mundo cadastrado\n6 para sair: ");
        scanf("%d", &acao);

        switch (acao) {
            case 1:
                censo = NovaCidade(censo, &tam);
                break;
            case 2:
                InserirOuAtualizar(censo, tam);
                break;
            case 3:
                Remover(censo, tam);
                break;
            case 4:
                Procura(censo, tam);
                break;
            case 5:
                ViewTable(censo, tam);
                break;
            case 6:
                Desaloca(censo, tam);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
