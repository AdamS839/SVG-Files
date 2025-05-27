#include "../includes/Ellipse.hpp"
#include "../includes/ColorHelper.hpp"
#include "../includes/deserializeHelper.hpp"
#include "../includes/CommandParseHelper.hpp"
#include <stdexcept>

// All methods work the same as in Circle.cpp and Rect.cpp, with the same logic

Ellipse::Ellipse() : center({0,0}), radiusX(0), radiusY(0), Figure(black) {}
Ellipse::Ellipse(const Point &p, double _radiusX, double _radiusY, const Color &_color) : Figure(_color), radiusX(_radiusX), radiusY(_radiusY), center(p) {}

// уравнение на елипса
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

void Ellipse::printToTerminalWithColors(std::ostream &os) const {
    os << "<ellipse cx=\"" <<valueColorAnsi(light_green) <<  center.x << defaultAnsiCol()
       << "\" cy=\"" << valueColorAnsi(light_green) << center.y << defaultAnsiCol()
       << "\" rx=\"" << valueColorAnsi(light_green) << radiusX << defaultAnsiCol()
       << "\" ry=\"" << valueColorAnsi(light_green) << radiusY << defaultAnsiCol()
       << "\" fill=\"" << colorToStringAnsi(color) << "\"/>\n";
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

void Ellipse::parseFromTokens(const std::vector<std::string> &tokens) {
    if (tokens.size() < 5 || tokens.size() > 6) {
        throw std::invalid_argument("Invalid parameters for ellipse");
    }
    center.x = std::stod(stodCorrect(tokens[1]));
    center.y = std::stod(stodCorrect(tokens[2]));
    radiusX = std::stod(stodCorrect(tokens[3]));
    radiusY = std::stod(stodCorrect(tokens[4]));

    color = (tokens.size() == 6) ? stringToColor(tokens[5]) : Color();
}

void Ellipse::deserialize(std::istream &line) {
    center.x = dataDoubleAttribute(line, "cx");
    center.y = dataDoubleAttribute(line, "cy");
    radiusX = dataDoubleAttribute(line, "rx");
    radiusY = dataDoubleAttribute(line, "ry");
    color = stringToColor(ColorAttribute(line, "fill"));
}