/** 
 *  @file   Chat.cpp 
 *  @brief  Chat command class
 *  @author Ryan and Andres 
 *  @date   2020-04-18 
 ***********************************************/

// Project header files
#include "Chat.hpp"

/**
 * Constructor for a Chat command.
 * @param msg is a string message
 */
Chat::Chat(const std::string& msg) {
    m_msg = msg;
    m_client = nullptr;
}
/**
 * Constructor for a Chat command.
 * @param msg is a string message
 * @param client
 */
Chat::Chat(const std::string& msg, UDPNetworkClient* client) :  m_client(client){
    m_msg = msg;
}

/*!\brief Prints the message to terminal.
 * If UDPNetworkClient is not null, then
 * send the message to the server.
 */
void Chat::execute() {
    if(m_client != nullptr){
        m_client->sendString("CHAT,EXECUTE," + m_msg);
    }
    std::cout << m_msg << std::endl;
}
/*!\brief Currently does nothing. A chat command cannot be undo.
 *
 */
void Chat::undo() {}
