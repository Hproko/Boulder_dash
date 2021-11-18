/* Henrique Prokopenko  GRR20186712 */




#define UP 1
#define LEFT 2
#define RIGHT 3 
#define DOWN 4
#define STOPPED 5


#define METAL 0 
#define ROCK 1 
#define TERRA 2
#define VAZIO 3 
#define PLAYER 4 
#define PORTAL 5
#define DIAMANTE 6 
#define BRICK 7 
#define EXPLOSION 8


//entrutura que guarda as informacoes do player
struct player{

	int i,j; 			//Posicao do player na matriz

	int diamantes;  		//Quantidade de diamantes coletados
	
	int framefront; 		//Indice do vetor de sprites de quando o personagem esta de frente
	
	int frameleft;
	
	int frameright;
	
	int direcao; 			//Direcao que o personagem esta andando

	int player_cooldown; 		// Stamina do personagem

	bool alive; 			// Flag de player que pode estar morto ou vivo

	long score; 			//Pontuacao

	bool win; 			//Flag se o player venceu
};





//Estrutura que pode guardar pedras ou diamantes (Usadas para entidades que caem) 
struct FallingEntity{ 

	int i,j; 			//Posicao da entidade na matriz
	
	bool falling; 			//Flag que diz se a entidade esta caindo ou nao

};





//Estrutura que guarda a posicao do portal, usada para abrir o portal quando o jogador coletar os diamantes
struct portal{
	
	int i, j; 			//Posicao na matriz
	
	int portal_open_frames; 	//Indice do vetor de sprites do portal
};

