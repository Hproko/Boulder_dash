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
#include "Boulder_dash.h"

#define MAXTIME 153


//Faz a contagem de bonus points
int count_bonus_points(int *time, struct player *info){

	if(*time == 0)
		return 1;
	
	*time -= 1;
	info->score++;
	
	return 0;
}




//Testa se a posicao na matriz esta vazia
int isVazio(int **matriz, int i, int j){

	if(matriz[i][j] == VAZIO)
		return 1;

	return 0;
}





//Se o cheat for ativado todas as pedras explodem
void blow_all_rocks(int **matriz, struct FallingEntity *pedras, int num_pedras){

	for(int i=0;i<num_pedras;i++){
		matriz[pedras[i].i][pedras[i].j] = EXPLOSION;
	}

}




//depois de explodidas todas as pedras se tornam VAZIO
void all_rocks_go_empty(int **matriz, struct FallingEntity *pedras, int num_pedras){
	
	for(int i=0; i < num_pedras; i++){
		
		matriz[pedras[i].i][pedras[i].j] = VAZIO;
		
		pedras[i].i = 0;
		pedras[i].j = 0;
		
		matriz[pedras[i].i][pedras[i].j] = METAL;
	}
}





//Atualizacao da posicao das pedras a cada frame
void rocks_update(int **matriz, long frame, struct sounds *sound, struct FallingEntity *vet_pedras, int num_pedras, struct player *info, int explosion){

	

	
	if(info->alive == false)
		return;



	//Quando todas as pedras explodirem elas devem se tornar VAZIO
	if(explosion == 4 && matriz[vet_pedras[0].i][vet_pedras[0].j] == EXPLOSION){
		all_rocks_go_empty(matriz, vet_pedras, num_pedras);
		return;
	}



	//se as pedras se tornarem VAZIO ou frame nao for multiplo de dez retorna
	if(frame % 10 != 0 || matriz[vet_pedras[0].i][vet_pedras[0].j] == VAZIO)
		return;

	
	
	
	
	//Testa todo o vetor de pedras
	for(int i=0;i<num_pedras;i++){
		


		//Testa se a pedra cai em cima do jogador
		if(matriz[vet_pedras[i].i+1][vet_pedras[i].j] == PLAYER && vet_pedras[i].falling){
				kaboom(matriz, info, sound);
				return;
		}





		//Se embaixo da pedra esta vazio a pedra cai
		if(isVazio(matriz, vet_pedras[i].i+1, vet_pedras[i].j)){

			matriz[vet_pedras[i].i+1][vet_pedras[i].j] = ROCK;
			matriz[vet_pedras[i].i][vet_pedras[i].j] = VAZIO;
			
			vet_pedras[i].i++;
			vet_pedras[i].falling = 1;
			
			continue;
		}



	
		//Testando qual entidade tem embaixo da pedra, se houver diamante, pedra ou tijolo testa se tem espaco para cair
		if(matriz[vet_pedras[i].i+1][vet_pedras[i].j] == DIAMANTE || matriz[vet_pedras[i].i+1][vet_pedras[i].j] == ROCK || matriz[vet_pedras[i].i+1][vet_pedras[i].j] == BRICK ){


			
			//se tiver espaco para a direita pedra cai pra direita
			if(isVazio(matriz, vet_pedras[i].i+1, vet_pedras[i].j+1) && isVazio(matriz, vet_pedras[i].i, vet_pedras[i].j+1)){

				matriz[vet_pedras[i].i+1][vet_pedras[i].j+1] = ROCK;
				matriz[vet_pedras[i].i][vet_pedras[i].j] = VAZIO; 
				
				vet_pedras[i].i++;
				vet_pedras[i].j++;
				
				vet_pedras[i].falling = 1;
				
				continue;
			}
				
	

			//Testa se a pedra escorregou para a direita e caiu sobre o jogador
			if(matriz[vet_pedras[i].i+1][vet_pedras[i].j+1] == PLAYER && vet_pedras[i].falling && isVazio(matriz, vet_pedras[i].i, vet_pedras[i].j+1)){
				
				kaboom(matriz, info, sound);
				
				return;
			}




			//se tives espaco para esquerda pedra cai pra esquerda
			if(isVazio(matriz, vet_pedras[i].i+1, vet_pedras[i].j-1) && isVazio(matriz, vet_pedras[i].i, vet_pedras[i].j-1)){

				matriz[vet_pedras[i].i+1][vet_pedras[i].j-1] = ROCK;
				matriz[vet_pedras[i].i][vet_pedras[i].j] = VAZIO;
				
				vet_pedras[i].i++;
				vet_pedras[i].j--;
				
				vet_pedras[i].falling = 1;
				
				continue;
			}
			


			//Testa se a pedra escorregou para a esquerda e caiu sobre a cabeca do jogador
			if(matriz[vet_pedras[i].i+1][vet_pedras[i].j-1] == PLAYER && vet_pedras[i].falling && isVazio(matriz,vet_pedras[i].i, vet_pedras[i].j-1)){
				kaboom(matriz,info, sound);
				return;
			}
		
		
		}


		if(vet_pedras[i].falling){//Se a funcao chegar ate aqui significa que a pedra esta caindo, entao toca som de pedra caindo
			
			al_play_sample(sound->boulder, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			vet_pedras[i].falling = 0;
		}
	
	}
}








void diamantes_update(int **matriz, long frame, struct sounds* sound, struct FallingEntity* vet_dima, int num_diamantes, struct player *info){
	
	
	
	if(frame % 10 != 0 || info->alive == false)
		return;






	//Testa todo o vetor de diamantes  
	for(int i=0;i<num_diamantes;i++){

		
		
		//Testando se o diamante caiu sobre o personagem
		if(matriz[vet_dima[i].i+1][vet_dima[i].j] == PLAYER && vet_dima[i].falling){
				
			kaboom(matriz, info, sound);
				
			return;
		}





		//Se embaixo do diamantes esta vazio
		if(isVazio(matriz, vet_dima[i].i+1, vet_dima[i].j)){

			matriz[vet_dima[i].i+1][vet_dima[i].j] = DIAMANTE;
			matriz[vet_dima[i].i][vet_dima[i].j] = VAZIO;
			
			vet_dima[i].i++;
			
			vet_dima[i].falling = 1;
			
			continue;
		}



		//Testa se diamante deve cair para esquerda ou para a direita
		if(matriz[vet_dima[i].i+1][vet_dima[i].j] == DIAMANTE || matriz[vet_dima[i].i+1][vet_dima[i].j] == ROCK || matriz[vet_dima[i].i+1][vet_dima[i].j] == BRICK ){

			
			
			//se tiver espaco para a direita diamante cai pra direita
			if(isVazio(matriz, vet_dima[i].i+1, vet_dima[i].j+1) && isVazio(matriz, vet_dima[i].i, vet_dima[i].j+1)){

				matriz[vet_dima[i].i+1][vet_dima[i].j+1] = DIAMANTE;
				matriz[vet_dima[i].i][vet_dima[i].j] = VAZIO; 
				
				vet_dima[i].i++;
				vet_dima[i].j++;
				
				vet_dima[i].falling = 1;
				
				continue;
			}




			//Testa se o diamante rolou para a direita e caiu sobre o player
			if(matriz[vet_dima[i].i+1][vet_dima[i].j+1] == PLAYER && vet_dima[i].falling && isVazio(matriz, vet_dima[i].i, vet_dima[i].j+1)){
				
				kaboom(matriz, info, sound);
				
				return;
			}




			//se tives espaco para esquerda diamante cai pra esquerda
			if(isVazio(matriz, vet_dima[i].i+1, vet_dima[i].j-1) && isVazio(matriz, vet_dima[i].i, vet_dima[i].j-1)){

				matriz[vet_dima[i].i+1][vet_dima[i].j-1] = DIAMANTE;
				matriz[vet_dima[i].i][vet_dima[i].j] = VAZIO;
				
				vet_dima[i].i++;
				vet_dima[i].j--;
				
				vet_dima[i].falling = 1;
				
				continue;
			}
			
			
			
			//Testando se o diamante rolou para a esquerda e caiu sobre o personagem
			if(matriz[vet_dima[i].i+1][vet_dima[i].j-1] == PLAYER && vet_dima[i].falling && isVazio(matriz, vet_dima[i].i, vet_dima[i].j-1)){
				
				kaboom(matriz,info,sound);
				
				return;
			}
		}



		if(vet_dima[i].falling){//Se a funcao chegou aqui o diamante bateu no chao entao toca som de diamante caindo
			
			al_play_sample(sound->diamond_fall, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			vet_dima[i].falling = 0;
		}
		
	}

	return;

}




//funcao que testa se o bloco eh destrutivel
int eh_destrutivel(int **matriz, int i, int j){
	
	if(matriz[i][j] != METAL && matriz[i][j] != PORTAL){
		return 1;
	}

	return 0;

}





//Funcao que explode o player e ao redor
void kaboom(int **matriz, struct player *info, struct sounds* sound){
	
	al_play_sample(sound->explosion, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	if(eh_destrutivel(matriz, info->i, info->j))
		matriz[info->i][info->j] = EXPLOSION;


	if(eh_destrutivel(matriz, info->i-1, info->j))
		matriz[info->i-1][info->j] = EXPLOSION;


	if(eh_destrutivel(matriz, info->i-1, info->j+1))
		matriz[info->i-1][info->j+1] = EXPLOSION;


	if(eh_destrutivel(matriz, info->i, info->j+1))
		matriz[info->i][info->j+1] = EXPLOSION;


	if(eh_destrutivel(matriz, info->i+1, info->j+1))
		matriz[info->i+1][info->j+1] = EXPLOSION;


	if(eh_destrutivel(matriz, info->i+1, info->j))
		matriz[info->i+1][info->j] = EXPLOSION;


	if(eh_destrutivel(matriz, info->i+1, info->j-1))
		matriz[info->i+1][info->j-1] = EXPLOSION;


	if(eh_destrutivel(matriz, info->i, info->j-1))
		matriz[info->i][info->j-1] = EXPLOSION;


	if(eh_destrutivel(matriz, info->i-1, info->j-1))
		matriz[info->i-1][info->j-1] = EXPLOSION;
	
}







//Funcao que atualiza o frame do portal
int portalframe_update(long frame, struct player *info, int portalframe, int **matriz, struct portal *coord_portal, struct sounds *sound){
	

	if(frame % 15 != 0)
		return portalframe;



	//Apos 3 segundos o portal se transforma no player para iniciar o jogo
	if(frame == 180)
		matriz[info->i][info->j] = PLAYER;


	//atualiza o frame do portal aberto
	if(coord_portal->portal_open_frames > 0){
		
		coord_portal->portal_open_frames++;
		
		if(coord_portal->portal_open_frames == 2)
			
			coord_portal->portal_open_frames = 0;
	}


	//Quando o player pega 12 diamantes o portal se abre 
	if(info->diamantes == 12 && matriz[coord_portal->i][coord_portal->j] != PORTAL){
		
		matriz[coord_portal->i][coord_portal->j] = PORTAL;
		
		
		al_play_sample(sound->portal_open, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		
		
		coord_portal->portal_open_frames++;
	}



	//Atualiza o frame do portal antes do jogo iniciar durante 3 segundos
	if(frame < 180 || info->diamantes >= 12){
		
		portalframe++;
	
		if(portalframe == 2)
			
			portalframe = 0;
	}

	return portalframe;

}





//Atualiza tile do diamante a cada cinco frames
int diamondframe_update(int diamondframe, long frame){

	if(frame % 5 == 0){
		diamondframe++;
	}

	if(diamondframe == 8)
		diamondframe = 0;

	return diamondframe;

}




//Atualiza o tempo e caso o player tenha vencido, para de atualizar
void time_update(int *time, long frame, int **matriz, struct player *info, struct sounds* sound){
	
	if(info->win)
		return;

	if(*time > 0)
		
		*time = MAXTIME - (frame/60);
	
	else
		
		kaboom(matriz, info, sound);
	
}







//Funcao que atualiza frame da explosao
int explosionframe_update(int explosionframe, long frame, int **matriz, struct player *info, struct FallingEntity *pedras){
	

	//Quando terminar a explosao do player que morreu, acaba o programa e seta player como morto
	if(explosionframe == 5  && matriz[info->i][info->j] == EXPLOSION){
		
		info->alive = 0;
		
		return explosionframe - 1;
	}



	//Quando cheat e ativado entao nao e necessario setar player como morto
	if(explosionframe == 5)
		return explosionframe - 1;



	//Atualiza qual tile deve mostrar na explosao
	if(frame % 5 == 0 && matriz[info->i][info->j] == EXPLOSION){
		
		explosionframe++;		
		
		return explosionframe;
	}



	//Atualizacao de frame de explosao quando o cheat e ativado
	if(matriz[pedras[0].i][pedras[0].j] == EXPLOSION && frame % 5 == 0 )
		explosionframe++;


	return explosionframe;

}







//Faz todas as jogadas e mudancas do jogo envolvendo o player
int player_update(int **matriz, unsigned char *key, struct player* info, long frame, struct FallingEntity *vet_pedras, int num_pedras, struct sounds* sound, struct FallingEntity* vet_dima, int num_diamantes){




	int i = info->i;
	int j = info->j;



	info->direcao = STOPPED;
	

	if(info->alive == false)
		return 0;

	//Atualizacao da tile do rockford de frente
	if(frame % 7 == 0)
		info->framefront++;
	
	if(info->framefront == 7)
		info->framefront = 0;



	//Atualizacao da tile do rockford de lado
	if(frame % 3 == 0){
		
		info->frameleft++;
		info->frameright++;
	

		if(info->frameleft == 7 || info->frameright == 7){
			info->frameleft = 0;
			info->frameright = 0;

		}
	}




	//Jogador fica bloqueado durante 3 segundos ou quando ja venceu a partida
	if(frame < 180 || info->win)
		return 0;





	//Computa a jogada
	if(key[ALLEGRO_KEY_UP]){
		i--;
		info->direcao = UP;
	}else

		if(key[ALLEGRO_KEY_DOWN]){
			i++;
			info->direcao = DOWN;
		}else

			if(key[ALLEGRO_KEY_LEFT]){
				j--;
				info->direcao = LEFT;
			}else

				if(key[ALLEGRO_KEY_RIGHT]){
					j++;
					info->direcao = RIGHT;
				}

	



	//Cooldown de cinco frames para segurar velocidade do personagem
	if(info->player_cooldown < 5){
		
		info->player_cooldown++;
		
		return 0;
	}
	
	info->player_cooldown = 0;




	//nao deixa personagem se mover na direcao caso seja borda ou tijolo
	if(matriz[i][j] == METAL || matriz[i][j] == BRICK)
		return 0;





	//Jogador vence a partida
	if(matriz[i][j] == PORTAL && info->diamantes >= 12){
		
		matriz[info->i][info->j] = VAZIO;
		
		matriz[i][j] = PLAYER;
				
		info->win = true;
		
		al_play_sample(sound->counting_points, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		
		return 1;
	}


	//Personagem coleta diamante
	if(matriz[i][j] == DIAMANTE){

		//Encontra no vetor de diamantes o diamante correto e retira ele da matriz e do vetor
		for(int k=0;k<num_diamantes;k++){
			
			if(vet_dima[k].i == i && vet_dima[k].j == j){
				
				vet_dima[k].i = 0;
				vet_dima[k].j = 0;
				
				break;
			}
		}



		if(info->diamantes >= 12)
		       
			info->score += 15;
		
		else
			
			info->score += 10;


		info->diamantes++;
		
		matriz[i][j] = PLAYER;
		matriz[info->i][info->j] = VAZIO;
		
		info->i = i;
		info->j = j;
		
		al_play_sample(sound->diamond_collect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		
		return 0;
	}




	//Empurra pedra pra direita se houver espaco
	if(matriz[i][j] == ROCK && info->direcao == RIGHT){
		
		
		//Testa se ao lado da pedra esta vazio para ser empurrada
		if(isVazio(matriz, i, j+1)){
			
			//Encontra a pedra que corresponde no vetor de pedras e muda sua posicao 
			for(int k=0; k<num_pedras;k++){
				
				if(vet_pedras[k].i == i && vet_pedras[k].j == j){
					
					vet_pedras[k].j++;		
					
					break;
				}
			}


			matriz[i][j+1] = ROCK;
			matriz[i][j] = PLAYER;
			matriz[i][j-1] = VAZIO;
			
			info->i = i;
			info->j = j;	
			
			return 0;
		}

	}



	//Empurra pedra pra esquerda se houver espaco
	if(matriz[i][j] == ROCK && info->direcao == LEFT){
		
		
		if(isVazio(matriz, i, j-1)){

			for(int k = 0; k < num_pedras; k++){
				
				
				if(vet_pedras[k].i == i && vet_pedras[k].j == j){
					vet_pedras[k].j--;
					break;
				}

			}

			matriz[i][j-1] = ROCK;
			matriz[i][j] = PLAYER;
			matriz[i][j+1] = VAZIO;
			
			info->i = i;
			info->j = j;
			
			return 0;
		}
	}






	//movimenta personagem
	if(matriz[i][j] == VAZIO){
		
		matriz[info->i][info->j] = VAZIO;
		matriz[i][j] = PLAYER;
		
		info->i = i;
		info->j= j;
		
		al_play_sample(sound->empty_walk, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		
		return 0;
		
	}





	if(matriz[i][j] == TERRA){
		
		matriz[info->i][info->j] = VAZIO;
		matriz[i][j] = PLAYER;
		
		info->i = i;
		info->j= j;
		
		al_play_sample(sound->earth_walk, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}

	return 0;

}

