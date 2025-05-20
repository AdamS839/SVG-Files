#ifndef __Ellipse_HPP
#define __Ellipse_HPP
#include "Figure.hpp"

class Ellipse : public Figure{
protected:
    Point center;
    double radiusX, radiusY;
public:
    Ellipse();
    Ellipse(const Point&, double, double, const Color&);

    void print(std::ostream &) const override;
    void translate(double, double) override;

    bool within(const Figure&) const override;
    bool containsPoint(const Point&) const override;

    std::string getType() const override;

    virtual Figure *clone() const override;

    void setColor(const Color&);
};



#endif