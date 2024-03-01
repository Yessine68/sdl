prog: main.o new_window.o function.o
	gcc main.o new_window.o function.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g

main.o: main.c
	gcc -c main.c -g

new_window.o: new_window.c
	gcc -c new_window.c -g

function.o: function.c
	gcc -c function.c -g
