//
//  generalHelpers.hpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/12/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#ifndef generalHelpers_hpp
#define generalHelpers_hpp

#include <stdio.h>
#include<string>

char* toC_String(std::string str);  // Converts std::string to a mutable c string

int getMiddle(int imageDimension, int windowDimension); //Calculates middle of screen  based on a on a image dimension(width or height) and the window dimension(width or height).
#endif /* generalHelpers_hpp */
