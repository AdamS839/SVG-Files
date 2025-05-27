#ifndef __deserializeHelper_HPP
#define __deserializeHelper_HPP
#include <string>
#include <istream>
#include <stdexcept>
#include <iostream>

// функция за извличане на стойността на даден атрибут от реда на файла
// get the value from the file when reading from it
double dataDoubleAttribute(std::istream &in, const std::string &attr);

// същата функция като горната, но за извличане на цвета от реда на файла
// get te color value from the file when reading from it
std::string ColorAttribute(std::istream &in, const std::string &attr);

// функция за вземане на типа на фигурата от реда на файла
// get type of the figure from the reading line
std::string getTypeOfFigure(std::istream &in);

#endif