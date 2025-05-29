#include "../includes/ColorHelper.hpp"
#include <iostream>
#include <stdexcept>

// convert string to color object (or rgb value)
Color stringToColor(const std::string& str) {
    if (str == "red") return red;
    if (str == "green") return green;
    if (str == "blue") return blue;
    if (str == "yellow") return yellow;
    if (str == "purple") return purple;
    if (str == "black") return black;
    if (str == "white") return white;

    if (str.rfind("rgb(", 0) == 0 && str.back() == ')'){
        std::string innerCol = str.substr(4, str.length() - 5);
        std::size_t firstGap = innerCol.find(',');
        std::size_t secondGap = innerCol.find(',', firstGap + 1);
        if(firstGap != std::string::npos && secondGap != std::string::npos){
            try{
                unsigned int r = std::stoi(innerCol.substr(0,firstGap));
                unsigned int g = std::stoi(innerCol.substr(firstGap + 1, secondGap - firstGap - 1));
                unsigned int b = std::stoi(innerCol.substr(secondGap + 1));
                return {r,g,b};
            }
            catch(const std::exception &e){
                std::cerr << "Couldnt parse color: " << e.what() << std::endl;
            }
        }
    }

    throw std::invalid_argument("Unknown color: " + str);
}

// get color code as a string word or rgb value with ANSI to print color in terminal
std::string colorToStringAnsi(const Color& col) {
    if (col == red)    return "\033[31mred\033[0m";
    if (col == green)  return "\033[32mgreen\033[0m";
    if (col == blue)   return "\033[34mblue\033[0m";
    if (col == yellow) return "\033[33myellow\033[0m";
    if (col == purple) return "\033[35mpurple\033[0m";
    if (col == black)  return "\033[30mblack\033[0m";
    if (col == white)  return "\033[37mwhite\033[0m";
    
    return "rgb(" + std::to_string(col.r) + "," + std::to_string(col.g) + "," + std::to_string(col.b) + ")";
}

// get color code as a string word or rgb value
std::string colorToString(const Color &col) {
    if (col == red) return "red";
    if (col == green) return "green";
    if (col == blue) return "blue";
    if (col == yellow) return "yellow";
    if (col == purple) return "purple";
    if (col == black) return "black";
    if (col == white) return "white";

    return "rgb(" + std::to_string(col.r) + "," + std::to_string(col.g) + "," + std::to_string(col.b) + ")";
}

// cosmetic function used in printing to terminal with colors for better visibility
std::string valueColorAnsi(const Color &col){
    if(col == red) return "\033[31m";
    if(col == green) return "\033[32m";
    if(col == light_green) return "\033[92m";
    if(col == blue) return "\033[34m";
    if(col == yellow) return "\033[33m";
    if(col == purple) return "\033[35m";
    if(col == black) return "\033[30m";
    if(col == white) return "\033[37m";
    return "\033[0m";
}

// return the default ANSI color code to reset the color in terminal
std::string defaultAnsiCol(){
    return "\033[0m";
}