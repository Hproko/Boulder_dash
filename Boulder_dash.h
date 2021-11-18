/* Henrique Prokopenko     GRR20186712 */



//definicao do tipo estado para 
typedef enum { MENU, PLAY, WIN, GAMEOVER, END} t_state;


//Mostra resultado da partida 
void win();


//Menu de entrada
void menu();


//Encerra o jogo
void end();


//player perdeu a partida
void lose();


//loop principal do jogo
void main_loop();
