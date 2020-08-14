#include "gameOver.hpp"

const int LEADERBOARD_MENU_NUM_OF_BUTTONS = 1;

/* Constants for all menu buttons */
const int NUM_OF_SPRITE_COLS = 2;
const int BUTTON_WIDTH = 165;
const int BUTTON_HEIGHT = 160;

void winnerScreen(struct Clunky_Window* window);
void loserScreen(struct Clunky_Window* window);

void gameOver( struct Clunky_Window* window, struct Clunky_Event* event, int dimensions, int numOfRounds, int winnerFlag) {
    
    int tempValue;
    int CENTER_X = window->width * 0.5;
    int CENTER_y = window->height * 0.5;
    
    // WINNER
    if (winnerFlag) {
        winnerScreen(window);   // Display Winner on Screen
        
        // Get score
        int score = calcScore(numOfRounds, dimensions, dimensions);
        
        // Check if high score
        if(isHighScore(score)) {
            
            // Get Name
            std::string name = std::string(inputName(window, event));
            
            // Save Score
            enterScore(score, name);
            
            
                                 /* CREATE LEADERBOARD MENU */
                std::string title = "LEADERBOARD";
                
                // Note main menu must be capitalized to MAIN MENU for menu function to recognize it properly
                std::string scoreMenuDescriptions [LEADERBOARD_MENU_NUM_OF_BUTTONS] = {"EXIT"};
                
                struct Clunky_Texture score_menu_texture;
                clunky_load_texture(toC_String("./menu_functions/menu_assets/pageMenuButtons.bmp"), &score_menu_texture, window);  // Initialize texture for board menu
                
                struct Clunky_Sprite lmb;   //stores sprite image of leader menu buttons
                clunky_init_sprite(LEADERBOARD_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &score_menu_texture, &lmb); // Initialize sprite
                
                // Buttons for pages should be at the bottom of the screen in a single row
                // Same xCoordinates as USER MANUAL
                int xCoordinates[LEADERBOARD_MENU_NUM_OF_BUTTONS];
                xCoordinates[0] = window->width * 0.20;
            
                int yCoordinates[LEADERBOARD_MENU_NUM_OF_BUTTONS];
                yCoordinates[0] = window->height * 0.95;
                
                
                struct Clunky_Event_Element_Container* score_menu = buttonSetup(LEADERBOARD_MENU_NUM_OF_BUTTONS, scoreMenuDescriptions, &lmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
                
                struct Clunky_Text* scoreMenuTitle = clunky_get_text(window->width * 0.4, window->height * 0.15, window->width * 0.50, window->height * 0.10, 1.0, window);    // Get Clunky_Text instance for colorMenu title
                
                clunky_add_text(scoreMenuTitle, toC_String(title));   // Add text to clunky_text
                
                std::string path = "./data/high_scores/scores.txt";
                std::vector<char*> scoreStrings;
                //printf("|||||||||\n");
                fileToStrings(path, scoreStrings);    //Get cstring version of text file
               // printf("|||||||||\n");
                
                // Trace statement
                for(int i = 0; i < scoreStrings.size(); i ++){
                    printf("GGP() %s\n", scoreStrings[i]);
                }

             
                struct Clunky_Text* score_content[scoreStrings.size()];
                int lineOffset = window->height * 0.05;
                int lineY = window->height * 0.3;
                int linesPerPage = 10;   //To show multipage functionality
                int count = 0;
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
                
            
            Menu* scoreMenu = new Menu(window, score_menu, LEADERBOARD_MENU_NUM_OF_BUTTONS, scoreMenuDescriptions, scoreMenuTitle, score_content, 1, linesPerPage);
            
            // Display Leaderboard
            if (scoreMenu->run(event, &tempValue) == -1) {
                delete scoreMenu;
                SDL_QUIT();
            }
            
        }
        
        
    } else {
        //Loser
        loserScreen(window);    // Display you lose
        
        
    }
}

void winnerScreen(struct Clunky_Window* window) {
    int CENTER_x = window->width * 0.5;
    int CENTER_y = window->height * 0.5;
    
    struct Clunky_Text* winnerText = clunky_get_text(CENTER_x, CENTER_y, 64, 1.,window);
    clunky_add_text(winnerText, "WINNER");
    clunky_render_text(winnerText, window);
    
    for (int i = 0; i < 500; i++) {
        //Pause screen to show text
    }
    
}

void loserScreen(struct Clunky_Window* window) {
    int CENTER_x = window->width * 0.5;
    int CENTER_y = window->height * 0.5;
    
    struct Clunky_Text* winnerText = clunky_get_text(CENTER_x, CENTER_y, 64, 1.,window);
    clunky_add_text(winnerText, "YOU LOSE");
    clunky_render_text(winnerText, window);
    
    for (int i = 0; i < 500; i++) {
        //Pause screen to show text
    }
    
}
