#include "../includes/ManagerPattern.hpp"

// Base ManagerCommand constructor
ManagerCommand::ManagerCommand(Manager &manager, const std::string &args) : manager(manager), args(args) {}

// CreateCommand
CreateCommand::CreateCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args) {}

void CreateCommand::execute() {
    manager.createFigure(args);
}

// TranslateCommand
TranslateCommand::TranslateCommand(Manager &manager, const std::string &args): ManagerCommand(manager, args) {}

void TranslateCommand::execute() {
    manager.translateFigures(args);
}

// EraseCommand
EraseCommand::EraseCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args) {}

void EraseCommand::execute() {
    manager.erase(args);
}

// WithinCommand
WithinCommand::WithinCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args), fig(nullptr) {
    std::vector<std::string> token = splitTokens(args);
    if(!token.empty()){
        try{
            fig = factory(token[0]);
            if(fig){
                fig->parseFromTokens(token);
            }
        }
        catch(const std::exception& e){
            std::cerr << "Command 'within' cant be executed propertly, problem occured at: " << e.what() << '\n';
        }
    }
    else{
        std::cerr << "Missing figure type in 'within'" << std::endl;
    }
}

void WithinCommand::execute() {
    if(fig){
    manager.withinCommandCall(*fig);
    }
    else std::cerr << "Invalid figure input." << std::endl;
}

WithinCommand::~WithinCommand() {
    delete fig;
}

// PrintCommand
PrintCommand::PrintCommand(Manager &manager) : ManagerCommand(manager, {}) {}

void PrintCommand::execute() {
    manager.printFigures();
}

// OpenCommand
OpenCommand::OpenCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args) {}

void OpenCommand::execute() {
    if(args.empty()) {
        std::cerr << "Missing pathname to open/crate" << std::endl;
    }
    else manager.open(args);
}

// SaveCommand
SaveCommand::SaveCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args) {}

void SaveCommand::execute() {
    if(!args.empty()){
        std::cerr << "Save command cant take arguments" << std::endl;
    }
    else{
        manager.save();
    }
}

// SaveAsCommand
SaveAsCommand::SaveAsCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args) {}

void SaveAsCommand::execute() {
    if(!manager.isOpen()){
        std::cerr << "No file is opened at the moment. Use 'open' first and then 'saveas' + <pathname>" << std::endl;
    }
    else if(args.empty()) {
        std::cerr << "Missing pathname to open/crate" << std::endl;
    }
    else manager.saveAs(args);
}

// CloseCommand
CloseCommand::CloseCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args) {}

void CloseCommand::execute() {
    if(!args.empty()){
        std::cerr << "Do not input other symbols after command 'close'" << std::endl;
    }
    else manager.close(false);
}

// ExitCommand
ExitCommand::ExitCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args) {}

void ExitCommand::execute() {
    if(!args.empty()){
        std::cerr << "Do not input anything other than keyword 'exit' to exit the program" << std::endl;
        return;
    }
    std::cout << "Exiting the program..." << std::endl;
    manager.close(true);
    std::exit(0);
}

// HelpCommand
HelpCommand::HelpCommand(Manager &manager, const std::string &args) : ManagerCommand(manager, args) {}

void HelpCommand::execute() {
    if(!args.empty()){
        std::cerr << "Do not input other symbols after command 'help'" << std::endl;
    }
    else{
        manager.help();
    }
}
