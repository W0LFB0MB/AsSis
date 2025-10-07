AsSis: AsSis.c lib/display.c lib/colours.c lib/sequence.c lib/coupling.c
	clang -Wall -std=c11 -pedantic AsSis.c lib/display.c lib/colours.c lib/sequence.c lib/coupling.c -o AsSis ${sdl2-config --cflags --libs}  -lSDL2 -lm
clean:
	rm -f AsSis