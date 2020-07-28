

#ifndef generalHelpers_hpp
#define generalHelpers_hpp

#include <stdio.h>
#include<string>
#include<vector>
#include<fstream>
#include <iostream>

#include <locale>

char* toC_String(std::string str);  // Converts std::string to a mutable c string

int getMiddle(int imageDimension, int windowDimension); //Calculates middle of screen  based on a on a image dimension(width or height) and the window dimension(width or height).

void clunkifyStr(char* str); //Replaces invalid characters with white space characters ' '

void fileToStrings(std::string path, std::vector<char*> &vector);  //Converts a text file into an vector of c strings

#endif /* generalHelpers_hpp */


