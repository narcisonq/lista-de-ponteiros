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

    (*playlists)->id = (int*)realloc((*playlists)->id, ((*playlists)->qtd + 1) * sizeof(int));
    if ((*playlists)->id == NULL) {
        printf(stderr, "erro alocando memoria para id, compre mais RAM\n");
        
    }

    (*playlists)->qtd_mus = (int*)realloc((*playlists)->qtd_mus, ((*playlists)->qtd + 1) * sizeof(int));
    if ((*playlists)->qtd_mus == NULL) {
        printf(stderr, "Erro alocando memoria para qtd_mus\n");
        exit(EXIT_FAILURE);
    }

    (*playlists)->qtd_mus[(*playlists)->qtd] = 0;

    (*playlists)->id[(*playlists)->qtd] = id;

    (*playlists)->qtd++;

    *playlists = (playlist*)realloc(*playlists, (*playlists)->qtd * sizeof(playlist));
    if (*playlists == NULL) {
        printf(stderr, "erro criando mais uma playlist\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for nome_mus
    (*playlists)->nome_mus = (char***)realloc((*playlists)->nome_mus, (*playlists)->qtd * sizeof(char**));
    if ((*playlists)->nome_mus == NULL) {
        printf(stderr, "Erro alocando memoria para nome_mus\n");
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
                printf(stderr, "Erro alocando memoria para (mais uma) nome_mus[%d]\n", i);
                exit(EXIT_FAILURE);
            }

            playlists->nome_mus[i][playlists->qtd_mus[i] - 1] = (char*)malloc(strlen(nome) + 1); // malocando para o nome da musica
            if (playlists->nome_mus[i][playlists->qtd_mus[i] - 1] == NULL) {
                printf(stderr, "Erro alocando memoria para o nome_mus[%d][%d]\n", i, playlists->qtd_mus[i] - 1);
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
        if(id == playlists->id[i]){

            for(int j = 0 ; j < playlists->qtd_mus[i]; j++){
                if(strcmp(playlists->nome_mus[i][j], nome) == 0){
                    printf("tirando a música %s em questão da playlist %d", nome, id);
                    free(playlists->nome_mus[i][j]); // free maroto reio de guerra
                    // preenchendo aquele lugar com as musicas posteriores
                    for (int k = j; k < playlists->qtd_mus[i] - 1; k++) {
                        playlists->nome_mus[i][k] = playlists->nome_mus[i][k + 1];
                    }
                    playlists->qtd_mus[i]--;
                    break; 
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
        for (int j = 0; j < playlists->qtd_mus[i]; j++) {
            if (strcmp(nome, playlists->nome_mus[i][j]) == 0) {
                printf("Removendo a música %s de todas as playlists\n", nome);
                free(playlists->nome_mus[i][j]);

                // Shift songs after the deleted one
                for (int k = j; k < playlists->qtd_mus[i] - 1; k++) {
                    playlists->nome_mus[i][k] = playlists->nome_mus[i][k + 1];
                }

                // Update the number of songs in the current playlist
                playlists->qtd_mus[i]--;
            }
        }
    }
}

void PRINT_ONE(playlist* playlists, int id){

    for(int i = 0 ; i < playlists->qtd; i++){
        if(id == playlists->id[i]){
            printf("as musicas da playlist %d são: \n", playlists->id[i]);
            for(int j = 0; j < playlists->qtd_mus[i]; j++){
                printf("%s\n", playlists->nome_mus[i][j]);
            }


            
        }
        

        else{
            //printf("não achei essa playlist\n");
        }
    }
}


int main() {
