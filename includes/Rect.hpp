#ifndef __Rect_HPP
#define __Rect_HPP
#include "Figure.hpp"

class Rect : public Figure{
protected:
Point start_point;
double width, height;
public:
    //Constructors
    Rect();
    Rect(const Point&, double, double,const Color&);

    // Overridden methods from Figure class, with logic specific for Rectangle

    void print(std::ostream &) const override;
    void printToTerminalWithColors(std::ostream &) const override;

    void translate(double, double) override;
    
    void parseFromTokens(const std::vector<std::string> &) override;
    
    bool within(const Figure&) const override;
    bool containsPoint(const Point&) const override;

    std::string getType() const override;

    virtual Figure *clone() const override;

    void deserialize(std::istream &) override;
};


#endif