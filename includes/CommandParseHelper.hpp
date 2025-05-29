#ifndef __CommandParseHelper_HPP
#define __CommandParseHelper_HPP
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// replace commas with dots in the string to be able to use std::stod correctly (example: 1,23 -> 1.23)
std::string stodCorrect(std::string line);

// instead of writing criteria for saveas in the map, we just make a function that checks criteria for correct filename
// with a good error message
bool saveasFilenameCriteria(const std::string &filename, std::string &errorMessage);

// return the first word of the line input, which is command
std::string firstWordIsCommand(const std::string &line);

//get the rest of the line input after the command word
std::string getRestOfLine(const std::string& line, const std::string& command);

// splitting the line into tokens of strings in a vector
std::vector<std::string> splitTokens(const std::string& line);

#endif