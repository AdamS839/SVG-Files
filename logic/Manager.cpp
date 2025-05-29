#include "../includes/Manager.hpp"
#include "../includes/Circle.hpp"
#include "../includes/Rect.hpp"
#include "../includes/Ellipse.hpp"
#include "../includes/Figure.hpp"
#include "../includes/ColorHelper.hpp"
#include "../includes/CommandParseHelper.hpp"
#include <fstream>

Manager::Manager() : isFileOpen(false) {}

// destructor with closing the file
Manager::~Manager() {
    close(true);
}

// opening the file, if it exists, read the figures and store the data in vector of figures
bool Manager::open(const std::string &pathname){

    std::string error;
    if(!saveasFilenameCriteria(pathname, error)){
        std::cerr << error << std::endl;
        return false;
    }

    if(isFileOpen){
        std::cout << "A file is already open. Please close it." << std::endl;
        return false;
    }

    std::ifstream in(pathname);
    //if not opened
    if(!in.is_open()){
        // If the file does not exist, create a new one
        std::ofstream out(pathname);

        if(!out.is_open()){
            std::cout << "Failed to create file: " << pathname << std::endl;
            return false;
        }
        std::cout << "File created and opened: " << pathname << std::endl;
        currentFilename = pathname;
        isFileOpen = true;  
        return true;
    }
    
    std::string line;
    
    while(std::getline(in, line)){
        // Skip lines that do not contain any figure tags
        if(line.find("<rect") == std::string::npos && 
            line.find("<circle") == std::string::npos && 
            line.find("<ellipse") == std::string::npos) {
            continue; 
        }
        try{
            std::istringstream convert(line);
            Figure *fig = Figure::deserializeAll(convert);
            if(fig){
                figures.push_back(fig);
            }
        }
        catch(std::exception &e){
            std::cerr << "Error with parsing figures from line: " << e.what() << std::endl;
        }
    }
    std::cout << "Successfully opened: " << pathname << std::endl;
    currentFilename = pathname;
    isFileOpen = true;
    return true;
}

// close the file, delete all figures and print a message
void Manager::close(bool outputMessage){
    if(!isFileOpen){
        if(!outputMessage){
            std::cout << "No file is opened." << std::endl;
        }
        return;
    }
    for (Figure *fig : figures){
        delete fig;
    }
    figures.clear();
    if(!outputMessage){
        std::cout << "Successfully closed: " << currentFilename << std::endl;
    }
    currentFilename.clear();
    isFileOpen = false;
}

// save the current file to the itself, overwriting it
bool Manager::save() const{
    if(!isFileOpen){
        std::cout << "No file is open." << std::endl;
        return false;
    }
    std::ofstream out(currentFilename);
    if(!out.is_open()){
        std::cout << "Failed to save to file: " << currentFilename << std::endl;
        return false;
    }
    out << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
    out << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n";
    out << "  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    out << "<svg>\n";
    for (Figure *fig : figures){
        fig->print(out);
    }
    out << "</svg>\n";
    std::cout << "Successfully saved changes to " << currentFilename << std::endl;
    return true;
}

// save the current file to a new filename
// reuse the code from save() but just add a filename param and check if the name is the same as currentFilename
bool Manager::saveAs(const std::string &pathname){
    std::string printError;
    if(!saveasFilenameCriteria(pathname, printError)){
        std::cerr << printError << std::endl;
        return false;
    }
    if(pathname == currentFilename){
        std::cout << "Cant use the same filename for 'saveas'" << std::endl;
        return false;
    }
    std::string saveCurrName = currentFilename;
    currentFilename = pathname;
    bool result = save();
    if(!result){
        currentFilename = saveCurrName;
    }
    return result;
}

// print out all functions and little description about them
int Manager::help() const{
    std::cout << "open <file>                                              - Opens SVG file or create a new one" << std::endl;
    std::cout << "close                                                    - Closes the current file" << std::endl;
    std::cout << "save                                                     - Save changes to the current file" << std::endl;
    std::cout << "saveas <newfilename>                                     - Save changes to a new file" << std::endl;
    std::cout << "print                                                    - Prints all figures" << std::endl;
    std::cout << "create [figure(params)]                                  - Creates a new new figure from the parameters given after the command" << std::endl;
    std::cout << "erase <index>                                            - Erases a figure with given index" << std::endl;
    std::cout << "translate [vertical=]/[horizontal=]/(optional)[id=]      - Translates figures(1 figure if given index/all figures if not given index)" <<std::endl;
    std::cout << "within [figure(params)]                                  - Prints figures that are inside another figure" << std::endl;
    std::cout << "help                                                     - Shows this list of commands" << std::endl;
    std::cout << "exit                                                     - Exists the program" << std::endl;
    return 0;
}

// check if the file is open
bool Manager::isOpen() const{
    return isFileOpen;
}

// return the current fileanem
std::string Manager::getFilename() const{
    return currentFilename;
}

// print all figures that are inside a given figure with type and parameters, for each figure inside the vector, we call the within method since we dont know the figure type inside the vector
void Manager::withinCommandCall(const Figure &fig){
    // Without indices
    // for(const Figure *f : figures){
    //     if(f->within(fig)) f->print(std::cout);
    // }
    if(!isFileOpen){
        std::cout << "No file is opened" << std::endl;
        return;
    }
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

// create a figure by deserializing the command line input with its type and parameters
bool Manager::createFigure(const std::string& command) {
    std::vector<std::string> token = splitTokens(command);
    if(token.empty()){
        std::cerr << "No command given" << std::endl;
        return false;
    }
    std::string type = token[0];
    try{
        Figure *fig = factory(type);
        fig->parseFromTokens(token);
        figures.push_back(fig);
        std::cout << "Successfully created " << type << "\n";
        return true;
    }
    catch(const std::exception &e){
        std::cerr << "Failed to create figure with type: " << type << "\n" << "Problem occured at /: " << e.what() << std::endl;
        return false;
    }    
}

// ersea figure by inputting an index of the figure
bool Manager::erase(const std::string &wantedId){
    try{
        std::size_t index = std::stoi(wantedId);
        if(index <= 0 || index > figures.size()){
            std::cerr << "Theres no figure with number " << index << "!\n";
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

// translate figure/s with inputing keywords vertical=, horizontal= and id= (id is optional)
bool Manager::translateFigures(const std::string& command) {
    try {
        double vertical = 0.0, horizontal = 0.0;
        int index = -1;

        // Parse vertical
        size_t vertPos = command.find("vertical=");
        if (vertPos == std::string::npos) {
            throw std::invalid_argument("Missing vertical/horizontal keywords");
        }
        vertPos += 9; // skip word "vertical" and "="
        size_t vertEnd = command.find(' ', vertPos);

        // convert the string to double, using stodCorrect to replace commas with dots (example in deserializeHelper.hpp)
        vertical = std::stod(stodCorrect(command.substr(vertPos, vertEnd - vertPos)));


        // the same for horizontal

        // Parse horizontal
        size_t horizPos = command.find("horizontal=");
        if (horizPos == std::string::npos) {
            throw std::invalid_argument("Missing vertical/horizontal keywords");
        }
        horizPos += 11; // length of "horizontal="
        size_t horizEnd = command.find(' ', horizPos);
        horizontal = std::stod(stodCorrect(command.substr(horizPos, horizEnd - horizPos)));

        // Parse optional index
        size_t indexPos = command.find("id=");
        if (indexPos != std::string::npos) {
            indexPos += 3; // length of "id="
            size_t indexEnd = command.find(' ', indexPos);
            index = std::stoi(command.substr(indexPos, indexEnd - indexPos)) - 1;
            if (index < 0 || index >= figures.size()) {
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


// print all figures using serialization function with cout
void Manager::printFigures(){
    if(figures.empty()){
        std::cout << "There are no figures to print." << std::endl;
        return;
    }
    for (std::size_t i = 0; i < figures.size(); ++i) {
        std::cout << i+1 << ". ";
        // print without colors : figures[i]->print(std::cout);
        figures[i]->printToTerminalWithColors(std::cout);
    }
}

std::vector<Figure*> &Manager::getFigures() {return figures;}
    
const std::vector<Figure*> &Manager::getFigures() const {return figures;}