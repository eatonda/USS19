
#ifndef page_hpp
#define page_hpp
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include "../menu_functions/menuHelpers.hpp"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"


class Page {
    struct Clunky_Window* window;   //Main window to render to
    std::vector<struct Clunky_Text*> content;   //Holds content of page.
    int linesPerPage;
    int pageNumber; //Index for page, array indexing
    std::string* stringContent; //Holds string version of content to load into Clunky_Text elemenets
    int numOfLines; //Total number of lines
    
    Page(struct Clunky_Window* window, std::vector<struct Clunky_Text*> content, int linesPerPage, std::string* stringContent, int numOfLines);
    void _display(struct Clunky_Event* event);   //Displays page
    int run(struct Clunky_Event* event);    //Runs button logic and displays page
    
}
