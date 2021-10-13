/** 
 *  @file   UDPNetworkServer.cpp 
 *  @brief  Class for server object
 *  @author Mike and Ryan and Andres 
 *  @date   2020-04-18 
 ***********************************************/

// Include standard library C++ libraries.
#include <iostream>
#include <time.h>
#include <array>
// Project header files
#include "UDPNetworkServer.hpp"
#include "Draw.hpp"

/*!\brief Construct our UDP Server
 *
 * @param name of our server
 * @param address of our server
 * @param port of our server
 */
UDPNetworkServer::UDPNetworkServer(const std::string& name, sf::IpAddress address,unsigned short port){
    m_name = name;
    m_ipAddress = address;
    m_port = port;
    m_start = false;
    std::cout << "Server Constructor" << std::endl;
}

/*!\brief Default deconstructor for UDP server.
 *
 */
UDPNetworkServer::~UDPNetworkServer()= default;

/*!\brief Start the server.
 *
 * The server is a non-blocking UDP server which will bind
 * to a port if it is available. The server will listen where
 * clients are communicating from, and store that information.
 *
 * @param test checks if the server is a test server
 * @param maxTime used for test server which have a limited lifespan.
 *
 */
int UDPNetworkServer::start(bool test, double maxTime){
    
    time_t start = time(0);
    double elapsedTime = 0;
    std::cout << "Starting UDP Network server" << std::endl;
    // Attempt to bind to a port
    int status;
    status = (m_socket.bind(m_port) != sf::Socket::Done);
    if(status){
	std::cout << "Unable to bind -- Error: " << status << std::endl;
        return status;
    }
    m_start = true;

    // We are going to create a non-blocking UDP server..
    m_socket.setBlocking(false);
    
    // Start a server that will run forever
    while(m_start){

        // When a connection is made to our server, we get some amount of bytes
        // We store the clients ip and port that is connected
	std::array<char,128> in{};
	sf::IpAddress senderIp;
	size_t received;
	unsigned short senderPort;
	// If the server receives a message
	// then we want to broadcast that message out to
	// all potential folks who have joined our server.
	if(m_socket.receive(&in,in.size(),received,m_ipAddress,senderPort) == sf::Socket::Done){
            std::string input(std::begin(in),std::end(in));
            // Check if this is the first message sent by the client
            // by iterating through all of our current clients.
            // If we reach the end of the map, then we know this is a
            // new client.
            std::map<unsigned short, sf::IpAddress>::iterator clientIterator;
            clientIterator = m_activeClients.find(senderPort);
            if(clientIterator == m_activeClients.end()){
                std::cout << "First time joiner!" << std::endl;
                handleClientJoining(senderPort,senderIp); 
                // Add client to our activeClients map so we can send them more
                // messages that come in
                m_activeClients[senderPort] = senderIp;
            }

            if(input.find("CLEAR_CANVAS") != std::string::npos){
                m_sentHistory.clear();
            }
            if(input.find("CHAT") != std::string::npos){
                m_msgHistory.push_back(input);
            } else{
                m_sentHistory.push_back(input);
            }
            // We create an iterator that looks through our map
            // For each of our clients we are going to send to them
            // (including the client that just joined) the message that
            // was just received.
            std::map<unsigned short, sf::IpAddress>::iterator ipIterator;
            for(ipIterator = m_activeClients.begin(); ipIterator != m_activeClients.end(); ipIterator++){
                //Send data from the server to clients except for the original sender client.
		        //Original sender client is sent its data if it is the test string
                if(ipIterator->first != senderPort || input == "1A (from testClient)") {
                    m_socket.send(input.c_str(),input.size()+1, ipIterator->second, ipIterator->first);
                }
            }
		}
	    //Is this a test server.
	    if (test) {
	        if (elapsedTime >= maxTime) {
	    	    return 0;
	        } else {
	    	    elapsedTime = difftime(time(0), start);
	    }
	}

    } // End our server while loop
    return 0;
}

/*!\brief Stop the server.
 *
 */
int UDPNetworkServer::stop(){
    m_start = false;
    return 0;
}



/*!\brief Handle a new client joining the server.
 *  By giving a log of all the command and
 *  message history.
 *
 * @param clientPort the client's port number
 * @param clientIpAddress the client's IP address
 */
int UDPNetworkServer::handleClientJoining(unsigned short clientPort, 
                                         sf::IpAddress clientIpAddress){
    std::cout << "Updating new client" << std::endl;
    // Iterate through every message sent and send it to the client.
    for(auto & i : m_sentHistory){
        m_socket.send(i.c_str(),i.length()+1,clientIpAddress,clientPort);
    }
    for(auto & i : m_msgHistory){
        m_socket.send(i.c_str(),i.length()+1,clientIpAddress,clientPort);
    }
    return 0;
}


