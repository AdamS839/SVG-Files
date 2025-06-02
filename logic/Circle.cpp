#include "../includes/Circle.hpp"
#include "../includes/ColorHelper.hpp"
#include "../includes/deserializeHelper.hpp"
#include "../includes/CommandParseHelper.hpp"
#include <stdexcept>

// All methods work the same as in Rect.cpp and Ellipse.cpp, with the same logic

Circle::Circle() : center({0,0}), radius(0), Figure(black) {}
Circle::Circle(const Point &p, double _radius, const Color &_color) : Figure(_color), radius(_radius), center(p) {}

// equation of a circle
// (x0 - center.x)^2 + (y0 - center.y)^2 <= radius^2
bool Circle::containsPoint(const Point& p) const {
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

// check if figure contains circle points
bool Circle::within(const Figure &f) const{
    Point topLeft = {center.x - radius, center.y - radius};
    Point topRight = {center.x + radius, center.y - radius};
    Point bottomLeft = {center.x - radius, center.y + radius};
    Point bottomRight = {center.x + radius, center.y + radius};

    return f.containsPoint(topLeft) &&
           f.containsPoint(topRight) &&
           f.containsPoint(bottomLeft) &&
           f.containsPoint(bottomRight);
}

// create copy of the circle
Figure* Circle::clone() const{
    return new Circle(*this);
}


// print the circle in SVG format in the terminal or file
void Circle::print(std::ostream &os) const {
    os << "<circle cx=\"" << center.x
       << "\" cy=\"" << center.y
       << "\" r=\"" << radius
       << "\" fill=\"" << colorToString(color) << "\"/>\n";
}

// print the circle in svg format in terminal with colors on parameters and fill color (cosmetic method of printing)
void Circle::printToTerminalWithColors(std::ostream &os) const {
    os << "<circle cx=\"" << valueColorAnsi(light_green) << center.x << defaultAnsiCol()
       << "\" cy=\"" << valueColorAnsi(light_green) << center.y << defaultAnsiCol()
       << "\" r=\"" << valueColorAnsi(light_green) << radius << defaultAnsiCol()
       << "\" fill=\"" << colorToStringAnsi(color) << "\"/>\n";
}

// translate with X and Y values
void Circle::translate(double horizontal, double vertical) {
    center.x += horizontal;
    center.y += vertical;
}

// set color (dont need) - will remove
void Circle::setColor(const Color &color){
    this->color = color;
}

// get the type 'circle' as a string
std::string Circle::getType() const{
    return "circle";
}

// parse circle parameters from a vector of tokens (using another function (stodCorrect) to replace commas with dots) to be able to use std::stod - deserilializeHelper.hpp)
void Circle::parseFromTokens(const std::vector<std::string> &tokens) {
    if (tokens.size() < 4 || tokens.size() > 5) {
        throw std::invalid_argument("Invalid parameters for circle");
    }
    center.x = std::stod(stodCorrect(tokens[1]));
    center.y = std::stod(stodCorrect(tokens[2]));
    radius = std::stod(stodCorrect(tokens[3]));
    
    color = (tokens.size() == 5) ? stringToColor(tokens[4]) : Color();
}


// deserialize circle parameters from a string line (using helping function to get the double value or the color as a string - deserilializeHelper.hpp)
void Circle::deserialize(std::istream &line) {
    center.x = dataDoubleAttribute(line, "cx");
    center.y = dataDoubleAttribute(line, "cy");
    radius = dataDoubleAttribute(line, "r");
    color = stringToColor(ColorAttribute(line, "fill"));
}