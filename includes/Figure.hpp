#ifndef __Figure_HPP
#define __Figure_HPP
#include <iostream>
#include <vector>

struct Point{
    double x, y;
};

struct Color{
    unsigned int r,g,b;

bool operator==(const Color &other) const{
    return r == other.r && g == other.g && b == other.b;
}
};

const Color red = {255,0,0},
            green = {0,255,0},
            blue = {0,0,255},
            yellow = {255,255,0}, 
            white = {255,255,255},
            purple = {128,0,128},
            black = {0,0,0};

class Figure{
protected:
    Color color;
public:
    Figure();
    Figure(Color);

    virtual void print(std::ostream &) const = 0;
    virtual void translate(double, double) = 0;
    virtual Figure* clone() const = 0;
    virtual bool within(const Figure&) const = 0;
    virtual bool containsPoint(const Point&) const = 0;
    virtual std::string getType() const = 0;
    
    static std::string colorToString(const Color&);
    void setColor(const Color&);
    
    virtual ~Figure() = default; 
};


// std::ostream& operator << (std::ostream&,const Point&);
// std::istream& operator >> (std::istream&,Point&);

std::ostream& operator<<(std::ostream& out,const std::vector<Figure*> v);


#endif