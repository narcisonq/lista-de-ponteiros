#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int qtd;         // quantidade de playlists
    int* id;         // ids, que tem o tamanho da quantidade
    int* qtd_mus;    // quantidade de músicas em cada playlist
    char*** nome_mus; // ponteiro triplo para alocar primeiro a quantidade de playlists, depois cada música em determinada playlist
} playlist;

void CREATE(playlist** playlists) {
    int id;
    printf("digite o id da playlist: ");
    scanf("%d", &id);
    
    //realocando para mais uma id de playlist
    (*playlists)->id = (int*)realloc((*playlists)->id, ((*playlists)->qtd + 1) * sizeof(int));
    if ((*playlists)->id == NULL) {
        printf("erro alocando memoria para id, compre mais RAM\n");
        
    }
    
    //realocando para mais uma quantidade de músicas
    (*playlists)->qtd_mus = (int*)realloc((*playlists)->qtd_mus, ((*playlists)->qtd + 1) * sizeof(int));
    if ((*playlists)->qtd_mus == NULL) {
        printf("Erro alocando memoria para qtd_mus\n");
        exit(EXIT_FAILURE);
    }

    (*playlists)->qtd_mus[(*playlists)->qtd] = 0;

    (*playlists)->id[(*playlists)->qtd] = id;

    (*playlists)->qtd++;
    
    //malocando para mais uma playlist 
    // *playlists = (playlist*)realloc(*playlists, (*playlists)->qtd * sizeof(playlist));
    // if (*playlists == NULL) {
    //     printf("erro criando mais uma playlist\n");
    //     exit(EXIT_FAILURE);
    // }

    // malocando para os nomes das musicas
    (*playlists)->nome_mus = (char***)realloc((*playlists)->nome_mus, (*playlists)->qtd * sizeof(char**));
    if ((*playlists)->nome_mus == NULL) {
        printf("Erro alocando memoria para nome_mus\n");
        exit(EXIT_FAILURE);
    }

    // inicializando mais um vetor para os nomes de musicas
    (*playlists)->nome_mus[(*playlists)->qtd - 1] = NULL;
}


void ADD(playlist* playlists, char* nome) {
    //char nome[40];
    int id;

    playlists->qtd_mus = (int*)realloc(playlists->qtd_mus, (playlists->qtd + 1) * sizeof(int));

    printf("\nDigite o ID da playlist: ");
    scanf("%d", &id);

    for (int i = 0; i < playlists->qtd; i++) {
        if (playlists->id[i] == id) {
            playlists->qtd_mus[i]++;
            playlists->nome_mus[i] = (char**)realloc(playlists->nome_mus[i], playlists->qtd_mus[i] * sizeof(char*)); // realocando para mais uma musica
            if (playlists->nome_mus[i] == NULL) {
                printf("Erro alocando memoria para (mais uma) nome_mus[%d]\n", i);
                exit(EXIT_FAILURE);
            }

            playlists->nome_mus[i][playlists->qtd_mus[i] - 1] = (char*)malloc(strlen(nome) + 1); // malocando para o nome da musica
            if (playlists->nome_mus[i][playlists->qtd_mus[i] - 1] == NULL) {
                printf("Erro alocando memoria para o nome_mus[%d][%d]\n", i, playlists->qtd_mus[i] - 1);
                exit(EXIT_FAILURE);
            }

            strcpy(playlists->nome_mus[i][playlists->qtd_mus[i] - 1], nome);
            break;
        }
    }
}


void FIM(playlist* playlists) {
    for (int i = 0; i < playlists->qtd; i++) {
        for (int j = 0; j < playlists->qtd_mus[i]; j++) {
            free(playlists->nome_mus[i][j]);
        }
        free(playlists->nome_mus[i]);
    }
    free(playlists->nome_mus);
    free(playlists->qtd_mus);
    free(playlists->id);
    free(playlists);
}

void PRINT_ALL(playlist* playlists){
    for(int i = 0; i < playlists->qtd ; i++){
        printf("musicas da playlist_id %d: \n", playlists->id[i]);
            for (int j = 0; j < playlists->qtd_mus[i]; j++){
                printf("%s\n", playlists->nome_mus[i][j]);
            }
    }
}

void DEL(playlist* playlists, char* nome){
    int id;
    printf("diga o ID da playlist pra tirar a música\n");
    scanf("%d", &id);

    for(int i = 0 ; i < playlists->qtd; i++){
        int flag  =1;
        if(id == playlists->id[i]){

            for(int j = 0 ; j < playlists->qtd_mus[i] && flag != 0; j++){
                if(strcmp(playlists->nome_mus[i][j], nome) == 0){
                    printf("tirando a música %s em questão da playlist %d", nome, id);
                    free(playlists->nome_mus[i][j]); // free maroto reio de guerra
                    // preenchendo aquele lugar com as musicas posteriores
                    for (int k = j; k < playlists->qtd_mus[i] - 1; k++) {
                        playlists->nome_mus[i][k] = playlists->nome_mus[i][k + 1];
                    }
                    // atualizando o valor de musicas daquela playlist
                    playlists->qtd_mus[i]--;
                    flag = 0;
                    //break; 
                }

                else{
                    printf("não achei essa musica na playlist\n");
                }
            }
        }

        else{
            printf("não achei essa playlist\n");
        }
    }
}

void BAN(playlist* playlists, char* nome) {
    for (int i = 0; i < playlists->qtd; i++) {
        //int flag = 1;
        for (int j = 0; j < playlists->qtd_mus[i]; j++) {
            if (strcmp(nome, playlists->nome_mus[i][j]) == 0) {
                printf("Removendo a música %s da playlist %d\n", nome, playlists->id[i]);
                free(playlists->nome_mus[i][j]);

                // deslocando as musicas para preencher o vazio
                for (int k = j; k < playlists->qtd_mus[i] - 1; k++) {
                    playlists->nome_mus[i][k] = playlists->nome_mus[i][k + 1];
                }

                // atualizando o valor de musicas daquela playlist
                playlists->qtd_mus[i]--;
                //flag = 0;
            }
        }
    }
}

void PRINT_ONE(playlist* playlists, int id){
    int flag = 1;

    for(int i = 0 ; i < playlists->qtd && flag != 0; i++){
        if(id == playlists->id[i]){
            printf("as musicas da playlist %d são: \n", playlists->id[i]);
            for(int j = 0; j < playlists->qtd_mus[i]; j++){
                printf("%s\n", playlists->nome_mus[i][j]);
            }

            flag = 0;
            
        }
        

        else{
            printf("não achei essa playlist\n");
        }
    }
}


int main() {
    playlist* playlists;

    playlists = (playlist*)malloc(1 * sizeof(playlist)); // criando a primeira playlist

    playlists->qtd = 0;
    playlists->qtd_mus = NULL;
    playlists->nome_mus = NULL;

    int acao = -1;
    while(acao != 7){
        printf("\n\ndigite 1 para criar playlist\ndigite 2 para adicionar musica em determinada playlist\ndigite 3 para tirar musica de determinada playlist\ndigite 4 para tirar musica de todas as playlists\ndigite 5 pra printar tudo\ndigite 6 para printar uma\ndigite 7 pra sair: ");
        scanf("%d", &acao);
        
        if(acao == 1){
            CREATE(&playlists);
        }
        
        else if(acao == 2){
            char nome[30];
            printf("digite o nome da musica: ");
            scanf(" %s", nome);
            
            ADD(playlists, nome);        
        }      

        else if(acao == 3){
            char nome[30];
            printf("\ndigite o nome da musica para ser deletada: ");
            scanf("%s", nome);
            DEL(playlists, nome);

        }

        else if(acao == 4){
            char nome[30];
            printf("\ndigite o nome da musica para ser deletada de todas as playlists: ");
            scanf("%s", nome);
            BAN(playlists, nome);
        }

        else if(acao == 5){
            PRINT_ALL(playlists);
        }

        else if(acao == 6){
            int id;
            printf("\ndigite o id da playlist: ");
            scanf("%d", &id);
            PRINT_ONE(playlists, id);
        }

        else if(acao == 7){
            printf("\n\naté mais...\n\n");
            FIM(playlists);
        }
    }

    return 0;
   
}
