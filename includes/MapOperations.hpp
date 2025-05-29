#ifndef __MapOperations_HPP
#define __MapOperations_HPP
#include "ManagerPattern.hpp"
#include "CommandParseHelper.hpp"
#include <functional>
#include <map>
//#include <unordered_map> -> unordered map is faster than <map>

/*
* #include "FigureOperationPattern.hpp"
* #include "FileManagerPattern.hpp"
Both of these hpp files had std::vector<Figure*> figures and after running operations
open/close/save/saveas/exit & create/print/within/erase/translate
they both manipulated their own vector of figures, so the best idea was to unite the
2 hpp files into the existing one - Manager.hpp and to use single vector of figures
*/

//std::map<std::string, std::function<Command*(const std::string &, std::vector<Figure*> &)>> createCommandFactory(FileManager &filemanager, FigureManager &figuremanager);

std::map<std::string, std::function<Command*(const std::string &, std::vector<Figure*> &)>> createCommandFactory(Manager &manager);


#endif

