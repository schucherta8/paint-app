/** 
 *  @file   Command.hpp 
 *  @brief  Represents an actionable command by the user.
 *  @author Mike and Andres 
 *  @date   2020-09-02 
 ***********************************************/
#ifndef COMMAND_HPP
#define COMMAND_HPP

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
// Project header files
// #include ...

/*!\brief This class represents a command action.
 *
 */
class Command {
   public:
    Command();
    // Destructor for a command
    virtual ~Command();

    virtual void execute() = 0;
    virtual void undo() = 0;
};

#endif
