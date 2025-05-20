#include "../includes/Figure.hpp"
#include "../includes/Rect.hpp"
#include "../includes/Circle.hpp"
#include "../includes/Ellipse.hpp"


Figure::Figure() : color(black) {}
Figure::Figure(Color _color) : color(_color) {}

std::ostream& operator << (std::ostream &out,const Point &p){
    out << p.x << " " << p.y;
    return out;
}

std::istream& operator >> (std::istream &in,Point &p){
    in >> p.x >> p.y;
    return in;
}

Figure *factory(std::string type){
    if (type == "rect") return new Rect();
    else if (type == "circle") return new Circle();
    else if (type == "ellipse")return new Ellipse();
    throw std::invalid_argument("Unknown object type: " + type);
    return nullptr;
}

std::string Figure::colorToString(const Color &col){
    if(col == red) return "red";
    if(col == green) return "green";
    if(col == blue) return "blue";
    if(col == yellow) return "yellow";
    if(col == purple) return "purple";
    if(col == black) return "black";
    if(col == white) return "white";

    return "rgb(" + std::to_string(col.r) + "," + std::to_string(col.g) + "," + std::to_string(col.b) + ")";
}

std::ostream& operator<<(std::ostream& out,const std::vector<Figure*> v){
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        out << i + 1 << ". ";
        v[i]->print(out);
    }
    return out;
}

void Figure::setColor(const Color &_color){
    this->color = _color;
}

