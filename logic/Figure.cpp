#include "../includes/Figure.hpp"
#include "../includes/Rect.hpp"
#include "../includes/Circle.hpp"
#include "../includes/Ellipse.hpp"
#include "../includes/deserializeHelper.hpp"


Figure::Figure() : color(black) {}
Figure::Figure(Color _color) : color(_color) {}


// set color to figure
void Figure::setColor(const Color &_color){
    this->color = _color;
}

// create a new figure by type
Figure *factory(const std::string &type){
    if (type == "rect") return new Rect();
    else if (type == "circle") return new Circle();
    else if (type == "ellipse") return new Ellipse();
    throw std::invalid_argument("Unknown object type: " + type);
    return nullptr;
}


// deseriazlie a figure: call the factory for the type, then call the deserialize method for that type
// easiest way of doing that is with a stringstream that gets a string and presents it as input stream
Figure* Figure::deserializeAll(std::istream &in){
    std::string line;
    if(!std::getline(in, line)){
        throw std::runtime_error("Failed to read line from input stream");
    }
    std::istringstream lineStream(line);
    std::string type = getTypeOfFigure(lineStream);

    if(type.empty()){
        throw std::runtime_error("Failed to get type of figure from line: " + line);
    }

    Figure *fig = factory(type);
    if(!fig) throw std::runtime_error("Failed to create figure of type: " + type);

    fig->deserialize(lineStream);
    return fig;
}