#ifndef __Figure_HPP
#define __Figure_HPP
#include <iostream>
#include <vector>
#include "ColorHelper.hpp"

// DO NOT ADD THESE INCLUDES HERE
// #include "Ellipse.hpp"
// #include "Circle.hpp"
// #include "Rect.hpp"


struct Point{
    double x, y;
};

class Figure{
protected:
    Color color;
public:
    Figure();
    Figure(Color);

    virtual void print(std::ostream &) const = 0;
    
    // just deserialization
    virtual void parseFromTokens(const std::vector<std::string> &) = 0;
    
    virtual void translate(double, double) = 0;
    virtual Figure* clone() const = 0;
    virtual bool within(const Figure&) const = 0;
    virtual bool containsPoint(const Point&) const = 0;
    virtual std::string getType() const = 0;
    
    //static std::string colorToString(const Color&);
    void setColor(const Color&);
    
    virtual ~Figure() = default; 
};


// std::ostream& operator << (std::ostream&,const Point&);
// std::istream& operator >> (std::istream&,Point&);

std::ostream& operator<<(std::ostream& out,const std::vector<Figure*> v);

Figure *factory(const std::string &);

#endif