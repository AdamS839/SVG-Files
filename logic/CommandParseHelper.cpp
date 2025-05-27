#include "../includes/CommandParseHelper.hpp"

// replace comma with dot because the string wont be parsed to double (stod)
std::string stodCorrect(std::string line){
    std::replace(line.begin(), line.end(), ',', '.');
    return line;
}

// criteria to validate the filename for saving (also used in opening the correct file)
bool saveasFilenameCriteria(const std::string &filename, std::string &errorMessage) {
    if (filename.empty()) {
        errorMessage = "Filename cant be empty";
        return false;
    }
    else if(filename.find(' ') != std::string::npos){
        errorMessage = "Filename cant contain spaces";
        return false;        
    }
    else if(filename.find('/') != std::string::npos || filename.find('\\') != std::string::npos){
        errorMessage = "Filename cant contain slashes";
        return false;
    }
    else if(filename.find('.') == std::string::npos) {
        errorMessage = "Filename must contain an extension";
        return false;
    }
    else if(filename.find('.') != filename.rfind('.')) {
        errorMessage = "Filename must have only one extension";
        return false;
    }
    else if(filename.size() < 4 || filename.substr(filename.size() - 4) != ".svg") {
        errorMessage = "Filename must end with .svg";
        return false;
    }
    return true;
}

// get the first word of the line input, which is a command
std::string firstWordIsCommand(const std::string &line){
    std::size_t i = 0;
    while(i < line.length() && line[i] != ' ' && line[i] != '\t'){
        ++i;
    }
    return line.substr(0, i);
}

// return everything after the command in the line input
std::string getRestOfLine(const std::string& line, const std::string& command) {
    if (line.length() > command.length()){
        return line.substr(command.length() + 1);
    }
    return "";
}

// helping function for little description about other operations (will add more info about creat/within/erase/translate)
int help(){
    std::cout << "open <file>                                              - Opens SVG file or create a new one" << std::endl;
    std::cout << "close                                                    - Closes the current file" << std::endl;
    std::cout << "save                                                     - Save changes to the current file" << std::endl;
    std::cout << "saveas <newfilename>                                     - Save changes to a new file" << std::endl;
    std::cout << "print                                                    - Prints all figures" << std::endl;
    std::cout << "create [figure(params)]                                  - Creates a new new figure from the parameters given after the command" << std::endl;
    std::cout << "erase <index>                                            - Erases a figure with given index" << std::endl;
    std::cout << "translate [vertical=] [horizontal=] (optional)[id=]      - Translates figures(1 figure if given index/all figures if not given index)" <<std::endl;
    std::cout << "within [figure(params)]                                  - Prints figures that are inside another figure" << std::endl;
    std::cout << "help                                                     - Shows this list of commands" << std::endl;
    std::cout << "exit                                                     - Exists the program" << std::endl;
    return 0;
}
