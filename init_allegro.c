/* Henrique Prokopenko GRR20186712*/


#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "init_allegro.h"
#include "load_files.h"



//Inicia display e buffer do allegro
void inicia_display(ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **buffer){

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	*display = al_create_display(DISPLAY_W, DISPLAY_H);
	must_init(display, "display");

	*buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
	must_init(buffer, "bitmap buffer");
	
}



//Inicia audio de addons do allegro
void inicia_audio(){
	
	must_init(al_install_audio(),"audio");
	
	must_init(al_init_acodec_addon(), "audio codecs");
	
	must_init(al_reserve_samples(16), "reserve samples");
}

