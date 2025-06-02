#include "../includes/MapOperations.hpp"

std::map<std::string, std::function<Command*(const std::string &, std::vector<Figure*> &)>> createCommandFactory(Manager &manager) {
    return {
        {"create", [&manager](const std::string &args, std::vector<Figure*> &figures) {
            return new CreateCommand(manager, args);
        }},
        {"translate", [&manager](const std::string &args, std::vector<Figure*> &figures) {
            return new TranslateCommand(manager, args);
        }},
        {"erase", [&manager](const std::string &args, std::vector<Figure*> &figures) {
            return new EraseCommand(manager, args);
        }},
        {"within", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            return new WithinCommand(manager, args);
        }},
        {"print", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            if(!args.empty()){
                std::cerr << "Do not input anything other than the keyword 'print'" << std::endl;
                return nullptr;
            }
            else return new PrintCommand(manager);

        }},
        {"open", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            return new OpenCommand(manager, args);
        }},
        {"save", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            if(!args.empty()){
                std::cerr << "Save command cant take multiple arguments" << std::endl;
                return nullptr;
            }
            return new SaveCommand(manager, args);
        }},
        {"saveas", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            return new SaveAsCommand(manager, args);
        }},
        {"close", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            if(!args.empty()){
                std::cerr << "Do not input other symbols after command 'close'" << std::endl;
                return nullptr;
            }   
            return new CloseCommand(manager, args);
        }},
        {"exit", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            if(!args.empty()){
                std::cerr << "Do not input anything other than keyword 'exit' to exit the program" << std::endl;
                return nullptr;
            }
            return new ExitCommand(manager, args);
        }},
        {"help", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            if(!args.empty()){
                std::cerr << "Do not input other symbols after command 'help'" << std::endl;
                return nullptr;
            }
            return new HelpCommand(manager, args);
        }}
    };
}