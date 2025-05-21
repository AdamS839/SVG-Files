#include "../includes/Rect.hpp"
#include "../includes/ColorHelper.hpp"
#include <stdexcept>

Rect::Rect() : start_point({0,0}), width(0), height(0), Figure(black) {}
Rect::Rect(const Point &p, double _width, double _height,const Color &_color) : Figure(_color), width(_width), height(_height), start_point(p) {}

bool Rect::containsPoint(const Point& p) const {
    return p.x >= start_point.x &&
           p.y >= start_point.y &&
           p.x <= start_point.x + width &&
           p.y <= start_point.y + height;
}

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

Figure* Rect::clone() const{
    return new Rect(*this);
}

void Rect::print(std::ostream &os) const{
    os << "<rect x=\"" << start_point.x
       << "\" y=\"" << start_point.y
       << "\" width=\"" << width
       << "\" height=\"" << height
       << "\" fill=\"" << colorToString(color) << "\"/>\n";
}

void Rect::translate(double horizontal, double vertical) {
    start_point.x += horizontal;
    start_point.y += vertical;
}

std::string Rect::getType() const{
    return "rect";
}

void Rect::parseFromTokens(const std::vector<std::string> &tokens) {

}
