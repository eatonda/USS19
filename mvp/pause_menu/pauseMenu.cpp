

#include "../menu_functions/menu.hpp"
#include <stdio.h>
#include <string>

// gets the user selection from the pause menu
// - if the SDL_QUIT is encountered, -1 is returned
// - if the user selects restart game, 1 is returned
// - if the user selects exit game, 2 is returned
// - if the user simply exits the menu, 3 is returned
int getPauseSelection(struct Clunky_Window* window, struct Clunky_Event* event) {

	// Constants for the menu
	const int NUM_OF_SPRITE_COLS = 2;
	const int BUTTON_WIDTH = 165;
	const int BUTTON_HEIGHT = 160;
	const int NUM_BUTTONS = 4;
	const std::string title = "GAME PAUSED";


	std::string menuDescriptions[NUM_BUTTONS] = {"user manual", "restart game",
		"exit game", "exit menu"};
	int menuValues[] = {0, 1, 2, 3};
	// holds the value navigated to
	int navigation = -1;

	// gets x coordinate that centers button
	int x = getMiddle(BUTTON_WIDTH, window->width);

	int xCoordinates[NUM_BUTTONS] = {x, x, x, x};	

	// button height offset from other buttons in menu relative to window
	// height
	int yOffset = window->height * 0.15;

	// first button height 
	int y = window->height * 0.35;

	// set y coordinates for each of the buttons
	int yCoordinates[NUM_BUTTONS];
	for (int i = 0; i < NUM_BUTTONS; i++) {
		yCoordinates[i] = y;
		y += yOffset;
	}

	struct Clunky_Texture pause_menu_texture;
	clunky_load_texture(toC_String("./clunky_assets/pauseMenuButtons.bmp"),
		&pause_menu_texture, window);	

	// stores sprite image of pause menu buttons
	struct Clunky_Sprite pmb;
	clunky_init_sprite(NUM_BUTTONS, NUM_OF_SPRITE_COLS, &pause_menu_texture,
		&pmb);

	// store menu as an array of Clunky_Button
	struct Clunky_Event_Element_Container* pause_menu =
		buttonSetup(NUM_BUTTONS, menuDescriptions, &pmb, xCoordinates,
		yCoordinates);

	// get Clunky_Text instance for pauseMenu title
	struct Clunky_Text* pauseMenuTitle = clunky_get_text(x, 
		window->height * 0.15, window->width * 0.50, window->height * 0.10,
		1.0, window);
	// add text to clunky_text
	clunky_add_text(pauseMenuTitle, toC_String(title));


	// initialize a menu object for the pause menu`	
	Menu* pMenu = new Menu(window, pause_menu, NUM_BUTTONS, menuValues, 
		menuDescriptions, pauseMenuTitle);

	// flag maintained to see if SDL_QUIT is encountered (in which case
	// a -1 is stored in the flag
	int menuFlag;

	// flag indicating that the pause menu should be continued to be
	// rendered
	int menuCont = 1;
	// holds the value that this function will return indicating the 
	// cause of the exit from the pause menu
	// -1 for SDL QUIT
	// 1 for restart game
	// 2 for exit game
	// 3 for exit menu
	int returnVal = -1;

	while (menuCont) {
		menuFlag = pMenu->run(event, &navigation); 
		if (menuFlag > 0) {
			switch(navigation) {
				// user manual selected
				case 0: 
					std::cout << "Pause Menu: User Manual\n";
					// ** once game manual is finalized there should be
					// functionality to go to the game manual and return to
					// the pause menu **
					break;
				// restart game selected
				case 1:
					std::cout << "Pause Menu: Restart Game\n";
					returnVal = 1;
					menuCont = 0;
					break;
				// exit game selected
				case 2:
					std::cout << "Pause Menu: Exit Game\n";
					returnVal = 2;
					menuCont = 0;
					break;
				// exit menu selected
				case 3:
					std::cout << "Pause Menu: Exit Menu\n";
					returnVal = 3;
					menuCont = 0;
					break;
				default:
					break;
			}
		}

		else {
			std::cout << "Pause Menu: SDL_QUIT encountered\n";
			menuCont = 0;
		}
	}

	SDL_QUIT;
	// free menu memory
	free(pMenu);

	return returnVal;   
}
