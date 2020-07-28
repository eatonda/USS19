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



/*  clunkifyStr
 Description: Replaces invalid characters with white space characters ' ' or capitalized characters
 Parameters: std::string* str
 Preconditions: str != NULL
 */
void clunkifyStr(char* str){
    assert(str != NULL);
    
    int ascii;
    
    // Convert to capital letters
    for (int i = 0; i < strlen(str); i++){
        ascii = (int)str[i];
        
        if (ascii >= 98 && ascii <= 122) {
            ascii -= 32;    // Convert to capital letter
            str[i] = (char)ascii;
        }
    }
    
    for(int i = 0; i < strlen(str); i++){
        if (!std::isalnum(str[i]) && str[i] != '.' && str[i] != '(' && str[i] != ')' && str[i] != ':' && str[i] != '?') {
            // Convert invalid character to white space
            str[i] = ' ';
        }
    }
}


/*  fileToStrings
 Description: This function converts a text file's contents into a vector of strings.
 Parameters: std::string path, std::vector<std::string> &vect
 Preconditions: vector != NULL, text must be Clunky_Text characters
 */
void fileToStrings(std::string path, std::vector<char*> &vect){
    
    
    std::string line;   // Holds read in line of text from file
    char* cString;
    
    std::ifstream inputFile;
    inputFile.open(path);   //Open text file
    
    if (inputFile) {
        // If file opens successfully read in contents
        while(getline(inputFile, line)){
            std::cout << line << std::endl; //Trace statement for debugging
            cString = toC_String(line); // Convert to a c style string
            clunkifyStr(cString); //Remove invalid characters
            
            vect.push_back(cString);   //Add clunky string to vect
        }
    } else {
        std::cout << "Error cannot open " << path << std::endl;
    }
}
