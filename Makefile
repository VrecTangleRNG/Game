all:
	@gcc src/main.c src/player.c -o a.exe -I include -L lib -lraylib -lgdi32 -lwinmm

start:
	@./a.exe

clean:
	@rm -f a.exe