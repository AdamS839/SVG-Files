#ifndef __Circle_HPP
#define __Circle_HPP
#include "Figure.hpp"

class Circle : public Figure{
protected:
Point center;
double radius;
public:
    // Constructors
    Circle();
    Circle(const Point&, double, const Color&);

    // Overridden methods from Figure class, with logic specific for Circle
    // Methods explained in Figure.hpp

    void print(std::ostream &) const override;

    void printToTerminalWithColors(std::ostream &) const override;
    
    void parseFromTokens(const std::vector<std::string> &) override;

    void translate(double, double) override;

    bool within(const Figure&) const override;
    bool containsPoint(const Point&) const override;

    std::string getType() const override;

    virtual Figure *clone() const override;

    void setColor(const Color&);

    void deserialize(std::istream &) override;
};


#endif