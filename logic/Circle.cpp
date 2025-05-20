#include "../includes/Circle.hpp"

Circle::Circle() : center({0,0}), radius(0), Figure(black) {}
Circle::Circle(const Point &p, double _radius, const Color &_color) : Figure(_color), radius(_radius), center(p) {}

// circle uravn.
bool Circle::containsPoint(const Point& p) const {
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

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

Figure* Circle::clone() const{
    return new Circle(*this);
}

void Circle::print(std::ostream &os) const {
    os << "<circle cx=\"" << center.x
       << "\" cy=\"" << center.y
       << "\" r=\"" << radius
       << "\" fill=\"" << colorToString(color) << "\"/>\n";
}

void Circle::translate(double horizontal, double vertical) {
    center.x += horizontal;
    center.y += vertical;
}

void Circle::setColor(const Color &color){
    this->color = color;
}

std::string Circle::getType() const{
    return "circle";
}