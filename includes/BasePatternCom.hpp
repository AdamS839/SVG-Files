#ifndef __BasePatternCom_HPP
#define __BasePatternCom_HPP

class Command{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

#endif