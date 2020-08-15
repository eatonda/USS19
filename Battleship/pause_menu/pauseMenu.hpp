
#include "../menu_functions/menu.hpp"

#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

// gets the user selection from the pause menu
// - if the SDL_QUIT is encountered, -1 is returned
// - if the user selects restart game, 1 is returned
// - if the user selects exit game, 2 is returned
// - if the user simply exits the menu, 3 is returned
int getPauseSelection(struct Clunky_Window* window, struct Clunky_Event* event);

#endif
