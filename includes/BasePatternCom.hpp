#ifndef __BasePatternCom_HPP
#define __BasePatternCom_HPP

// Base Command class with virtual destructor and void execute()

class Command{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

#endif