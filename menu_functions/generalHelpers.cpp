//
//  generalHelpers.cpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/12/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#include "generalHelpers.hpp"

char* toC_String(std::string str){
    /* Convert string to char* for C function calls */
    char* cStr = new char[str.length() + 1]; // For a proper mutable c string create new char [].
    memset(cStr, '\0', str.length());    // For c string safety initialize cPath of null terminators.
    strcpy(cStr, str.c_str());   // Copy contents over to finish conversion}

    return cStr;
}


/*  getMiddle
 Description: Returns value to center image on corresponding axis of window. For example if centering on x axis provide image width value and window width info.
 Parameters: int imageDimension, int windowDimension
 Returns: Returns value to center image on corresponding axis of window.
 Preconditions: Both parameters should be greater than 0. window width must be less than or equal to window dimension.
 */
int getMiddle(int imageDimension, int windowDimension) {
    assert(imageDimension > 0 && windowDimension > 0);  // Assert preconditions
    assert(imageDimension <= windowDimension);
    
    int imageMiddle = imageDimension/2;
    int windowMiddle = windowDimension/2;
    
    int ceiling = 0;
    if(imageDimension % 2 != 0) ceiling = 1;
    
    return (windowMiddle - imageMiddle) + ceiling;   //Center based off of center of image
}
