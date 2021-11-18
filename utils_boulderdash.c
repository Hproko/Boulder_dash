/* Henrique Prokopenko GRR20186712*/


#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "load_files.h"
#include "entidades.h"
#include "utils_boulderdash.h"
#include "init_allegro.h"



//Mantem o teclado atualizado para desativar as teclas que foram pressionadas
void keyboard_update(ALLEGRO_EVENT* event, unsigned char *key){

	switch(event->type){
		case ALLEGRO_EVENT_TIMER:
			for(int i=0;i<ALLEGRO_KEY_MAX;i++)
				key[i] &= KEY_SEEN;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			key[event->keyboard.keycode] = KEY_SEEN | KEY_REALEASED;
			break;

		case ALLEGRO_EVENT_KEY_UP:
			key[event->keyboard.keycode] &= KEY_REALEASED;
			break;

	}

}



//Percorre a matriz e desenha de acordo com o conteudo de cada celula da matriz
void drawmap(int **matriz, struct sprites *spr, struct player* info, int diamondframe, int portalframe, int explosionframe, struct portal *coord){
	
	
	for(int i=0; i < 22; i++)
		for(int j=0;j < 40; j++){
			
			
			switch(matriz[i][j]){
				case METAL: 
					al_draw_bitmap(spr->metal, j*16, (i*16)+16, 0); break;

				case TERRA:
					al_draw_bitmap(spr->dirt, j*16, (i*16)+16, 0); break;

				case ROCK:
					al_draw_bitmap(spr->rock, j*16, (i*16)+16, 0); break;

				case VAZIO:
					if(coord->portal_open_frames)
						al_draw_bitmap(spr->light, j*16, (i*16)+16,0);
					else
						al_draw_bitmap(spr->vazio, j*16, (i*16)+16, 0); 
					break;

				case PLAYER:
					if(info->direcao == STOPPED) {
						al_draw_bitmap(spr->player_front[info->framefront], j*16, (i*16)+16, 0); break;	
					}

					if(info->direcao == RIGHT || info->direcao == UP){
						al_draw_bitmap(spr->player_right[info->frameright], j*16, (i*16)+16, 0); break;		
					}

					if(info->direcao == LEFT  || info->direcao == DOWN){
						al_draw_bitmap(spr->player_left[info->frameleft], j*16, (i*16)+16, 0); break;	
					}

				case PORTAL:
					al_draw_bitmap(spr->portal[portalframe], j*16, (i*16)+16, 0); break;
				
				case DIAMANTE:
					al_draw_bitmap(spr->diamond[diamondframe], j*16, (i*16)+16, 0); break;
				
				case BRICK:
					al_draw_bitmap(spr->brick, j*16, (i*16)+16, 0); break;
				
				case EXPLOSION:
					al_draw_bitmap(spr->explosion[explosionframe], j*16, (i*16)+16, 0); break;
			}
		}	
}



//Libera memoria das samples na estrutura de sons
void free_samples(struct sounds *sound){

	al_destroy_sample(sound->boulder);
	al_destroy_sample(sound->diamond_collect);
	al_destroy_sample(sound->earth_walk);
	al_destroy_sample(sound->empty_walk);
	al_destroy_sample(sound->diamond_fall);
	al_destroy_sample(sound->explosion);
	al_destroy_sample(sound->counting_points);
	al_destroy_sample(sound->portal_open);
	al_destroy_sample(sound->menu_music);

}


//Testa se o cheat code foi digitado corretamente
bool cheat_test(char *cheatcode){
	

	switch(strlen(cheatcode)){
		case 1: 
			if(cheatcode[0] != 'e')
				memset(cheatcode, 0, strlen(cheatcode));
			break;
		
		case 2:
			if(cheatcode[1] != 'x')
		       		memset(cheatcode, 0, strlen(cheatcode));

			break;
		case 3:
			if(cheatcode[2] != 'p'){
		       		memset(cheatcode, 0, strlen(cheatcode));
		       }
			break;
		case 4:
			if(cheatcode[3] != 'l'){
		       		memset(cheatcode, 0, strlen(cheatcode));
			
		       }
			break;
		case 5:
			if(cheatcode[4] != 'o'){
		       		memset(cheatcode, 0, strlen(cheatcode));
		
		       }
			break;

		case 6:
			if(cheatcode[5] != 'd'){
		       		memset(cheatcode, 0, strlen(cheatcode));
	
		       }
			break;

		case 7:
			if(cheatcode[6] != 'e'){
		       		memset(cheatcode, 0, strlen(cheatcode));
	
		       }
			break;
		
		default:
			return false;
	
	}
	if(! strcmp(cheatcode, "explode")){
		memset(cheatcode, 0, strlen(cheatcode));
		return true;
	}

	return false;
}





//Recebe teclas de abertura de menu e de cheat code
int get_keys(ALLEGRO_EVENT *event, char *cheatcode){

	if(event->keyboard.keycode == ALLEGRO_KEY_H || event->keyboard.keycode == ALLEGRO_KEY_F1)
		return 1;

	if(event->keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
		return 0;

	if(event->keyboard.keycode == ALLEGRO_KEY_R)
		return 2;

	if(event->keyboard.keycode == ALLEGRO_KEY_E){
		
		cheatcode[strlen(cheatcode)] = 'e';
		
		return 3;
	}

	if(event->keyboard.keycode == ALLEGRO_KEY_X){
		
		cheatcode[strlen(cheatcode)] = 'x';
		
		return 3;
	}

	if(event->keyboard.keycode == ALLEGRO_KEY_P){
		
		cheatcode[strlen(cheatcode)] = 'p';
		
		return 3;
	}

	if(event->keyboard.keycode == ALLEGRO_KEY_L){
		
		cheatcode[strlen(cheatcode)] = 'l';
	
		return 3;
	}

	if(event->keyboard.keycode == ALLEGRO_KEY_O){
		
		cheatcode[strlen(cheatcode)] = 'o';
		
		return 3;
	}

	if(event->keyboard.keycode == ALLEGRO_KEY_D){
		
		cheatcode[strlen(cheatcode)] = 'd';
	
		return 3;
	}

	return 3;
}




//desenha o hud a cada iteracao do loop principal
void imprime_hud(ALLEGRO_FONT* font, long score, int timer, int diamantes, struct sprites *spr, int diamond_frame){

	al_draw_bitmap(spr->diamond[diamond_frame], 50, 0, 0);

	al_draw_textf(font, al_map_rgb_f(0.5,1,1), 75, 0, 0, "%d", diamantes);

	al_draw_textf(font, al_map_rgb_f(1,1,1), 300, 0, 0, "%d", timer);

	al_draw_textf(font, al_map_rgb_f(1,1,1), 560, 0 , 0, "%06ld", score);

}




//Desenha resultado da partida com a pontuacao do jogador
void draw_game_result(ALLEGRO_FONT *font, long score, long record){

	al_draw_textf(font, al_map_rgb_f(1,1,1), BUFFER_W/2, BUFFER_H/2, ALLEGRO_ALIGN_CENTER, 
			"THANK  YOU  FOR  PLAYING!");

	al_draw_textf(font, al_map_rgb_f(1,1,1), 240, 70, 0, 
			"Record %ld", record);

	al_draw_textf(font, al_map_rgb_f(1,1,1), 200, 30, 0,
			"Your score %ld", score);

	if(score > record)
		al_draw_textf(font, al_map_rgb_f(1,1,1), 90, 110, 0, 
				"NEW  RECORD  CONGRATULATIONS!");

	al_draw_textf(font,al_map_rgb_f(1,1,1), 10, BUFFER_H/2 + 90, 0,
			"Press  y  to  play  again");

	al_draw_textf(font,al_map_rgb_f(1,1,1), 10, BUFFER_H/2 + 140, 0,
			"Press  n  to  quit");
}





//Desenha tela de ajuda
void imprime_instrucoes(ALLEGRO_FONT *font){

	al_draw_textf(font, al_map_rgb_f(1,1,1), 5, 20, 0, 
			" Use  as  setas  do  teclado  para  mover  o  personagem!");
	
	al_draw_textf(font, al_map_rgb_f(1,1,1), 5, 60, 0,
			" A  tecla  R  reinicia  o  jogo ");

	al_draw_textf(font, al_map_rgb_f(1,1,1), 5, 100, 0, 
			" Colete  os  diamantes  e  depois  va  ate  o  portal!");

	al_draw_textf(font, al_map_rgb_f(1,1,1), 5, 140, 0, 
			" Tome  cuidado  com  as  pedras  que  podem  rolar  e  cair");	

	al_draw_textf(font, al_map_rgb_f(1,1,1), 5, 200, 0,
			" Para  voltar  ao  jogo  pressione  BACKSPACE");

	al_draw_textf(font, al_map_rgb_f(1,1,1), 450, 340, 0, 
			"Henrique Prokopenko");
}





//Grava novo record no arquivo txt
void new_record(long score){

	FILE* arq;

	arq = fopen("resources/record.txt", "w");
	if(!arq){
		printf("Erro ao abrir record.txt\n");
		exit(1);
	}

	fprintf(arq, "%ld", score);

	fclose(arq);

}




//pinta a tela de preto e seta o buffer como alvo de desenho
void disp_pre_draw(ALLEGRO_BITMAP* buffer){

	al_set_target_bitmap(buffer);
	al_clear_to_color(al_map_rgb(0,0,0));

}



//volta o alvo para o display e desenha o buffer com tamanho proporcional ao display
void disp_post_draw(ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP* buffer){

	al_set_target_backbuffer(disp);
	al_draw_scaled_bitmap(buffer, 0, 0 ,640, 368, 0, 0, 960, 600, 0);	

}




//Desenha o menu
void draw_menu(ALLEGRO_FONT* font){

	al_draw_textf(font, al_map_rgb_f(1,1,1), BUFFER_W/2, BUFFER_H/2 + 100, ALLEGRO_ALIGN_CENTER,
			"Press any key");
}




//Libera espaco de memoria dos bitmaps
void free_bitmaps(struct sprites *spr){

	int i;
	al_destroy_bitmap(spr->sheet2);
	al_destroy_bitmap(spr->logo);
	al_destroy_bitmap(spr->sheet);
	al_destroy_bitmap(spr->brick);	
	al_destroy_bitmap(spr->dirt);	
	al_destroy_bitmap(spr->vazio);
	al_destroy_bitmap(spr->light);
	al_destroy_bitmap(spr->rock);
	al_destroy_bitmap(spr->metal);
	al_destroy_bitmap(spr->portal[0]);
	al_destroy_bitmap(spr->portal[1]);

	for(i=0;i<7;i++){
		al_destroy_bitmap(spr->player_front[i]);
		al_destroy_bitmap(spr->player_right[i]);
		al_destroy_bitmap(spr->player_left[i]);
	}

	for(i=0;i<8;i++)
		al_destroy_bitmap(spr->diamond[i]);

	for(i=0;i<4;i++)
		al_destroy_bitmap(spr->explosion[i]);

}



//Libera memoria matriz principal
void free_matriz(int **matriz){

	for(int i=0;i<22;i++)
		free(matriz[i]);
	free(matriz);
}
