#ifndef __CommandParseHelper_HPP
#define __CommandParseHelper_HPP
#include <string>
#include <algorithm>
#include <iostream>

// File for helping functions for parsing and other useful functions i can use to save space

// replace commas with dots in the string to be able to use std::stod correctly (example: 1,23 -> 1.23)
std::string stodCorrect(std::string line);

// instead of writing criteria for saveas in the map, we just make a function that checks criteria for correct filename
// with a good error message
bool saveasFilenameCriteria(const std::string &filename, std::string &errorMessage);

// return the first word of the line input, which is command
std::string firstWordIsCommand(const std::string &line);

//get the rest of the line input after the command word
std::string getRestOfLine(const std::string &line, const std::string& command);

// print out message, containing all commands and little description about them
int help();

#endif