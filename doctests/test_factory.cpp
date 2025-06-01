#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../includes/Figure.hpp"
#include "../includes/Rect.hpp"
#include "../includes/Circle.hpp"
#include "../includes/Ellipse.hpp"

//compile with: g++ test/test_factory.cpp ./login/*.cpp

// test factory for creating figures
TEST_CASE("Figure factory creates correct figures") {
    CHECK_NOTHROW({
        Figure* rect = factory("rect");
        delete rect;
    });
    CHECK_NOTHROW({
        Figure* circ = factory("circle");
        delete circ;
    });
    CHECK_NOTHROW({
        Figure* ell = factory("ellipse");
        delete ell;
    });
    CHECK_THROWS_AS(factory("unknown"), std::invalid_argument);
}