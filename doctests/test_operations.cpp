#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../includes/Rect.hpp"
#include "../includes/Circle.hpp"
#include "../includes/Ellipse.hpp"
#include "../includes/Manager.hpp"

//compile with: g++ doctests/test_operations.cpp ./login/*.cpp

TEST_CASE("test operations - manipulating operations") {
    Manager manager;

    CHECK(manager.createFigure("rect 0 0 10 10 red") == true);
    CHECK(manager.createFigure("circle 50 50 30 blue") == true);
    CHECK(manager.createFigure("ellipse 100 100 40 20 green") == true);

    CHECK(manager.getFigures().size() == 3);

    //<sstream>
    SUBCASE("Print shapes") {
        std::ostringstream out;
        for (Figure* fig : manager.getFigures()) {
            fig->print(out);
        }
        std::string result = out.str();
        CHECK(result.find("<rect") != std::string::npos);
        CHECK(result.find("<circle") != std::string::npos);
        CHECK(result.find("<ellipse") != std::string::npos);
    }

    SUBCASE("Translate shapes") {
        for (Figure* fig : manager.getFigures()){
            fig->translate(5, 10);
        }
        std::ostringstream out;
        manager.getFigures()[0]->print(out);
        std::string result = out.str();
        // check for correct translation
        CHECK(result.find("x=\"5\"") != std::string::npos);
        CHECK(result.find("y=\"10\"") != std::string::npos);
    }

    SUBCASE("Within region") {
        Rect region;
        region.parseFromTokens({"rect", "0", "0", "200", "200", "white"});

        std::vector<Figure*> withinFigures;
        for (Figure* fig : manager.getFigures()){   
            if (fig->within(region)){
                withinFigures.push_back(fig);
            }
        }
        CHECK(withinFigures.size() == 3);
    }

    SUBCASE("Erase a figure") {
        delete manager.getFigures()[1]; // Erase circle
        manager.getFigures().erase(manager.getFigures().begin() + 1); // remove from vector
        CHECK(manager.getFigures().size() == 2); // check
        std::ostringstream out; // print the remaining
        for (Figure* fig : manager.getFigures()){
            fig->print(out);
        }
        std::string result = out.str();
        CHECK(result.find("<circle") == std::string::npos); // should not be here
    }

    SUBCASE("Clone a figure") {
        Figure* original = manager.getFigures()[0]; // get rectangle
        Figure* copy = nullptr;
        if(original != nullptr){
            copy = original->clone();
        }
        CHECK(copy != nullptr);
        CHECK(typeid(*copy) == typeid(*original)); // check for same type

        //print out both figures to compare
        std::ostringstream origOut, copyOut;
        original->print(origOut);
        copy->print(copyOut);
        CHECK(origOut.str() == copyOut.str()); // same info

        delete copy; //delete the copy
    }


    // set color of a figure
    SUBCASE("Set color of a figure") {
        Figure* fig = manager.getFigures()[0]; // get rectangle
        fig->setColor(stringToColor("black"));

        std::ostringstream out;
        fig->print(out);
        std::string result = out.str();

        CHECK(result.find("fill=\"black\"") != std::string::npos);
    }


    // Clean up memory
    for (Figure* fig : manager.getFigures()){
        delete fig;
    }
}