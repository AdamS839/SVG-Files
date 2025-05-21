#ifndef __ColorHelper_HPP
#define __ColorHelper_HPP
#include <string>

struct Color{
    unsigned int r,g,b;

bool operator==(const Color &other) const{
    return r == other.r && g == other.g && b == other.b;
}
};

const Color red = {255,0,0},
            green = {0,255,0},
            blue = {0,0,255},
            yellow = {255,255,0},
            white = {255,255,255},
            purple = {128,0,128}, 
            black = {0,0,0};

Color stringToColor(const std::string &);

std::string colorToStringAnsi(const Color&);

std::string colorToString(const Color &col);

#endif
