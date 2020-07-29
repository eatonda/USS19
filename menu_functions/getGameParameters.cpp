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
    
/* Constants for Help MENU */
const int HELP_MENU_NUM_OF_BUTTONS = 3;
    
/* Constant for menus array */
const int NUM_OF_MENUS = 6;
   
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
    clunky_load_texture(toC_String("/menu_functions/menu_assets/mainMenuButtons.bmp"), &main_menu_texture, window);  // Initialize texture for main menu
    
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
    clunky_load_texture(toC_String("/menu_functions/menu_assets/colorMenuButtons.bmp"), &color_menu_texture, window);  // Initialize texture for color menu
    
    
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
    clunky_load_texture(toC_String("/menu_functions/menu_assets/shipMenuButtons.bmp"), &ship_menu_texture, window);  // Initialize texture for ship menu
    
    
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
    std::string boardMenuDescriptions [BOARD_MENU_NUM_OF_BUTTONS] = {"5", "7", "10", "BACK"};
    int BOARD_MENU_VALUES [BOARD_MENU_NUM_OF_BUTTONS] = {25, 50, 75};     // Values for numOfShips
    
    struct Clunky_Texture board_menu_texture;
    clunky_load_texture(toC_String("/menu_functions/menu_assets/boardMenuButtons.bmp"), &board_menu_texture, window);  // Initialize texture for board menu
    
    
    struct Clunky_Sprite bmb;   //stores sprite image of board menu buttons
    clunky_init_sprite(BOARD_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &board_menu_texture, &bmb); // Initialize sprite

    struct Clunky_Event_Element_Container* board_menu = buttonSetup(BOARD_MENU_NUM_OF_BUTTONS, boardMenuDescriptions, &bmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
    
    struct Clunky_Text* boardMenuTitle = clunky_get_text(x, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for colorMenu title
    
    clunky_add_text(boardMenuTitle, toC_String(title));   // Add text to clunky_text
    
    /* Initialize a Menu object for the boardMenu*/
    Menu* boardMenu =  new Menu(window, board_menu, BOARD_MENU_NUM_OF_BUTTONS, BOARD_MENU_VALUES, boardMenuDescriptions, boardMenuTitle);
    
    
                    /* CREATE HELP MENU */
    title = "USER MANUAL";
    
    // Note main menu must be capitalized to MAIN MENU for menu function to recognize it properly
    std::string helpMenuDescriptions [HELP_MENU_NUM_OF_BUTTONS] = {"MAIN MENU", "PREVIOUS", "NEXT"};
    
    struct Clunky_Texture help_menu_texture;
    clunky_load_texture(toC_String("/menu_functions/menu_assets/pageMenuButtons.bmp"), &help_menu_texture, window);  // Initialize texture for board menu
    
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
    
    struct Clunky_Event_Element_Container* help_menu = buttonSetup(HELP_MENU_NUM_OF_BUTTONS, helpMenuDescriptions, &hmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
    
    struct Clunky_Text* helpMenuTitle = clunky_get_text(window->width * 0.4, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for colorMenu title
    
    clunky_add_text(helpMenuTitle, toC_String(title));   // Add text to clunky_text
    
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
    int linesPerPage = 2;   //To show multipage functionality
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
    
    Menu* helpMenu = new Menu(window, help_menu, HELP_MENU_NUM_OF_BUTTONS, helpMenuDescriptions, helpMenuTitle, help_content, 4, linesPerPage);
    
                                /* CREATE LEADERBOARD MENU */
        title = "LEADERBOARD";
        
        // Note main menu must be capitalized to MAIN MENU for menu function to recognize it properly
        std::string scoreMenuDescriptions [HELP_MENU_NUM_OF_BUTTONS] = {"MAIN MENU", "PREVIOUS", "NEXT"};
        
        struct Clunky_Texture score_menu_texture;
        clunky_load_texture(toC_String("/menu_functions/menu_assets/pageMenuButtons.bmp"), &score_menu_texture, window);  // Initialize texture for board menu
        
        struct Clunky_Sprite lmb;   //stores sprite image of leader menu buttons
        clunky_init_sprite(HELP_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &score_menu_texture, &lmb); // Initialize sprite
        
        // Buttons for pages should be at the bottom of the screen in a single row
        // Same xCoordinates as USER MANUAL
        
        
        struct Clunky_Event_Element_Container* score_menu = buttonSetup(HELP_MENU_NUM_OF_BUTTONS, scoreMenuDescriptions, &lmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
        
        struct Clunky_Text* scoreMenuTitle = clunky_get_text(window->width * 0.4, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for colorMenu title
        
        clunky_add_text(scoreMenuTitle, toC_String(title));   // Add text to clunky_text
        
        path = "./data/high_scores/scores.txt";
        std::vector<char*> scoreStrings;
        //printf("|||||||||\n");
        fileToStrings(path, scoreStrings);    //Get cstring version of text file
       // printf("|||||||||\n");
        
        // Trace statement
        for(int i = 0; i < scoreStrings.size(); i ++){
            printf("GGP() %s\n", scoreStrings[i]);
        }

     
        struct Clunky_Text* score_content[scoreStrings.size()];
        lineOffset = window->height * 0.05;
        lineY = window->height * 0.3;
        linesPerPage = 10;   //To show multipage functionality
        count = 0;
        for(int i = 0; i < scoreStrings.size(); i++) {
            if (count >= linesPerPage) {
                count = 0;  //Reset count
                lineY = window->height * 0.3;   //Reset y
            }
            count++;
            printf(">>%d, %d\n", i, scoreStrings.size());  // Trace statement
            score_content[i] = clunky_get_text(window->width * 0.4, lineY, window->width * 0.9, window->height * 0.10, 1.0, window);
            //printf("===\n");
            //clunky_add_text(content[i], toC_String(words[i]));
            clunky_add_text(score_content[i], scoreStrings[i]);
            //printf("++++\n");
            lineY+= lineOffset;
        }
        
    
    Menu* scoreMenu = new Menu(window, score_menu, HELP_MENU_NUM_OF_BUTTONS, scoreMenuDescriptions, scoreMenuTitle, score_content, 1, linesPerPage);
    
    
    Menu* menus[NUM_OF_MENUS] = {mainMenu, colorMenu, shipMenu, boardMenu, helpMenu, scoreMenu}; // Holds all menus for easy indexing
                         
                    
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
                    if (menus[5]->runPage(event) == -1){
                        mainCont = 0;   //Break loop
                        
                    }
                    break;
                
                case 2:
                    std::cout << "GGP(): USER MANUAL\n";
                    std::cout << "HOW TO PLAY:\n Click the buttons to navigate menus, when the board is created click the cells to add a planning pin\n";
                    if (menus[4]->runPage(event) == -1){
                        mainCont = 0;   //Break loop
                        
                    }
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

        
            
