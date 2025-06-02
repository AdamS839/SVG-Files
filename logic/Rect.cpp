#include "../includes/Rect.hpp"
#include "../includes/ColorHelper.hpp"
#include "../includes/deserializeHelper.hpp"
#include "../includes/CommandParseHelper.hpp"
#include <stdexcept>

// All methods work the same as in Circle.cpp and Ellipse.cpp, with the same logic

Rect::Rect() : start_point({0,0}), width(0), height(0), Figure(black) {}
Rect::Rect(const Point &p, double _width, double _height,const Color &_color) : Figure(_color), width(_width), height(_height), start_point(p) {}

// point is within the rectangle x and y coordinates
bool Rect::containsPoint(const Point& p) const {
    return p.x >= start_point.x &&
           p.y >= start_point.y &&
           p.x <= start_point.x + width &&
           p.y <= start_point.y + height;
}

// check if figure contains rect points
bool Rect::within(const Figure &f) const{
    Point topLeft = start_point;
    Point topRight = {start_point.x + width, start_point.y};
    Point bottomLeft = {start_point.x, start_point.y + height};
    Point bottomRight = {start_point.x + width, start_point.y + height};

    return f.containsPoint(topLeft) &&
           f.containsPoint(topRight) &&
           f.containsPoint(bottomLeft) &&
           f.containsPoint(bottomRight);
}

// create a copy of rect
Figure* Rect::clone() const{
    return new Rect(*this);
}

// print rect in svg format
void Rect::print(std::ostream &os) const{
    os << "<rect x=\"" << start_point.x
       << "\" y=\"" << start_point.y
       << "\" width=\"" << width
       << "\" height=\"" << height
       << "\" fill=\"" << colorToString(color) << "\"/>\n";
}

// print rect in svg format with colors
void Rect::printToTerminalWithColors(std::ostream &os) const {
    os << "<rect x=\"" << valueColorAnsi(light_green) << start_point.x << defaultAnsiCol()
       << "\" y=\"" << valueColorAnsi(light_green) << start_point.y << defaultAnsiCol()
       << "\" width=\"" << valueColorAnsi(light_green) << width << defaultAnsiCol()
       << "\" height=\"" << valueColorAnsi(light_green) << height << defaultAnsiCol()
       << "\" fill=\"" << colorToStringAnsi(color) << "\"/>\n";
}

// translate rect with x and y value
void Rect::translate(double horizontal, double vertical) {
    start_point.x += horizontal;
    start_point.y += vertical;
}

// get the type as string
std::string Rect::getType() const{
    return "rect";
}

// parse rectangle params from tokens
void Rect::parseFromTokens(const std::vector<std::string> &tokens) {
    if (tokens.size() < 5 || tokens.size() > 6) {
        throw std::invalid_argument("Invalid parameters for rect");
    }
    start_point.x = std::stod(stodCorrect(tokens[1]));
    start_point.y = std::stod(stodCorrect(tokens[2]));
    width = std::stod(stodCorrect(tokens[3]));
    height = std::stod(stodCorrect(tokens[4]));
    
    // Color can be skipped and the default color will be black - check for color
    color = (tokens.size() == 6) ? stringToColor(tokens[5]) : Color();
}

// deserialize a rectangle from a stream
void Rect::deserialize(std::istream &line) {
    start_point.x = dataDoubleAttribute(line, "x");
    start_point.y = dataDoubleAttribute(line, "y");
    width = dataDoubleAttribute(line, "width");
    height = dataDoubleAttribute(line, "height");
    color = stringToColor(ColorAttribute(line, "fill"));
}