/* Henrique Prokopenko GRR20186712*/


#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include "loadstuff.h"
#include "entidades.h"
#include "utils_boulderdash.h"
#include "gameupdate.h"
#include "game_init.h"
#include "init_allegro.h"
#include "Boulder_dash.h"

#define FPS 60 


ALLEGRO_BITMAP* buffer;
ALLEGRO_DISPLAY* disp;

struct sounds sound;
struct sprites sprites;
struct player info;

t_state state;

void menu(){
	
	//inicia allegro e o teclado
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");



	//inicia addon de audio
	inicia_audio();
	


	//Inicia display e buffer
	disp = NULL;
	buffer = NULL;
	inicia_display(&disp, &buffer);
	


	//Carrega samples na estrutura de sons
	sound_init(&sound);
	ALLEGRO_SAMPLE_ID menu_sound;
	al_play_sample(sound.menu_music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &menu_sound );



	//inicia addon de ttf e carrega fonte
	must_init(al_init_font_addon(), "font addon");
	must_init(al_init_ttf_addon(),"ttf addon");
	ALLEGRO_FONT* font = al_load_ttf_font("resources/menu.ttf", 20, ALLEGRO_TTF_NO_KERNING);



	//inicia addon de imagem e carrega sprites na estrutura de imagens
	must_init(al_init_image_addon(), "image addon");
	sprites_init(&sprites);



	ALLEGRO_EVENT event;



	//inicia event queue
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");	
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));




	while(state == MENU){
	
		//Desenha o menu de inicio do jogo
		disp_pre_draw(buffer);
		draw_menu(font);
		disp_post_draw(disp, buffer);
		al_draw_bitmap(sprites.logo, 180, 100 , 0);

		al_flip_display();	
		
		al_wait_for_event(queue, &event);
		
		switch(event.type){
			
			case ALLEGRO_EVENT_KEY_DOWN:	
				state = PLAY;
				break;
		
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				state = END;
				break;	
		}

	}

	al_stop_sample(&menu_sound);
	al_destroy_font(font);
	al_destroy_event_queue(queue);
	

	
}


void main_loop(){
		


	//Carrega fonte padrao do allegro
	ALLEGRO_FONT* font = al_load_ttf_font("resources/classic.ttf", 16, ALLEGRO_TTF_NO_KERNING );
	must_init(font, "font");



	//inicia timer do frame
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	must_init(timer, "timer");



	//inicia event queue
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");
	

	//Registro dos evento na queue
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));




	//alocacao de memoria da matriz de inteiros
	int  **matrizprincipal = cria_matriz();
	


	//inicializa estrutura player
	init_player_info(&info);



	//carrega o map.txt na matriz
	inicia_mapa(matrizprincipal);



	// declara variaveis de pedras e diamantes e calcula o tamanho do vetor de pedras e diamantes
	int num_diamantes = 0, num_pedras = 0;
	tam_vetores(&num_pedras, &num_diamantes, matrizprincipal);




	//apontadores para vetor de diamantes e vetor de pedras
	struct FallingEntity* vet_diamantes = cria_vetor(num_diamantes);
	struct FallingEntity* vet_pedras = cria_vetor(num_pedras);





	//guarda coordenada do portal para abri lo quando o player pegar 12 diamantes
	struct portal coord_portal;
	



	//inicializa vetores e estrutura de portal
	inicia_vetores(vet_pedras, vet_diamantes, matrizprincipal, &info, &coord_portal);




	//variaveis que controlam os frames/tiles que sera exibidas na tela
	int diamondframe = 0;
	int portalframes = 0;
	int explosionframes = 0;
	



	//contador de frames;
	long frames = 0;
	



	//zera vetor que guarda quais teclas foram pressionadas
	unsigned char key[ALLEGRO_KEY_MAX];	
	memset(key, 0, sizeof(key));





	//help page = 0 imprime o mapa do jogo | help page = 1 imprime a tela de ajuda
	int help_page = 0;
	


	//buffer que guardo o cheat code
	char cheatcode[7+1] = "\0";




	//tempo restante da partida
	int time = 1;




	bool done = false;
	bool redraw = true;

	ALLEGRO_EVENT event;
	al_start_timer(timer);

	while(1){

		al_wait_for_event(queue, &event);

		switch(event.type){

			case ALLEGRO_EVENT_TIMER:
				//GAME LOGIC

				if(! help_page && ! done){
				
				
					//Atualizacao do jogo
 
					rocks_update(matrizprincipal, frames, &sound, vet_pedras, num_pedras, &info, explosionframes);
					
					if(player_update(matrizprincipal, key, &info, frames, vet_pedras, num_pedras, &sound, vet_diamantes, num_diamantes))
						state = WIN;
					
					diamantes_update(matrizprincipal, frames, &sound, vet_diamantes, num_diamantes, &info);                     
				
					portalframes = portalframe_update(frames, &info, portalframes, matrizprincipal, &coord_portal, &sound);
						
					diamondframe = diamondframe_update(diamondframe, frames);
				
					explosionframes = explosionframe_update(explosionframes, frames, matrizprincipal, &info, vet_pedras);


					time_update(&time, frames, matrizprincipal, &info, &sound);

					//player morreu
					if(!info.alive){
						state = GAMEOVER;
						done = true;
					

					}


					//player venceu
					if(state == WIN){
						if(count_bonus_points(&time, &info))
							done = true;
					}	

						
					frames++;
				
				}
				

				if(key[ALLEGRO_KEY_ESCAPE]){
					state = END;	
					done = true;
				}

				
				redraw = true;
				break;
			
				
			case ALLEGRO_EVENT_KEY_CHAR:
				

				switch(get_keys(&event, cheatcode)){
					case 0: help_page = 0;break;
					case 1: help_page = 1;break;
					case 2: done = true;
					     	state = GAMEOVER;
						break;
				}

				//testa se o cheat foi ativado
				if(cheat_test(cheatcode)){
					
					blow_all_rocks(matrizprincipal, vet_pedras, num_pedras);
					
					al_play_sample(sound.explosion, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					
					explosionframes = -1;
				}

				break;

				

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				state = END;
				done = true;
				break;
		}

		if(done)
			break;

		keyboard_update(&event, key);

		if(redraw && al_is_event_queue_empty(queue)){


			//Desenha tela do jogo
			if(!help_page){
				
				disp_pre_draw(buffer);
				
				drawmap(matrizprincipal, &sprites, &info, diamondframe, portalframes, explosionframes, &coord_portal);
				
				imprime_hud(font, info.score, time, info.diamantes, &sprites, diamondframe);
			
				disp_post_draw(disp, buffer);
			
			}

			//Desenha tela de ajuda
			else{

				disp_pre_draw(buffer);
				
				imprime_instrucoes(font);
				
				disp_post_draw(disp, buffer);
			
			}
			
			al_flip_display();

			redraw = false;
		}


	}
	
	free_matriz(matrizprincipal);
	free(vet_diamantes);
	free(vet_pedras);
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

}






void win(){
	

	//Teclado do allegro
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, ALLEGRO_KEY_MAX);


	//Carrega o record do arquivo txt 
	long record = carrega_record();


	//registra novo recorde caso o record tenha sido quebrado
	if(info.score > record)
		new_record(info.score);


	//Carrega fonte
	ALLEGRO_FONT* font;
	font = al_load_ttf_font("resources/classic.ttf", 30, ALLEGRO_TTF_NO_KERNING);
	must_init(font, "font win");



	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue win");



	ALLEGRO_EVENT event;
	
	al_register_event_source(queue, al_get_display_event_source(disp));

	al_register_event_source(queue, al_get_keyboard_event_source());

	
	
	while(state == WIN){
		

		//Desenha tela de resultado do jogo
		disp_pre_draw(buffer);
		draw_game_result(font, info.score, record);
		disp_post_draw(disp, buffer);
		al_flip_display();
				
		al_wait_for_event(queue, &event);


		switch(event.type){
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				state = END;
		 		break;	 

			default:
				if(key[ALLEGRO_KEY_Y]){
					state = PLAY;
					break;
				}
				if(key[ALLEGRO_KEY_N]){
					state = END;
					break;
				}
				if(key[ALLEGRO_KEY_ESCAPE]){
					state = END;
					break;
				}

				break;
		}

	
		keyboard_update(&event, key);	
	}

	al_destroy_font(font);
	al_destroy_event_queue(queue);
}




//Se o jogador morreu, loop principal reinicia
void lose(){
	//sleep(0.7);
	state = PLAY;
}



//Fim do jogo
void end(){	
	free_samples(&sound);
	free_bitmaps(&sprites);
	al_destroy_display(disp);
	al_destroy_bitmap(buffer);
}
