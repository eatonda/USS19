

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


    /* CREATE HELP MENU */
	const int HELP_MENU_NUM_OF_BUTTONS = 3;
    std::string helpTitle = "USER MANUAL";
    
    // Note main menu must be capitalized to MAIN MENU for menu function to recognize it properly
    std::string helpMenuDescriptions [HELP_MENU_NUM_OF_BUTTONS] = {"MAIN MENU", "PREVIOUS", "NEXT"};
    
    struct Clunky_Texture help_menu_texture;
    clunky_load_texture(toC_String("./clunky_assets/pauseUserManualButtons.bmp"), &help_menu_texture, window);  // Initialize texture for board menu
    
    struct Clunky_Sprite hmb;   //stores sprite image of help menu buttons
    clunky_init_sprite(HELP_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &help_menu_texture, &hmb); // Initialize sprite
    
    // Buttons for pages should be at the bottom of the screen in a single row
    int xOffset = window->width * 0.25;
    x = window->width * 0.20;
    for (int i = 0; i < HELP_MENU_NUM_OF_BUTTONS; i++){
        xCoordinates[i] = x;
        x+= xOffset;
        yCoordinates[i] = window->height * 0.95;
    }
   
	// store buttons as an array of Clunky_Button 
    struct Clunky_Event_Element_Container* help_menu = buttonSetup(HELP_MENU_NUM_OF_BUTTONS, helpMenuDescriptions, &hmb, xCoordinates, yCoordinates);    
    struct Clunky_Text* helpMenuTitle = clunky_get_text(window->width * 0.4, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for help menu title
    
    clunky_add_text(helpMenuTitle, toC_String(helpTitle));   // Add text to clunky_text
    
//    struct Clunky_Text* content = (struct Clunky_Text*)malloc(sizeof(struct Clunky_Text*) * 8);
   std::string words[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
    
    std::string path = "./menu_functions/menu_assets/user_manual.txt";
    std::vector<char*> manualStrings;
    //printf("|||||||||\n");
    fileToStrings(path, manualStrings);    //Get cstring version of text file
   // printf("|||||||||\n");
    
    // Trace statement
    for(int i = 0; i < manualStrings.size(); i ++){
        printf("GGP() %s\n", manualStrings[i]);
    }

 
    struct Clunky_Text* help_content[manualStrings.size()];
    int lineOffset = window->height * 0.05;
    int lineY = window->height * 0.3;
    int linesPerPage = 10;   //To show multipage functionality
    int count = 0;
    for(int i = 0; i < manualStrings.size(); i++) {
        if (count >= linesPerPage) {
            count = 0;  //Reset count
            lineY = window->height * 0.3;   //Reset y
        }
        count++;
        printf(">>%d, %d\n", i, manualStrings.size());  // Trace statement
        help_content[i] = clunky_get_text(window->width * 0.05, lineY, window->width * 0.9, window->height * 0.10, 1.0, window);
        //printf("===\n");
        //clunky_add_text(content[i], toC_String(words[i]));
        clunky_add_text(help_content[i], manualStrings[i]);
        //printf("++++\n");
        lineY+= lineOffset;
    }
    
    Menu* helpMenu = new Menu(window, help_menu, HELP_MENU_NUM_OF_BUTTONS, helpMenuDescriptions, helpMenuTitle, help_content, 6, linesPerPage);	



	while (menuCont) {
		menuFlag = pMenu->run(event, &navigation); 
		if (menuFlag > 0) {
			switch(navigation) {
				// user manual selected
				case 0: 
					std::cout << "Pause Menu: User Manual\n";
					if (helpMenu->runPage(event) == -1) {
						menuCont = 0;
					}				
	
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

	// free menu memory
	free(pMenu);

	return returnVal;   
}
