#include "../includes/Figure.hpp"
#include "../includes/Circle.hpp"
#include "../includes/Rect.hpp"
#include "../includes/Ellipse.hpp"
#include "../includes/CommandCalls.hpp"
#include "../includes/ColorHelper.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

// helper function to call within for each figure
void withinCommandCall(const Figure &fig, const std::vector<Figure*> &figures){
    // Without indices
    // for(const Figure *f : figures){
    //     if(f->within(fig)) f->print(std::cout);
    // }
    bool isfound = false;
    for (std::size_t i = 0; i < figures.size(); ++i){
        if(figures[i]->within(fig)){
            std::cout << i + 1 << ". ";
            figures[i]->printToTerminalWithColors(std::cout);
            isfound = true;
        }
    }
    if(!isfound){
        std::cout << "No figures within the given figure with type: "<< fig.getType() << std::endl;
    }
}

bool createFigure(const std::string& command, std::vector<Figure*>& figures) {

    // get position of the spaces
    std::size_t pos = 0;
    std::size_t next_pos;
    std::vector<std::string> token;


    // Split command into tokens
    while((next_pos = command.find(' ', pos)) != std::string::npos){
        if(next_pos > pos){
            token.push_back(command.substr(pos, next_pos - pos));
        }
        pos = next_pos + 1;
    }
    if(pos < command.length()){
        token.push_back(command.substr(pos));
    }
    if(token.empty()){
        std::cerr << "No command given" << std::endl;
        return false;
    }

    // first token is figure type
    const std::string &type = token[0];

    // using the factory function to create the figure
    // and then using the deserialization function to parse the parameters
    try{
        Figure *fig = factory(type);
        fig->parseFromTokens(token);
        figures.push_back(fig);
        std::cout << "Successfully created " << type << "\n";
        return true;
    }
    catch(const std::exception &e){
        std::cerr << "Failed to create figure: " << e.what() << std::endl;
        return false;
    }    
}

bool erase(const std::string &line, std::vector<Figure*> &figures){
    try{
        std::size_t index = std::stoi(line);
        if(index <= 0 || index > figures.size()){
            std::cerr << "Theres no figure number " << index << "!\n";
            return false;
        }
        Figure *toDelete = figures[index - 1];
        std::string type = toDelete->getType();

        delete toDelete;

        figures.erase(figures.begin() + index - 1);
        std::cout << "Erased a " << type << " " << "(" << index << ")" << "\n";
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Invalid index. Failed at: " << e.what() << '\n';
        return false;
    }
    
}

bool translateFigures(const std::string& command, std::vector<Figure*>& figures) {
    try {
        double vertical = 0.0, horizontal = 0.0;
        int index = -1;

        // Parse vertical
        size_t vertPos = command.find("vertical=");
        if (vertPos == std::string::npos) {
            throw std::invalid_argument("Missing vertical parameter");
        }
        vertPos += 9; // length of "vertical="
        size_t vertEnd = command.find(' ', vertPos);

        // convert the string to double, using stodCorrect to replace commas with dots (example in deserializeHelper.hpp)
        vertical = std::stod(command.substr(vertPos, vertEnd - vertPos));


        // the same for horizontal

        // Parse horizontal
        size_t horizPos = command.find("horizontal=");
        if (horizPos == std::string::npos) {
            throw std::invalid_argument("Missing horizontal parameter");
        }
        horizPos += 11; // length of "horizontal="
        size_t horizEnd = command.find(' ', horizPos);
        horizontal = std::stod(command.substr(horizPos, horizEnd - horizPos));

        // Parse optional index
        size_t indexPos = command.find("id=");
        if (indexPos != std::string::npos) {
            indexPos += 3; // length of "id="
            size_t indexEnd = command.find(' ', indexPos);
            index = std::stoi(command.substr(indexPos, indexEnd - indexPos)) - 1;
            if (index < 0 || index > figures.size()) {
                std::cout << figures.size() << std::endl;
                std::cout << index << std::endl;

                std::cerr << "Invalid figure index.\n";
                return false;
            }
        }

        // Apply translation
        if (index == -1) {
            for (Figure* fig : figures) fig->translate(horizontal, vertical);
            std::cout << "Translated all figures\n";
        } else {
            figures[index]->translate(horizontal, vertical);
            std::cout << "Translated figure " << (index + 1) << "\n";
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Couldn't apply translate: " << e.what() << "\n";
        return false;
    }
}

void printFigures(const std::vector<Figure*>& figures){
    if(figures.empty()){
        std::cout << "There are no figures to print." << std::endl;
        return;
    }
    for (std::size_t i = 0; i < figures.size(); ++i) {
        std::cout << i+1 << ". ";
        figures[i]->print(std::cout);
    }
}

