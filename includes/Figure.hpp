#ifndef __Figure_HPP
#define __Figure_HPP
#include <iostream>
#include <vector>
#include <sstream>
#include "ColorHelper.hpp"

// DO NOT ADD THESE INCLUDES HERE
// #include "Ellipse.hpp"
// #include "Circle.hpp"
// #include "Rect.hpp"

// saving x and y coordinates to imitate 2d space
struct Point{
    double x, y;
};

class Figure{
protected:
    Color color;
public:
    //Constructors
    Figure();
    Figure(Color);

    // All methods in virtual are written in Rect.hpp/.cpp, Circle.hpp/.cpp & Ellipse.hpp/.cpp with logic for their figure type 

    // sets parameters from a vector of tokens(a string) for their own type of figure
    virtual void parseFromTokens(const std::vector<std::string> &) = 0;
    
    // translate a figure by horizontal(X) and vertical(Y) value
    virtual void translate(double, double) = 0;

    // creating a copy of the figure
    virtual Figure* clone() const = 0;

    // check if the figure is within another figure
    virtual bool within(const Figure&) const = 0;

    // check if the figure contains a point
    virtual bool containsPoint(const Point&) const = 0;

    //get the type of the figure as a string
    virtual std::string getType() const = 0;
    
    //set the color (dont need)
    void setColor(const Color&);
    
    // default destructor
    virtual ~Figure() = default; 

    // deserialize a figure from a string
    virtual void deserialize(std::istream &) = 0;

    // deserialize all figures from a string from the file
    static Figure* deserializeAll(std::istream &);

    // print is serialization function - for printFigures we call std::cout, and for saving to the file we call std::ofstream
    virtual void print(std::ostream &) const = 0;
    
    // purely cosmetic method for printing to the terminal with colors (example: fill="red", the word red will appear red)
    virtual void printToTerminalWithColors(std::ostream &) const = 0;
};


// std::ostream& operator << (std::ostream&,const Point&);
// std::istream& operator >> (std::istream&,Point&);

//std::ostream& operator<<(std::ostream& out,const std::vector<Figure*> v);

// create a figure by type
Figure *factory(const std::string &);

#endif