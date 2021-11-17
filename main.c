/* Henrique Prokopenko GRR20186712 */





#include "Boulder_dash.h"



t_state state;

int main(){
	
	state = MENU;
	
	for(;;){
		switch(state){
			case MENU: menu(); break;
	
			case PLAY: main_loop(); break;

			case WIN: win();break;

			case GAMEOVER: lose();break;

			case END: end(); return 0;

		}
	}
}
