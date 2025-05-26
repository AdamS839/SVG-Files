#include "../includes/deserializeHelper.hpp"
#include <string>
#include <algorithm>


// helping function for parsing double values from .svg file (example: attr=x -> pos = find(x="))
double dataDoubleAttribute(const std::string& line, const std::string& attr) {
    //looking for \ x=", y=", ect.=" \ to get the value after the keyword
    std::size_t pos = line.find(attr + "=\"");
    if (pos == std::string::npos) return 0.0;

    // adding 2 to the position to skip the  ' =" '
    pos += attr.length() + 2;

    // looking for the next " to get the end of the value (example: x="1.23")
    std::size_t end = line.find('"', pos);

    // if the end is not found, return 0.0
    if (end == std::string::npos) return 0.0;
    return std::stod(line.substr(pos, end - pos));
}


// same function as above but for parsing the color parameter (wxample: attr=red -> pos = find(red+="))
std::string ColorAttribute(const std::string& line, const std::string& attr) {
    std::size_t pos = line.find(attr + "=\"");
    if (pos == std::string::npos) return "black";

    pos += attr.length() + 2;
    std::size_t end = line.find('"', pos);

    if (end == std::string::npos) return "black";
    return line.substr(pos, end - pos);
}

// function to get the type of the figure from the line (exmple: <circle /<ellipse /<rect )
std::string getTypeOfFigure(const std::string& line) {
    std::size_t pos = line.find('<');
    if (pos == std::string::npos) return "";

    pos += 1;
    std::size_t end = line.find(' ', pos);
    if (end == std::string::npos) end = line.find('>', pos);

    return line.substr(pos, end - pos);
}
