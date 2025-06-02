#ifndef __BasePatternCommmand_HPP
#define __BasePatternCommmand_HPP

// Base Command class with virtual destructor and void execute()

// starter for command pattern
class Command{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

#endif