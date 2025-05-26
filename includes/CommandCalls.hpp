#ifndef __CommandCalls_HPP
#define __CommandCalls_HPP
#include "Figure.hpp"
#include <iostream>
#include <vector>

void withinCommandCall(const Figure &, const std::vector<Figure*> &);
bool createFigure(const std::string &, std::vector<Figure*> &);
bool erase(const std::string &, std::vector<Figure*> &);
bool translateFigures(const std::string &, std::vector<Figure*> &);
void printFigures(const std::vector<Figure*> &);

#endif