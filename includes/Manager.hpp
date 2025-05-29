#ifndef __Manager_HPP
#define __Manager_HPP
#include <vector>
#include <string>
#include "Figure.hpp"

class Manager{
std::vector<Figure*> figures;
std::string currentFilename;
bool isFileOpen;
public:
    Manager();
    ~Manager();

    /*
    Working with file
    */

    // Method for opening/creating a file(new file)
    bool open(const std::string &path);

    // Closing the file with printing message
    void close(bool outputMessage);

    // Saving all changes to the same file
    bool save() const;

    // Saving all changes to a new file (with different name)
    bool saveAs(const std::string &path);

    // print all operations and a little description about them
    int help() const;

    // checker if file is opened
    bool isOpen() const;

    // return the current fileanem
    std::string getFilename() const;

    /*
    Creating, printing and manipulating figures 
    */

    // Function for calling within function for each figure
    void withinCommandCall(const Figure &);

    // create a figure from a string
    bool createFigure(const std::string &);

    // erase a figure by index
    bool erase(const std::string &);

    // translate figures by X and Y coordinates
    bool translateFigures(const std::string &);

    // print all figures
    void printFigures();

    std::vector<Figure*> &getFigures();
    
    const std::vector<Figure*> &getFigures() const;
};

#endif