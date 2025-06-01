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
    else if(filename.rfind('.') == std::string::npos) {
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
    if (line.length() > command.length())
        return line.substr(command.length() + 1);
    return "";
}


std::vector<std::string> splitTokens(const std::string& line){
    std::vector<std::string> tokens;
    std::size_t pos = 0, next_pos;
    while ((next_pos = line.find(' ', pos)) != std::string::npos) {
        if (next_pos > pos) tokens.push_back(line.substr(pos, next_pos - pos));
        pos = next_pos + 1;
    }
    if (pos < line.length()) tokens.push_back(line.substr(pos));
    return tokens;
}