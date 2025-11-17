#ifndef COMMANDBASE_H
#define COMMANDBASE_H

class CommandBase {
public:
    virtual ~CommandBase() {}

    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual const char* getName() const = 0;
};

#endif // COMMANDBASE_H