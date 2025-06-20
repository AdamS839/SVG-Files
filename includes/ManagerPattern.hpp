#ifndef __ManagerPattern_HPP
#define __ManagerPattern_HPP

#include "Manager.hpp"
#include "BasePatternCommand.hpp"
#include "CommandParseHelper.hpp"
#include <vector>
#include <string>

// Command Pattern for each method in Manager.hpp
// use the same manager for using the same vector, string for arguments
class ManagerCommand : public Command {
protected:
Manager &manager;
std::string args;
public:
    virtual ~ManagerCommand() = default;
    ManagerCommand(Manager &, const std::string &);
    virtual void execute() = 0;
};

class CreateCommand : public ManagerCommand {
public:
    CreateCommand(Manager &mgr, const std::string &);
    void execute() override;
};

class TranslateCommand : public ManagerCommand {
public:
    TranslateCommand(Manager &, const std::string &);
    void execute() override;
};

class EraseCommand : public ManagerCommand {
public:
    EraseCommand(Manager &, const std::string &);
    void execute() override;
};

// within needs a figure to see if it contains the other figures
class WithinCommand : public ManagerCommand {
Figure *fig;
public:
    // added destructor to delete the figure we created
    virtual ~WithinCommand();
    WithinCommand(Manager &, const std::string &);
    void execute() override;
};

class PrintCommand : public ManagerCommand {
public:
    PrintCommand(Manager &);
    void execute() override;
};

class OpenCommand : public ManagerCommand {
public:
    OpenCommand(Manager &, const std::string &);
    void execute() override;
};

class SaveCommand : public ManagerCommand {
public:
    SaveCommand(Manager &, const std::string &);
    void execute() override;
};

class SaveAsCommand : public ManagerCommand {
public:
    SaveAsCommand(Manager &, const std::string &);
    void execute() override;
};

class CloseCommand : public ManagerCommand {
public:
    CloseCommand(Manager &, const std::string &);
    void execute() override;
};

class ExitCommand : public ManagerCommand {
public:
    ExitCommand(Manager &, const std::string &);
    void execute() override;
};

class HelpCommand : public ManagerCommand {
public:
    HelpCommand(Manager &, const std::string &);
    void execute() override;
};

#endif
