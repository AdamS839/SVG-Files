#include "../includes/Ellipse.hpp"

Ellipse::Ellipse() : center({0,0}), radiusX(0), radiusY(0), Figure(black) {}
Ellipse::Ellipse(const Point &p, double _radiusX, double _radiusY, const Color &_color) : Figure(_color), radiusX(_radiusX), radiusY(_radiusY), center(p) {}

// ellipse uravn.
bool Ellipse::containsPoint(const Point& p) const {
    double dx = (p.x - center.x) / radiusX;
    double dy = (p.y - center.y) / radiusY;
    return (dx * dx + dy * dy) <= 1;
}

bool Ellipse::within(const Figure &f) const{
    Point topLeft = {center.x - radiusX, center.y - radiusY};
    Point topRight = {center.x + radiusX, center.y - radiusY};
    Point bottomLeft = {center.x - radiusX, center.y + radiusY};
    Point bottomRight = {center.x + radiusX, center.y + radiusY};

    return f.containsPoint(topLeft) &&
           f.containsPoint(topRight) &&
           f.containsPoint(bottomLeft) &&
           f.containsPoint(bottomRight);
}

Figure* Ellipse::clone() const{
    return new Ellipse(*this);
}

void Ellipse::print(std::ostream &os) const {
    os << "<ellipse cx=\"" << center.x
       << "\" cy=\"" << center.y
       << "\" rx=\"" << radiusX
       << "\" ry=\"" << radiusY
       << "\" fill=\"" << colorToString(color) << "\"/>\n";
}

void Ellipse::translate(double horizontal, double vertical) {
    center.x += horizontal;
    center.y += vertical;
}

void Ellipse::setColor(const Color &color){
    this->color = color;
}

std::string Ellipse::getType() const{
    return "ellipse";
}