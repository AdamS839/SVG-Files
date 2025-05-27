#ifndef __CommandCalls_HPP
#define __CommandCalls_HPP
#include "Figure.hpp"
#include <iostream>
#include <vector>

// Function for calling within function for each figure
void withinCommandCall(const Figure &, const std::vector<Figure*> &);

// create a figure from a string
bool createFigure(const std::string &, std::vector<Figure*> &);

// erase a figure by index
bool erase(const std::string &, std::vector<Figure*> &);

// translate figures by X and Y coordinates
bool translateFigures(const std::string &, std::vector<Figure*> &);

// print all figures
void printFigures(const std::vector<Figure*> &);

#endif