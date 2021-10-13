/**
 *  @file   Chat.hpp
 *  @brief  Chat message interface.
 *  @author Andres
 *  @date   2020-09-04
 ***********************************************/
#ifndef CHAT_COMMAND_H
#define CHAT_COMMAND_H

#include <string>
#include <iostream>
#include "Command.hpp"
#include "UDPNetworkClient.hpp"

/*!\brief This class represents a Chat command.
 * Takes care of sending a message to the server.
 */
class Chat : public Command {
    std::string m_msg;
    UDPNetworkClient* m_client;

public:
    explicit Chat(const std::string& msg);
    Chat(const std::string& msg, UDPNetworkClient* client);
    void execute() override;
    void undo() override;
};
#endif //CHAT_COMMAND_H
