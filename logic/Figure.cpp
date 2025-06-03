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

    Figure *fig = nullptr;
    try{
        fig = factory(type);
    }
    catch(const std::exception& e){
        std::cerr << "Factory error occured at: " << e.what() << '\n';
    }

    try{        
        fig->deserialize(lineStream);
    }
    catch(const std::exception& e){
        std::cerr << "Deserialize error occured at: " << e.what() << '\n';
        delete fig;
        return nullptr;
    }
    return fig;
}