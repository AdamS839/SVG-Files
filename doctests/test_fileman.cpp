#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../includes/Manager.hpp"
#include <fstream>

//compile with: g++ doctests/test_fileman.cpp ./login/*.cpp

TEST_CASE("FileManager open, close, save and saveAs") {
    Manager m;
    
    // remove existing files if created before this test
    std::remove("newfile1.svg"); 
    std::remove("newfile2.svg");
    std::remove("tests/file.svg");

    // Opening a non-existent file creates it
    CHECK(m.open("newfile1.svg") == true);
    CHECK(m.isOpen() == true);
    CHECK(m.getFilename() == "newfile1.svg");

    // Opening another file without closing returns false
    CHECK(m.open("another.svg") == false);

    // Saving the current file should succeed
    CHECK(m.save() == true);

    // Saving as same filename fails
    CHECK(m.saveAs("newfile1.svg") == false);

    // Saving as a new filename should succeed
    CHECK(m.saveAs("newfile2.svg") == true);
    CHECK(m.getFilename() == "newfile2.svg");

    // Closing the file
    m.close(false);
    CHECK(m.isOpen() == false);
    CHECK(m.getFilename() == "");

    // Closing again should not crash or output error
    m.close(false);

    //check criteria
    CHECK(m.open("") == false);
    CHECK(m.open("file with spaces.svg") == false);
    CHECK(m.open("file/withslash.svg") == false);
    CHECK(m.open("tests/file.svg"));
    CHECK(m.open("file..svg") == false);
    CHECK(m.open("file.svgx") == false);

    //remove the created files
    std::remove("newfile1.svg");
    std::remove("newfile2.svg");
    std::remove("tests/file.svg");
}