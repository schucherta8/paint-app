/** 
 *  @file   CommandParser.cpp 
 *  @brief  Parser for incoming commands
 *  @author Mike and Ryan and Andres 
 *  @date   2020-04-18 
 ***********************************************/

// Include standard library C++ libraries.
#include <sstream>
// Project header files
#include "CommandParser.hpp"
#include <Draw.hpp>
#include <Clear_Canvas.hpp>
#include <Chat.hpp>

/**
 * Constructor for CommandParser object
 *
 * @param current image of a client canvas. Needed to create commands
 */
CommandParser::CommandParser(sf::Image& image)
: m_image(image), m_command_type(""), m_action_type(""){}

/*!\brief Parse an input string for command arguments.
 *
 * @param input is a command string
 * @return true if command string is valid, otherwise false.
 */
bool CommandParser::parseString(const std::string& input) {
    int i = 0;
    std::stringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ',')) {
        if(i == 0){
            if(token != "DRAW" && token != "CLEAR_CANVAS" && token != "CHAT"){
                return false;
            }
            m_command_type = token;
        }
        else if(i == 1){
            if(token != "EXECUTE" && token != "UNDO"){
                return false;
            }
            m_action_type = token;
        } else{
            if(m_command_type == "CHAT"){
                m_chat_msg += token;
            } else {
                try{//Arguments are pushed in the order of string.
                    m_args.push_back(std::stoi(token, nullptr));
                } catch (const std::invalid_argument& e){
                    e.what();
                    return false;
                }
            }
        }
        i++;
    }
    return true;
}
/*!\brief Get a command object.
 *
 * This will return a command object only if a string
 * has been parsed first, otherwise it returns a nullptr.
 *
 * @return a command object.
 */
Command* CommandParser::getCommand(){
    if(m_command_type == "DRAW"){
        sf::Color color(m_args[4], m_args[5], m_args[6]);
        sf::Color background(m_args[7], m_args[8], m_args[9]);
        return new Draw(m_args[0], m_args[1], m_args[2], m_args[3],
                        m_image, color, background);
    } else if(m_command_type == "CLEAR_CANVAS") {
        sf::Color color(m_args[0],m_args[1],m_args[2]);
        return new Clear_Canvas(m_image,color);
    } else if (m_command_type == "CHAT"){
        return new Chat(m_chat_msg);
    } else {
        return nullptr;
    }
}
/**
 * Return the command type
 * @return a string representing the command type
 */
std::string CommandParser::getCommandType(){
    return m_command_type;
}
/**
 * Return the action type of a command
 *
 * @return a string representing an action type of a command
 */
std::string CommandParser::getActionType(){
    return m_action_type;
}
/**
 * Deconstructor for CommandParser object.
 */
CommandParser::~CommandParser() = default;;
