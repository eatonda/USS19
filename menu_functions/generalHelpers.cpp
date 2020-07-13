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
