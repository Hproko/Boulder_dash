/* Henrique Prokopenko GRR20186712 */




#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "load_files.h"




//Funcao que testa se a inicializacao dos arquivos deu certo
void must_init(bool test, const char *description){
	
	if(test) return;

	printf("Nao foi possivel iniciar %s\n", description);
	exit(1);

}




//Corta tile do spritesheet
ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h){

	ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, w, h);
	must_init(sprite, "sprite grab");
	return sprite;

}




//Carrega sprites na estrutura de sprites
void sprites_init(struct sprites *sprites){
	
	sprites->sheet = al_load_bitmap("resources/bdsprites.png");
	must_init(sprites->sheet, "spritesheet");

	sprites->logo = al_load_bitmap("resources/BD-logo.png");
	must_init(sprites->logo, "logo");

	sprites->sheet2 = al_load_bitmap("resources/lightfull.png");

	sprites->player_front[0] = sprite_grab(sprites->sheet, 0, 0, 16, 16);
	sprites->player_front[1] = sprite_grab(sprites->sheet, 16, 0, 16, 16);
	sprites->player_front[2] = sprite_grab(sprites->sheet, 32, 0, 16, 16);
	sprites->player_front[3] = sprite_grab(sprites->sheet, 48, 0, 16, 16);
	sprites->player_front[4] = sprite_grab(sprites->sheet, 64, 0, 16, 16);
	sprites->player_front[5] = sprite_grab(sprites->sheet, 80, 0, 16, 16);
	sprites->player_front[6] = sprite_grab(sprites->sheet, 96, 0, 16, 16);
	
	sprites->player_left[0] = sprite_grab(sprites->sheet, 0, 16, 16, 16);
	sprites->player_left[1] = sprite_grab(sprites->sheet, 16, 16, 16, 16);
	sprites->player_left[2] = sprite_grab(sprites->sheet, 32, 16, 16, 16);
	sprites->player_left[3] = sprite_grab(sprites->sheet, 48, 16, 16, 16);
	sprites->player_left[4] = sprite_grab(sprites->sheet, 64, 16, 16, 16);
	sprites->player_left[5] = sprite_grab(sprites->sheet, 80, 16, 16, 16);
	sprites->player_left[6] = sprite_grab(sprites->sheet, 96, 16, 16, 16);

	sprites->player_right[0] = sprite_grab(sprites->sheet, 0, 32, 16, 16);
	sprites->player_right[1] = sprite_grab(sprites->sheet, 16, 32, 16, 16);
	sprites->player_right[2] = sprite_grab(sprites->sheet, 32, 32, 16, 16);
	sprites->player_right[3] = sprite_grab(sprites->sheet, 48, 32, 16, 16);
	sprites->player_right[4] = sprite_grab(sprites->sheet, 64, 32, 16, 16);
	sprites->player_right[5] = sprite_grab(sprites->sheet, 80, 32, 16, 16);
	sprites->player_right[6] = sprite_grab(sprites->sheet, 96, 32, 16, 16);

	sprites->rock = sprite_grab(sprites->sheet, 80, 48, 16, 16);

	sprites->brick = sprite_grab(sprites->sheet, 32, 48, 16, 16);

	sprites->metal = sprite_grab(sprites->sheet, 0, 48, 16, 16);

	sprites->dirt = sprite_grab(sprites->sheet, 64, 48, 16, 16);

	sprites->explosion[0] = sprite_grab(sprites->sheet, 128, 112, 16, 16);
	sprites->explosion[1] = sprite_grab(sprites->sheet, 128, 96, 16, 16);
	sprites->explosion[2] = sprite_grab(sprites->sheet, 128, 80, 16, 16);
	sprites->explosion[3] = sprite_grab(sprites->sheet, 128, 64, 16, 16);

	sprites->vazio = sprite_grab(sprites->sheet, 96, 48, 16, 16);

	sprites->light = sprite_grab(sprites->sheet2, 140, 0, 16, 16);

	sprites->explosion[4] = sprites->vazio;

	sprites->diamond[0] = sprite_grab(sprites->sheet, 0, 64, 16, 16);
	sprites->diamond[1] = sprite_grab(sprites->sheet, 0, 80, 16, 16);
	sprites->diamond[2] = sprite_grab(sprites->sheet, 0, 96, 16, 16);
	sprites->diamond[3] = sprite_grab(sprites->sheet, 0, 112, 16, 16);
	sprites->diamond[4] = sprite_grab(sprites->sheet, 16, 64, 16, 16);
	sprites->diamond[5] = sprite_grab(sprites->sheet, 16, 80, 16, 16);
	sprites->diamond[6] = sprite_grab(sprites->sheet, 16, 96, 16 ,16);
	sprites->diamond[7] = sprite_grab(sprites->sheet, 16, 112, 16, 16);		
	
	sprites->portal[0] = sprite_grab(sprites->sheet, 0, 48, 16, 16);
	sprites->portal[1] = sprite_grab(sprites->sheet, 16, 48, 16, 16);
}



//Carrega as samples na estrutura de sons
void sound_init(struct sounds* sound){
	
	sound->boulder = al_load_sample("resources/Sounds/boulder.ogg");
	must_init(sound->boulder, "boulder sound");

	sound->diamond_collect = al_load_sample("resources/Sounds/collect_diamond.ogg");
	must_init(sound->diamond_collect, "diamond collect sound");

	sound->diamond_fall = al_load_sample("resources/Sounds/diamondfall.ogg");
	must_init(sound->diamond_fall, "diamond fall sound");

	sound->explosion = al_load_sample("resources/Sounds/explosion.ogg");
	must_init(sound->explosion, "explosion sound");

	sound->counting_points = al_load_sample("resources/Sounds/Bonuspoints.ogg");
	must_init(sound->counting_points, "counting points sound");

	sound->menu_music = al_load_sample("resources/Sounds/menumusic.opus");
	must_init(sound->menu_music, "menu music");

	sound->portal_open = al_load_sample("resources/Sounds/portal.ogg");
	must_init(sound->portal_open, "portal open sound");

	sound->earth_walk = al_load_sample("resources/Sounds/walk_earth.ogg");
	must_init(sound->earth_walk, "earth walk");

	sound->empty_walk = al_load_sample("resources/Sounds/walk_empty.ogg");
	must_init(sound->empty_walk, "empty walk");
}


//Carrega pontuacao maxima obtida no jogo
long carrega_record(){
	
	long record;	
	FILE *arq;

	arq = fopen("resources/record.txt", "r");

	if(!arq){
		printf("Erro ao abrir record.txt\n");
		exit(1);
	}

	fscanf(arq, "%ld", &record);

	fclose(arq);

	return record;

}


