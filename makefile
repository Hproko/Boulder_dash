#Henrique Prokopenko      GRR20186712

CFLAGS = -Wall

LDLIBS =  $$(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 allegro_ttf-5 --libs --cflags)


objects = load_files.o Boulder_dash.o utils_boulderdash.o \
	  gameupdate.o game_init.o init_allegro.o main.o






all: game


game: $(objects)
	gcc $(objects) -o game $(LDLIBS)

main.o: main.c
	gcc -c main.c $(CFLAGS)
Boulder_dash.o: Boulder_dash.c Boulder_dash.h
	gcc -c Boulder_dash.c $(CFLAGS)

utils_boulderdash.o: utils_boulderdash.c utils_boulderdash.h
	gcc -c utils_boulderdash.c $(CFLAGS)

load_files.o: load_files.c load_files.h
	gcc -c load_files.c $(CFLAGS) 

gameupdate.o: gameupdate.c gameupdate.h
	gcc -c gameupdate.c $(CFLAGS)

game_init.o: game_init.c game_init.h
	gcc -c game_init.c $(CFLAGS)

init_allegro.o: init_allegro.c init_allegro.h
	gcc -c init_allegro.c $(CFLAGS)

clean: 
	-rm -f *~ *.o


purge: clean
	-rm -f game
