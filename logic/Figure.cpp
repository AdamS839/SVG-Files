#include "../includes/Figure.hpp"
#include "../includes/Rect.hpp"
#include "../includes/Circle.hpp"
#include "../includes/Ellipse.hpp"


Figure::Figure() : color(black) {}
Figure::Figure(Color _color) : color(_color) {}

// do i need it?
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

Figure *factory(const std::string &type){
    if (type == "rect") return new Rect();
    else if (type == "circle") return new Circle();
    else if (type == "ellipse") return new Ellipse();
    throw std::invalid_argument("Unknown object type: " + type);
    return nullptr;
}
