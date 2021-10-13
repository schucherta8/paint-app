/**
 *  @file   CommandParser.hpp
 *  @brief  Parses and returns commands
 *  @author Andres
 *  @date   2020-15-04
 ***********************************************/

#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Command.hpp"

/**
 * Represents a parser for command objects. This object will
 * parse strings for valid commands and is able to return commands.
 */
class CommandParser {
    sf::Image& m_image;
    std::string m_command_type;
    std::string m_action_type;
    std::string m_chat_msg;
    std::vector<int> m_args;

public:
    explicit CommandParser(sf::Image& image);
    bool parseString(const std::string& input);
    Command* getCommand();
    std::string getCommandType();
    std::string getActionType();
    ~CommandParser();
};


#endif //COMMAND_PARSER_HPP
