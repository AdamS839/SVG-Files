#include "../includes/deserializeHelper.hpp"

// helping function for parsing double values from .svg file (example: attr=x -> pos = find(x="))
double dataDoubleAttribute(std::istream &in, const std::string &attr){
    std::string token;
    while (in >> token){
        // look for the position of the attribute
        std::size_t pos = token.find(attr + "=\"");
        if (pos != std::string::npos) {
            pos += attr.length() + 2; // skip the attr and the opening
            std::size_t end = token.find('"', pos);
            if (end != std::string::npos) {
                try{
                    // convert the value to double and return it
                    return std::stod(token.substr(pos, end - pos));
                }
                // catch error
                catch(const std::exception& e){
                    std::cerr << "Couldnt convert value to double here: " << e.what() << std::endl;
                }
            }
        }
        // if at the end, exit loop and retunr 0
        if (token.find('>') != std::string::npos || token.find("/>") != std::string::npos) {
            break;
        }
    }
    return 0.0;
}


// same function as above but for parsing the color parameter (example: attr=red -> pos = find(red+="))
std::string ColorAttribute(std::istream &in, const std::string& attr) {
    std::string token;
    while (in >> token) {
        // look for the position
        std::size_t pos = token.find(attr + "=\"");
        if (pos != std::string::npos) {
            pos += attr.length() + 2; // skip the attr and the opening quote
            std::size_t end = token.find('"', pos);
            if (end != std::string::npos) {
                return token.substr(pos, end - pos);
            }
        }
        // if at the end, break loop and return color "black"
        if (token.find('>') != std::string::npos || token.find("/>") != std::string::npos) {
            break;
        }
    }
    return "black";
}

// function to get the type of the figure from the line (exmple: <circle /<ellipse /<rect )
std::string getTypeOfFigure(std::istream &in) {
   std::string token;
    while (in >> token) {
        // check if token is not empty and starts with <
        if (!token.empty() && token[0] == '<') {
            // find 'space' or '>' to get the end
            size_t endPos = token.find_first_of(" >");
            // if not found, just use the length of the token
            if (endPos == std::string::npos) {
                endPos = token.size();
            }
            // return from 1 to end - 1
            return token.substr(1, endPos - 1);
        }
    }
    // if no type, then empty string return
    return "";
}