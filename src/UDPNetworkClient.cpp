/** 
 *  @file   UDPNetworkClient.cpp 
 *  @brief  Class for Client object
 *  @author Mike and Ryan and Andres 
 *  @date   2020-04-18 
 ***********************************************/

// Include standard library C++ libraries.
#include <iostream>
#include <string>
#include <utility>
#include <array>
// Project header files
#include "UDPNetworkClient.hpp"

/*!\brief Constructor for a UDPNetworkClient object.
 * Bind socket to client port and set socket to non-blocking.
 *
 * @param username is the client's username
 * @param port is the client's port number
 */
UDPNetworkClient::UDPNetworkClient(const std::string& username, unsigned short port){
    m_serverPort = 50000;
    m_username = username;
    m_port = port;
    m_socket.bind(m_port);
    m_socket.setBlocking(false);
}

/*!\brief Default constructor for UDPNetworkClient
 *
 */
UDPNetworkClient::~UDPNetworkClient()= default;


/*!\brief Setup the server for which we will
 * attempt to communicate to and join.
 *
 * @param serverAddress is the server address
 * @param serverPort is the server port
 */
int UDPNetworkClient::joinServer(sf::IpAddress serverAddress, unsigned short serverPort){
    std::cout << "UDPClient will attempt to join server: " << std::endl;
    m_serverIpAddress = serverAddress;
    m_serverPort = serverPort;
    return 0;
}

/*!\brief Send a string containing data to the server.
 *
 * Return -1 if string to be sent is empty, otherwise 0
 *
 * @return an integer on whether sending data to the server was successful
 */
int UDPNetworkClient::sendString(const std::string& s){
    if(s.length() <= 0){return -1;}
    std::string str = s +  " (from "+ m_username+")";
    if(m_socket.send(str.c_str(),str.length()+1, m_serverIpAddress, m_serverPort) == sf::Socket::Done){}
    return 0;
}

/*!

*/
int UDPNetworkClient::sendPacket(sf::Packet& packet) {
    if(m_socket.send(packet, m_ipAddress, m_serverPort) == sf::Socket::Done) {
        return 0;
    }
    return -1;
}

/*!\brief Receive data from the server.
 *
 * If the socket receives no data, then it return an empty string,
 * otherwise returns a string containing information from the server.
 *
 * @return a string containing data from the server.
 */
std::string UDPNetworkClient::receiveData(){
    std::array<char,128> in{};
    size_t received;
    sf::IpAddress copyAddress = m_serverIpAddress;
    unsigned short copyPort = m_serverPort;
    if(m_socket.receive(&in,in.size(),received,copyAddress,copyPort) == sf::Socket::Done){
        if(received >0){
	    return std::string(in.begin(),in.end());
	}
    }
    return "";
}

/*!\brief Get the client's username.
 *
 * @return the client's username
 */
std::string UDPNetworkClient::getUsername(){return m_username;}

/*!\brief Set the client's username
 *
 */
int UDPNetworkClient::setUsername(const std::string& name){
    m_username = name;
    return 0;
}

