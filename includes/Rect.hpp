#ifndef __Rect_HPP
#define __Rect_HPP
#include "Figure.hpp"

class Rect : public Figure{
protected:
Point start_point;
double width, height;
public:
    Rect();
    Rect(const Point&, double, double,const Color&);

    void print(std::ostream &) const override;
    void translate(double, double) override;
    
    void parseFromTokens(const std::vector<std::string> &) override;
    
    bool within(const Figure&) const override;
    bool containsPoint(const Point&) const override;

    std::string getType() const override;

    Figure *clone() const override;
};


#endif