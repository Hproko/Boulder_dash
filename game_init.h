/* Henrique Prokopenko GRR20186712 */




//Aloca memoria pra matriz
int ** cria_matriz();



//Calcula tamanho dos vetores de pedra e diamante
void tam_vetores(int* pedras, int* diamantes, int** matriz);


//Aloca memoria para vetor de diamantes ou pedras
struct FallingEntity* cria_vetor(int tam_vetor);


//Inicia estrutura player
void init_player_info(struct player* info);


//Inicia variaveis dos vetores de diamantes e pedras
void inicia_vetores(struct FallingEntity* vet_pedras, struct FallingEntity* vet_diamantes, int** matriz, struct player* info, struct portal* portal);


//Carrega mapa do arquivo txt na matriz
void inicia_mapa(int **matriz);
