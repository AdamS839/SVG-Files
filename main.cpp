#include "includes/Figure.hpp"
#include "includes/Circle.hpp"
#include "includes/Rect.hpp"
#include "includes/Ellipse.hpp"
#include "includes/deserializeHelper.hpp"
#include "includes/CommandParseHelper.hpp"
#include "includes/MapOperations.hpp"
#include <iostream>

int main() {
    Manager manager;
    std::string line;
    std::cout << "Enter command to call: ";
    
    while (true){
        std::cout << "> ";
        if(!std::getline(std::cin, line)) break;
        if(line.empty()) continue;

        std::string command = firstWordIsCommand(line);
        std::string restline = getRestOfLine(line, command);

        // implement map for execute()
        //instead of auto - use: std::map<std::string, std::function<Command*(const std::string &, std::vector<Figure*> &)>> commandFactory = createCommandFactory(manager);
        auto commandFactory = createCommandFactory(manager);

        //instead of auto - use: std::map<std::string, std::function<Command*(const std::string&, std::vector<Figure*>&)>>::iterator it = commandFactory.find(command);
        auto it = commandFactory.find(command);
        if (it != commandFactory.end()) {
            Command* cmd = it->second(restline, manager.getFigures());
            if (cmd) {
                cmd->execute();
                delete cmd;
            }
        } else{
            std::cerr << "Unknown command: \"" << command << "\"\n";
        }
    }

    return 0;
}