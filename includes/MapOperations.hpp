#ifndef __MapOperations_HPP
#define __MapOperations_HPP
#include "ManagerPattern.hpp"
#include "CommandParseHelper.hpp"
#include <functional>
#include <map>
//#include <unordered_map> -> unordered map is faster than <map>

std::map<std::string, std::function<Command*(const std::string &, std::vector<Figure*> &)>> createCommandFactory(Manager &manager);


#endif

