#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../includes/Manager.hpp"
#include "../includes/MapOperations.hpp"
#include <functional>

//compile with: g++ test/test_map.cpp ./login/*.cpp

TEST_CASE("createCommandFactory returns correct commands") {
    Manager manager;
    std::vector<Figure*> figures;
    //std::map<std::string, std::function<Command*(const std::string &, std::vector<Figure*> &)>> factory = createCommandFactory(manager);
    auto factory = createCommandFactory(manager);

    // check for command existence
    CHECK(factory.find("create") != factory.end());
    CHECK(factory.find("translate") != factory.end());
    CHECK(factory.find("erase") != factory.end());
    CHECK(factory.find("within") != factory.end());
    CHECK(factory.find("print") != factory.end());
    CHECK(factory.find("open") != factory.end());
    CHECK(factory.find("save") != factory.end());
    CHECK(factory.find("saveas") != factory.end());
    CHECK(factory.find("close") != factory.end());
    CHECK(factory.find("exit") != factory.end());
    CHECK(factory.find("help") != factory.end());

    // check if command worked
    CHECK(factory["create"]("args", figures) != nullptr);
    CHECK(factory["translate"]("args", figures) != nullptr);
    CHECK(factory["erase"]("args", figures) != nullptr);
    CHECK(factory["within"]("args", figures) != nullptr);
    CHECK(factory["print"]("", figures) != nullptr);
    CHECK(factory["open"]("filename.svg", figures) != nullptr);
    CHECK(factory["saveas"]("filename2.svg", figures) != nullptr);
    
    // these dont need args
    CHECK(factory["save"]("unexpected", figures) == nullptr);
    CHECK(factory["close"]("unexpected", figures) == nullptr);
    CHECK(factory["exit"]("unexpected", figures) == nullptr);
    CHECK(factory["help"]("unexpected", figures) == nullptr);
    CHECK(factory["print"]("unexpected", figures) == nullptr);
}
