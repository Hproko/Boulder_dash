/* Henrique Prokopenko GRR20186712*/






#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "loadstuff.h"
#include "entidades.h"
#include "utils_boulderdash.h"
#include "gameupdate.h"
#include "game_init.h"


#define ALT 22
#define LARG 40





//Aloca memoria para matriz
int ** cria_matriz(){
	
	
	int **matriz;

	
	matriz = malloc(ALT * sizeof(int*));
	if(!matriz){
		printf("Erro ao alocar matriz\n");
		exit(1);
	}



	for(int i = 0;i < ALT;i++){
		
		matriz[i] = malloc(LARG * sizeof(int));
		
		if(!matriz[i]){
			
			printf("Erro ao alocar matriz\n");
			
			exit(1);
		}
	}

	return matriz;
}






//Calcula o tamanho dos vetores que serao alocados para diamantes e pedras
void tam_vetores(int* pedras, int *diamantes, int **matriz){

	for(int i=1;i<ALT;i++)
		for(int j=1;j<40-1;j++){

			if(matriz[i][j] == DIAMANTE){
				*diamantes+=1;
				continue;
			}

			if(matriz[i][j] == ROCK){
				*pedras+=1;
				continue;
			}
			
		}
	
}





//Aloca vetor de pedra ou diamantes
struct FallingEntity* cria_vetor(int tam_vetor){
	
	struct FallingEntity* vet;

	vet = malloc(tam_vetor * sizeof(struct FallingEntity));

	if(!vet){
		printf("Falha ao alocar memoria para vetor\n");
		exit(-1);
	}

	return vet;
}











//Inicia variaveis dos vetores de pedra, diamantes e da estrutura portal
void inicia_vetores(struct FallingEntity* vet_pedras, struct FallingEntity* vet_diamantes, int** matriz, struct player* info, struct portal* portal){
	
	int i_p = 0, i_d = 0;

	for(int i=1;i<ALT-1;i++)
		for(int j=1;j<LARG-1;j++){
			
			switch(matriz[i][j]){
				
				case ROCK:
					vet_pedras[i_p].i = i;
					vet_pedras[i_p].j = j;
					vet_pedras[i_p].falling = 0;
					i_p++;
					break;
				
				case DIAMANTE:
					vet_diamantes[i_d].i = i;
			       		vet_diamantes[i_d].j = j;
				 	vet_diamantes[i_d].falling = 0;
					i_d++;	
					break;
			
				case PORTAL:
					info->i = i;
					info->j = j;
					break;
				case METAL:
					portal->i = i;
					portal->j = j;
					portal->portal_open_frames = 0;
					break;
			}
		}
}







//Inicia estrutura player
void init_player_info(struct player* info){
	
	info->direcao = STOPPED;
	info->player_cooldown = 0;
	info->framefront = 0;
	info->frameleft = 0;
	info->frameright = 0;
	info->diamantes = 0;
	info->score = 0;
	info->alive = 1;
	info->win = false;

}




//Carrega mapa do arquivo txt na matriz
void inicia_mapa(int** matriz){
	
	int i, j;
	
	FILE* arq;

	arq = fopen("resources/map.txt", "r");
	if(!arq){
		printf("Erro ao abrir o arquivo de mapa\n");
		exit(1);
	}

	for(i=0; i < ALT; i++)
		for(j=0; j < LARG; j++){
			fscanf(arq, "%d", &matriz[i][j]);
		}
			
		
	

	fclose(arq);

		
}
