/* Henrique Prokopenko GRR20186712*/


#define KEY_SEEN 1
#define KEY_REALEASED 2


//Reseta o teclado para manter atualizado
void keyboard_update(ALLEGRO_EVENT* event, unsigned char* key);


//Percorre a matriz desenhando cada tipo de entidade
void drawmap(int **matriz, struct sprites *spr, struct player *info, int diamondframe, int portalframe, int explosionframe, struct portal *coord);


//Libera memoria dos audios
void free_samples(struct sounds* sound);


//seta o alvo de desenho pro buffer e pinta de preto
void disp_pre_draw(ALLEGRO_BITMAP* buffer);


//seta o display como alvo e desenha o buffer no display
void disp_post_draw(ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *buffer);


//Desenha tela de resultado do jogo com a pontuacao
void draw_game_result(ALLEGRO_FONT *font, long score, long record);


//Desenha o menu de entrada
void draw_menu(ALLEGRO_FONT *font);


//Registra o novo record 
void new_record(long score);


//Desenha tela de instrucoes do jogo h ou F1
void imprime_instrucoes(ALLEGRO_FONT *font);


//Desenha o hud atualizado
void imprime_hud(ALLEGRO_FONT *font, long score, int timer, int diamantes);


//Le teclas pressionadas e devolve: 0 tela do jogo, 1 tela de ajuda e 2 cheat ativado
int get_keys(ALLEGRO_EVENT* event, char *cheatcode);


//Libera memoria dos bitmaps
void free_bitmaps(struct sprites *spr);


//Testa se o jogador digitou o cheat code corretamente
bool cheat_test(char *cheatcode);


//Libera memoria da matriz de inteiros
void free_matriz(int **matriz);
