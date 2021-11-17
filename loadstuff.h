/* Henrique Prokopenko GRR20186712 */



#define DIAMOND_FRAMES 8
#define ROCKFORD_FRONT_FRAMES 7
#define ROCKFORD_LEFT_FRAMES 7
#define ROCKFORD_RIGHT_FRAMES 7
#define EXPLOSION_FRAMES 5
#define PORTAL_FRAMES 2




//Definicao da estrutra de sprites que o programa usa 
struct sprites{
	
	ALLEGRO_BITMAP* sheet;

	ALLEGRO_BITMAP *sheet2;

	ALLEGRO_BITMAP* logo;	

	ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
	
	ALLEGRO_BITMAP* diamond[DIAMOND_FRAMES];
	
	ALLEGRO_BITMAP* player_front[ROCKFORD_FRONT_FRAMES];
	
	ALLEGRO_BITMAP* player_right[ROCKFORD_RIGHT_FRAMES];
	
	ALLEGRO_BITMAP* player_left[ROCKFORD_LEFT_FRAMES];

	ALLEGRO_BITMAP* portal[PORTAL_FRAMES];

	ALLEGRO_BITMAP* brick;

	ALLEGRO_BITMAP* dirt;

	ALLEGRO_BITMAP* vazio;

	ALLEGRO_BITMAP* light;

	ALLEGRO_BITMAP* rock;

	ALLEGRO_BITMAP* metal;

};



//Definicao da estrutura de sons 
struct sounds{
	
	ALLEGRO_SAMPLE *diamond_collect;
	
	ALLEGRO_SAMPLE *boulder;

	ALLEGRO_SAMPLE *diamond_fall;

	ALLEGRO_SAMPLE *explosion;

	ALLEGRO_SAMPLE *menu_music;

	ALLEGRO_SAMPLE *portal_open;

	ALLEGRO_SAMPLE *counting_points;
	
	ALLEGRO_SAMPLE *earth_walk;

	ALLEGRO_SAMPLE *empty_walk;
};


//Funcao para teste de inicializacao
void must_init(bool test, const char *description);


//Inicializa e carrega os audios na estrutura de som
void sound_init(struct sounds *sound);


//ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h);


//Inicia estrutura de sprites
void sprites_init(struct sprites *sprites);


//Carrega maior pontuacao de todos os tempos
long carrega_record();




