

#include "pauseMenu.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
	
	const int WINDOW_WIDTH = 540;
	const int WINDOW_HEIGHT = 480;

	// intialize window to render the menu
	struct Clunky_Window window;
	struct Clunky_Event event;
	clunky_init(&window, &event, WINDOW_WIDTH, WINDOW_HEIGHT);

	// run the pause menu
	int menuSelection = getPauseSelection(&window, &event);

	switch (menuSelection) {
		case 1:
			std::cout << "Main function: restart game\n";
			break;
		case 2:
			std::cout << "Main function: exit game\n";
			break;
		case 3:
			std::cout << "Main function: exit menu\n";
			break;
		default:
			std::cout << "Main function: SDL_QUIT\n";
			break;	
	} 

	return 0;
}
