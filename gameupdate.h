/*Henrique Prokopenko GRR20186712 */







//Atualiza jogada do player
int player_update(int **matriz, unsigned char *key, struct player* info, long frame, struct FallingEntity *vet_pedras, int num_pedras, struct sounds *sound, struct FallingEntity* vet_dima, int num_diamantes);




//Atualiza frame do portal e tambem abre o portal caso o jogador tenha coletado 12 diamantes
int portalframe_update(long frame, struct player *info, int portalframe, int **matriz,  struct portal *coord_portal, struct sounds *sound);



//Atualiza frame dos diamantes
int diamondframe_update(int diamondframe, long frame);



//Atualiza frame de explosao 
int explosionframe_update(int explosionframe, long frame, int **matriz, struct player *info, struct FallingEntity *pedras);



//Explode os 8 blocos em volta do rockford
void kaboom(int **matriz, struct player *info, struct sounds *sound);



//Todas as pedras explodem (cheat)
void blow_all_rocks(int **matriz, struct FallingEntity *pedras, int num_pedras);



//Conta pontos bonus
int count_bonus_points(int *time, struct player *info);



//Atualiza o tempo de jogo restante
void time_update(int *time, long frame, int **matriz, struct player *info, struct sounds* sound);



//Percorre um vetor de struct pedras atualizando a posicao das pedras na matriz caso elas estejam caindo
void rocks_update(int **matriz, long frame, struct sounds *sound, struct FallingEntity *vet_pedras, int num_pedras, struct player *info, int explosion);



//Percorre um vetor de diamantes atualizando a posicao dos diamantes na matriz caso elas devam cair
void diamantes_update(int **matriz, long frame, struct sounds *sound, struct FallingEntity *vet_dima, int num_diamantes, struct player *info);




