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



struct player{

	int i,j;

	int diamantes;
	
	int framefront;
	
	int frameleft;
	
	int frameright;
	
	int direcao;

	int player_cooldown;

	int alive;

	long score;

	bool win;
};



struct FallingEntity{

	int i,j;
	
	int falling;

};




struct portal{
	int i, j;
	int portal_open_frames;
};

