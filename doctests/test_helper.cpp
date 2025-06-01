#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../includes/Figure.hpp"
#include "../includes/Rect.hpp"
#include "../includes/Circle.hpp"
#include "../includes/Ellipse.hpp"
#include <sstream> // for istringstream

//compile with: g++ doctests/test_helper.cpp ./login/*.cpp


// Use istringstream to wrap the string as istream so we can use it with deserializeAll
TEST_CASE("Deserialize Rect from svg string") {
    std::string rectSvg = "(<rect x=\"10\" y=\"20\" width=\"30\" height=\"40\" fill=\"red\"/>)";
    std::istringstream ss(rectSvg);
    Figure* fig = Figure::deserializeAll(ss);
    CHECK(fig != nullptr);
    // check if the figure is of type Rect
    CHECK(dynamic_cast<Rect*>(fig) != nullptr);
    delete fig;
}

// same test but for circle
TEST_CASE("Deserialize Circle from svg string") {
    std::string circleSvg = "(<circle cx=\"50\" cy=\"60\" r=\"25\" fill=\"green\"/>)";
    std::istringstream ss(circleSvg);
    Figure* fig = Figure::deserializeAll(ss);
    CHECK(fig != nullptr);
    CHECK(dynamic_cast<Circle*>(fig) != nullptr);
    delete fig;
}

// same test but for ellipse
TEST_CASE("Deserialize Ellipse from svg string") {
    std::string ellipseSvg = "(<ellipse cx=\"70\" cy=\"80\" rx=\"40\" ry=\"20\" fill=\"blue\"/>)";
    std::istringstream ss(ellipseSvg);
    Figure* fig = Figure::deserializeAll(ss);
    CHECK(fig != nullptr);
    CHECK(dynamic_cast<Ellipse*>(fig) != nullptr);
    delete fig;
}