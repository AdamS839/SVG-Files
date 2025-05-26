#ifndef __deserializeHelper_HPP
#define __deserializeHelper_HPP
#include <string>

// get the value from the file when reading from it
double dataDoubleAttribute(const std::string& line, const std::string& attr);

// get te color value from the file when reading from it
std::string ColorAttribute(const std::string& line, const std::string& attr);

// get type of the figure from the reading line
std::string getTypeOfFigure(const std::string& line);

#endif