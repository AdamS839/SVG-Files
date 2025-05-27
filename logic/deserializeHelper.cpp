#include "../includes/deserializeHelper.hpp"

// helping function for parsing double values from .svg file (example: attr=x -> pos = find(x="))
double dataDoubleAttribute(std::istream &in, const std::string &attr){
    std::string token;
    while (in >> token){
        std::size_t pos = token.find(attr + "=\"");
        if (pos != std::string::npos) {
            pos += attr.length() + 2; // skip the attr and the opening quote
            std::size_t end = token.find('"', pos);
            if (end != std::string::npos) {
                try{
                    return std::stod(token.substr(pos, end - pos));
                }
                catch(const std::exception& e){
                    std::cerr << "Couldnt convert value to double here: " << e.what() << std::endl;
                }
            }
        }
        if (token.find('>') != std::string::npos || token.find("/>") != std::string::npos) {
            break;
        }
    }
    return 0.0;
}


// same function as above but for parsing the color parameter (example: attr=red -> pos = find(red+="))
std::string ColorAttribute(std::istream &in, const std::string& attr) {
    std::string token;
    while (in >> token){
        std::size_t pos = token.find(attr + "=\"");
        if (pos != std::string::npos) {
            pos += attr.length() + 2; // skip the attr and the opening quote
            std::size_t end = token.find('"', pos);
            if (end != std::string::npos) {
                return token.substr(pos, end - pos);
            }
        }
        if (token.find('>') != std::string::npos || token.find("/>") != std::string::npos) {
            break;
        }
    }
    return "black";
}

// WORKS OMG
// function to get the type of the figure from the line (exmple: <circle /<ellipse /<rect )
std::string getTypeOfFigure(std::istream &in) {
    std::string token;
    while (in >> token){
        if (!token.empty() && token[0] == '<') {
            // Find the first space or '>' after the '<'
            size_t endPos = token.find_first_of(" >");
            if (endPos == std::string::npos) {
                endPos = token.size();
            }
            return token.substr(1, endPos - 1);
        }
    }
    return "";
}