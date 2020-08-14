#ifndef inputName_hpp
#define inputName_hpp

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include "./clunky_gl/clunkyCore.h"
#include "./clunky_gl/clunkyHash.h"
#include "./clunky_gl/clunkyEventElements.h"

String inputName(struct Clunky_Window* window, struct Clunky_Event* event);

#endif

