#ifndef __Ellipse_HPP
#define __Ellipse_HPP
#include "Figure.hpp"

class Ellipse : public Figure{
protected:
    Point center;
    double radiusX, radiusY;
public:
    // Constructors
    Ellipse();
    Ellipse(const Point&, double, double, const Color&);

    // Overridden methods from Figure class, with logic specific for Ellipse
    // Methods explained in Figure.hpp

    void translate(double, double) override;
    void parseFromTokens(const std::vector<std::string> &) override;

    bool within(const Figure&) const override;
    bool containsPoint(const Point&) const override;

    std::string getType() const override;

    virtual Figure *clone() const override;

    void setColor(const Color&);

    void deserialize(std::istream &) override;

    void print(std::ostream &) const override;
    void printToTerminalWithColors(std::ostream &) const override;
};



#endif