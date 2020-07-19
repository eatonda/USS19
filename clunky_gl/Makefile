CC=g++
exe=GC


board:
	$(CC) -lSDL2 clunkyCore.c clunkyAdvancedCollisions.c clunkyEventElements.c clunkyHash.c board_ex.cpp -o board_ex -w

menu:
	$(CC) -lSDL2 clunkyCore.c clunkyAdvancedCollisions.c clunkyEventElements.c clunkyHash.c menu_ex.cpp -o menu_ex -w

$(exe):
	$(CC) -lSDL2 clunkyCore.c grannyCrumpet.c clunkyAdvEvents.c clunkyHash.c clunkyAdvancedCollisions.c -o $(exe)
