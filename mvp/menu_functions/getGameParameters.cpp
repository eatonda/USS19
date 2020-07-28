/*  getGameParameters
 Description: Runs menus required to initialize game parameters in main via reference
 Parameters: struct Clunky_Window* window,  struct Clunky_Event* event, struct Clunky_Window* window, int* dimensions, int* numOfShips, int* colorTheme
 Returns: Updates all parameters except window via reference based on user selection
 
 Preconditions: No parameter can be NULL and the window parameter must be properly intitiated
 */

#include "getGameParameters.hpp"

int getGameParameters(struct Clunky_Window* window,  struct Clunky_Event* event, int* dimensions, int* numOfShips, int* colorTheme) {

/* Constants for all menu buttons */
const int NUM_OF_SPRITE_COLS = 2;
const int BUTTON_WIDTH = 165;
const int BUTTON_HEIGHT = 160;
    
/* Constants for MAIN MENU */
const int MAIN_MENU_NUM_OF_BUTTONS = 4;

/* Constants for COLOR MENU */
const int COLOR_MENU_NUM_OF_BUTTONS = 3;
    
/* Constants for SHIP MENU */
const int SHIP_MENU_NUM_OF_BUTTONS = 4;
    
/* Constants for Board MENU */
const int BOARD_MENU_NUM_OF_BUTTONS = 4;
    
/* Constant for menus array */
const int NUM_OF_MENUS = 4;
   
    std::string title;  // String used to initialize each menu clunky_text object
    
    
                            /* CREATE MAIN MENU */

    // Options for main menu
    title = "MAIN MENU";
    
    
    std::string mainMenuDescriptions [MAIN_MENU_NUM_OF_BUTTONS] = {"start", "leaderboard", "user manual", "quit"};
    
    int MAIN_MENU_VALUES[MAIN_MENU_NUM_OF_BUTTONS] = {0, 1, 2, 3};     // Navigates Main menu
    int navigation; // Holds value for navigation sake

    int x = getMiddle(BUTTON_WIDTH, window->width);  // Get x coordinate that centers the button
    
    int xCoordinates [MAIN_MENU_NUM_OF_BUTTONS] = {x,x,x,x};
    
    int yOffset = window->height * 0.15;    // button height offset from other buttons in main menu, relative to window height
    
    int y = window->height * 0.35;        //Starting button height, relative positioning
    
    int yCoordinates [MAIN_MENU_NUM_OF_BUTTONS];   // Stores y coordinates for buttons of the main menu
    for (int i = 0; i < MAIN_MENU_NUM_OF_BUTTONS; i++){
        yCoordinates[i] = y;
        y+= yOffset;
    }

    struct Clunky_Texture main_menu_texture;
    clunky_load_texture(toC_String("/menu_functions/mainMenuButtons.bmp"), &main_menu_texture, window);  // Initialize texture for main menu
    
    struct Clunky_Sprite mmb;   //stores sprite image of main menu buttons
    clunky_init_sprite(MAIN_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &main_menu_texture, &mmb); // Initialize sprite

    struct Clunky_Event_Element_Container* main_menu = buttonSetup(MAIN_MENU_NUM_OF_BUTTONS, mainMenuDescriptions, &mmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
    
    
    struct Clunky_Text* mainMenuTitle = clunky_get_text(x, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for mainMenu title
    
    clunky_add_text(mainMenuTitle, toC_String(title));   // Add text to clunky_text
    
    
    /* Initialize a Menu object for the mainMenu*/
    Menu* mainMenu =  new Menu(window, main_menu, MAIN_MENU_NUM_OF_BUTTONS, MAIN_MENU_VALUES, mainMenuDescriptions, mainMenuTitle);
    
    
    
                        /* CREATE COLOR MENU */
    // For simplicity all menus will have the same y and x coordinates but they can be customized
    
    title = "COLOR THEME";
    
    // Note back must be capitalized to BACK for menu function to recognize it properly
    std::string colorMenuDescriptions [COLOR_MENU_NUM_OF_BUTTONS] = {"0", "1", "BACK"};
    int COLOR_MENU_VALUES [COLOR_MENU_NUM_OF_BUTTONS] = {0, 1};     // Values for color are either 0 for light and 1 for dark
    

    struct Clunky_Texture color_menu_texture;
    clunky_load_texture(toC_String("/menu_functions/colorMenuButtons.bmp"), &color_menu_texture, window);  // Initialize texture for color menu
    
    
    struct Clunky_Sprite cmb;   //stores sprite image of color menu buttons
    clunky_init_sprite(COLOR_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &color_menu_texture, &cmb); // Initialize sprite

    struct Clunky_Event_Element_Container* color_menu = buttonSetup(COLOR_MENU_NUM_OF_BUTTONS, colorMenuDescriptions, &cmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
    
    struct Clunky_Text* colorMenuTitle = clunky_get_text(x, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for colorMenu title
    
    clunky_add_text(colorMenuTitle, toC_String(title));   // Add text to clunky_text
    
    /* Initialize a Menu object for the colorMenu*/
    Menu* colorMenu =  new Menu(window, color_menu, COLOR_MENU_NUM_OF_BUTTONS, COLOR_MENU_VALUES, colorMenuDescriptions, colorMenuTitle);
    
    
    
                        /* CREATE SHIP MENU */
    // For simplicity all menus will have the same y and x coordinates but they can be customized
    
    title = "NUMBER OF SHIPS";
    
    // Note back must be capitalized to BACK for menu function to recognize it properly
    std::string shipMenuDescriptions [SHIP_MENU_NUM_OF_BUTTONS] = {"5", "7", "10", "BACK"};
    int SHIP_MENU_VALUES [SHIP_MENU_NUM_OF_BUTTONS] = {5, 7, 10};     // Values for numOfShips
    
    struct Clunky_Texture ship_menu_texture;
    clunky_load_texture(toC_String("/menu_functions/shipMenuButtons.bmp"), &ship_menu_texture, window);  // Initialize texture for ship menu
    
    
    struct Clunky_Sprite smb;   //stores sprite image of ship menu buttons
    clunky_init_sprite(SHIP_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &ship_menu_texture, &smb); // Initialize sprite

    struct Clunky_Event_Element_Container* ship_menu = buttonSetup(SHIP_MENU_NUM_OF_BUTTONS, shipMenuDescriptions, &smb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
    
    struct Clunky_Text* shipMenuTitle = clunky_get_text(x, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for shipMenu title
    
    clunky_add_text(shipMenuTitle, toC_String(title));   // Add text to clunky_text
    
    /* Initialize a Menu object for the shipMenu*/
    Menu* shipMenu =  new Menu(window, ship_menu, SHIP_MENU_NUM_OF_BUTTONS, SHIP_MENU_VALUES, shipMenuDescriptions, shipMenuTitle);
    
    
    
                       /* CREATE BOARD MENU */
    // For simplicity all menus will have the same y and x coordinates but they can be customized
    title = "BOARD SIZE";
    
    // Note back must be capitalized to BACK for menu function to recognize it properly
    std::string boardMenuDescriptions [BOARD_MENU_NUM_OF_BUTTONS] = {"25", "50", "75", "BACK"};
    int BOARD_MENU_VALUES [BOARD_MENU_NUM_OF_BUTTONS] = {25, 50, 75};     // Values for numOfShips
    
    struct Clunky_Texture board_menu_texture;
    clunky_load_texture(toC_String("/menu_functions/boardMenuButtons.bmp"), &board_menu_texture, window);  // Initialize texture for board menu
    
    
    struct Clunky_Sprite bmb;   //stores sprite image of board menu buttons
    clunky_init_sprite(BOARD_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &board_menu_texture, &bmb); // Initialize sprite

    struct Clunky_Event_Element_Container* board_menu = buttonSetup(BOARD_MENU_NUM_OF_BUTTONS, boardMenuDescriptions, &bmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
    
    struct Clunky_Text* boardMenuTitle = clunky_get_text(x, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for colorMenu title
    
    clunky_add_text(boardMenuTitle, toC_String(title));   // Add text to clunky_text
    
    /* Initialize a Menu object for the boardMenu*/
    Menu* boardMenu =  new Menu(window, board_menu, BOARD_MENU_NUM_OF_BUTTONS, BOARD_MENU_VALUES, boardMenuDescriptions, boardMenuTitle);
    
    
    
    
    Menu* menus[NUM_OF_MENUS] = {mainMenu, colorMenu, shipMenu, boardMenu}; // Holds all menus for easy indexing
                         
                    
    //Flag that determines whether or not to go to next menu or to go back
    int menuFlag; //0 equals BACK, -1 means SDL_quit, 0 < x Means progress to next menu
   
    // Controls each menu loop, used different names for readability, reminds you which menu you are in
    int mainCont = 1;
    int colorCont = 1;
    int shipCont = 1;
    int boardCont = 1;
    
    int i = 0;
    
    
    
  // Menus Main Loop
    while(mainCont){
        // Run Main Menu
        // Also note that when back is encountered 0 is returend
        // Also note if SDL_Quit is encountered -1 is returned
        menuFlag = menus[i]->run(event, &navigation);
        //std::cout << menuFlag;
        if (menuFlag > 0) {
            switch (navigation) {
                case 0:
                    i++;    //increment index to next menu
                    std::cout << "GGP(): START\n";
                    while (colorCont) {
                        menuFlag = menus[i]->run(event, colorTheme);   // Run colorMenu
                        
                        if (menuFlag > 0) {
                            i++;
                            while (shipCont) {
                                menuFlag = menus[i]->run(event, numOfShips);    // Run shipsMenu
                                if (menuFlag > 0){
                                    i++;
                                    while (boardCont) {
                                        menuFlag = menus[i]->run(event, dimensions);    // Run board menu
                                        if (menuFlag > 0) {
                                            for (i = 0; i < NUM_OF_MENUS; i++) {
                                                free(menus[i]);  // Free menus memory
                                            }
                                            return 1;   //Return true to main
                                        } else if (!menuFlag) {
                                            std::cout << "GGP(): BACK\n";
                                            i--;
                                            break;
                                        } else {
                                            std::cout << "GGP(): SDL_QUIT\n";
                                            mainCont = 0;   // Turn off main loop
                                            break;
                                        }
                                    }
                                    
                                } else if (!menuFlag) {
                                    std::cout << "GGP(): BACK\n";
                                    i--;
                                    break;
                                } else {
                                    std::cout << "GGP(): SDL_QUIT\n";
                                    mainCont = 0;   // Turn off main loop
                                    break;
                                }
                            }
                            
                        } else if (!menuFlag){
                            std::cout << "GGP(): BACK\n";
                            i--;
                            break;
                            
                            
                        } else {
                            std::cout << "GGP(): SDL_QUIT\n";
                            mainCont = 0;   // Turn off main loop
                            break;
                        }
                    }
                    break;
                    
                case 1:
                    std::cout << "GGP(): LEADERBOARDS\n";
                    std::cout << "HIGHSCORES:\n *FOO:XXX\n *BAR:XXX\n *FOOBAR:XXX\n";
                    break;
                
                case 2:
                    std::cout << "GGP(): USER MANUAL\n";
                    std::cout << "HOW TO PLAY:\n Click the buttons to navigate menus, when the board is created click the cells to add a planning pin\n";
                    break;
                    
                case 3:
                    std::cout << "GGP(): EXIT\n";
                    mainCont = 0;   // Exit main loop
                    break;
                    
                default:
                    break;
            }
        } else {
            std::cout << "GGP(): SDL_QUIT encountered\n";
            mainCont = 0;   //Exit main loop
        }
    }

    std::cout << "Out of Loop\n";
    //Quit SDL subsystems
    SDL_Quit();
    
    for (i = 0; i < NUM_OF_MENUS; i++) {
        free(menus[i]);  // Free menus memory
    }

    return 0;
}

        
            