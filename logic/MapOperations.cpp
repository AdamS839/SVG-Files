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
            return new SaveCommand(manager, args);
        }},
        {"saveas", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            return new SaveAsCommand(manager, args);
        }},
        {"close", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            return new CloseCommand(manager, args);
        }},
        {"exit", [&manager](const std::string &args, std::vector<Figure*> &figures) -> Command* {
            return new ExitCommand(manager, args);
        }},
        {"help", [&manager](const std::string &args, std::vector<Figure*> &figures) {
            return new HelpCommand(manager, args);
        }}
    };
}

// std::map<std::string, std::function<Command*(const std::string &, std::vector<Figure*> &)>> createCommandFactory(SvgManager &svgmanager, FigureManager &figmanager, FileManager &filemanager) {
//     return {
//         {"create", [&](const std::string &args, std::vector<Figure*> &figures) {
//             return new CreateCommand(args, svgmanager, figmanager);
//         }},
//         {"translate", [&](const std::string &args, std::vector<Figure*> &figures) {
//             return new TranslateCommand(args,svgmanager, figmanager);
//         }},
//         {"erase", [&](const std::string &args, std::vector<Figure*> &figures) {
//             return new EraseCommand(args, svgmanager, figmanager);
//         }},
//         {"within", [&](const std::string &args, std::vector<Figure*> &figures) -> Command* {
//             return new WithinCommand(args, svgmanager, figmanager);
//         }},
//         {"print", [&](const std::string &args, std::vector<Figure*> &figures) -> Command* {
//             if(!args.empty()){
//                 std::cerr << "Do not input anything other than the keyword 'print'" << std::endl;
//                 return nullptr;
//             }
//             else return new PrintCommand(svgmanager, figmanager);

//         }},
//         {"open", [&](const std::string &args, std::vector<Figure*> &figures) -> Command* {
//             return new OpenCommand(filemanager, args);
//         }},
//         {"save", [&](const std::string &args, std::vector<Figure*> &figures) -> Command* {
//             return new SaveCommand(filemanager, args);
//         }},
//         {"saveas", [&](const std::string &args, std::vector<Figure*> &figures) -> Command* {
//             return new SaveAsCommand(filemanager, args);
//         }},
//         {"close", [&](const std::string &args, std::vector<Figure*> &figures) -> Command* {
//             return new CloseCommand(filemanager, args);
//         }},
//         {"exit", [&](const std::string &args, std::vector<Figure*> &figures) -> Command* {
//             return new ExitCommand(filemanager, args);
//         }},
//         {"help", [&](const std::string &args, std::vector<Figure*> &figures) {
//             return new HelpCommand(filemanager, args);
//         }}
//     };
// }