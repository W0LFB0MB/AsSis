AsSis: AsSis.c lib/display.c
	clang -Wall -std=c11 -pedantic AsSis.c lib/display.c -o AsSis ${sdl2-config --cflags --libs}  -lSDL2 -lm
clean:
	rm -f AsSis