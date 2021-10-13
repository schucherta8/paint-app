/**
 *  @file   main_test.cpp
 *  @brief  Unit Tests for our program
 *  @author Ryan and Andres
 *  @date   2020-04-18
 ***********************************************/

#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
#include <thread>
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"
#include "Clear_Canvas.hpp"
#include "Chat.hpp"
#include "UDPNetworkClient.hpp"
#include "UDPNetworkServer.hpp"
#include "Command_Stream.hpp"
#include "Mock_Command.hpp"

// UDPNetworkClient* client = new UDPNetworkClient("testClient", 50001);
// UDPNetworkClient* client2 = new UDPNetworkClient("testClient2", 50002);

// //Callback functions to initialize apps
// UDPNetworkClient* initialization() {
//     std::cout << "Test init 1. Joining server." << std::endl;
//     client->joinServer(sf::IpAddress::getLocalAddress(), 49999);
//     return client;
// }
// UDPNetworkClient* initialization2() {
//     std::cout << "Starting the App" << std::endl;
//     return client2;
// }

// //Starts a server in test mode, where it will only run for a limited time
// void startServer(UDPNetworkServer* server) {
//     server->start(true, 3);
// }

/**
 * ! \brief Test the instantiation of image, texture, and window objects
 * BASIC TEST
 */
// TEST_CASE("Test image texture window happens after app init"){
//     App app;
//     sf::Image* image = &app.GetImage();
//     sf::Texture* texture = &app.GetTexture();
//     REQUIRE(app.m_window == nullptr);
//     REQUIRE(texture != nullptr);
//     REQUIRE(image != nullptr);
//     app.initializeBoard();
//     REQUIRE(app.m_window != nullptr);
//     //app.Destroy();
// }

TEST_CASE("Test Command_Stream add() and remove()") {

    Command_Stream cs;
    std::cout << "Command Stream Created Succesfully" << std::endl;

    Command* cmd1 = new Mock_Command("Cmd 1");
    Command* cmd2 = new Mock_Command("Cmd 2");
    Command* cmd3 = new Mock_Command("Cmd 3");
    Command* cmd4 = new Mock_Command("Cmd 4");
    Command* cmd5 = new Mock_Command("Cmd 5");

    std::cout << "Commands Created Succesfully" << std::endl;

    cs.add(cmd1);
    cs.add(cmd2);
    cs.add(cmd3);
    cs.add(cmd4);
    cs.add(cmd5);
    
    std::cout << "Commands added Succesfully" << std::endl;

    while(!cs.isEmpty()) {
        cs.getCurrent()->execute();
        cs.remove();
    }
    std::cout << "Commands removed Succesfully" << std::endl;
    REQUIRE(cs.isEmpty() == true);
}

TEST_CASE("Test remove() from empty Command Stream") {
    Command_Stream cs;
    std::cout << "Command Stream Created Succesfully" << std::endl;

    REQUIRE(cs.isEmpty() == true);

    cs.remove();
    std::cout << "Removing item from empty command stream." << std::endl;

    REQUIRE(cs.getCurrent() == nullptr);
    std::cout << "Null returned from empty command stream after remove()." << std::endl;
}

TEST_CASE("Test Undo and Redo") {
    Command_Stream cs;

    std::cout << "Command Stream Created Succesfully" << std::endl;

    std::vector<Command*> commands;
    commands.push_back(new Mock_Command("Command 1"));

    while(!commands.empty()) {
        Command* cmd = commands.back();
        cmd->execute();
        commands.pop_back();
    }
}
// /**
//  * ! \brief Test the initialized state of the canvas is
//  * set correctly
//  * ANOTHER BASIC TEST
//  */
// TEST_CASE("Test initial state of canvas") {
//     App app;
//     app.initializeBoard();
//     sf::RenderWindow *initializedWindow = &app.GetWindow();
//     sf::Vector2u dimensions = initializedWindow->getSize();
//     REQUIRE(dimensions.x == 600);
//     REQUIRE(dimensions.y == 400);
//     for(int row = 0; row < dimensions.y; ++row){
//         for(int col = 0; col < dimensions.x; ++col){
//             REQUIRE(app.GetImage().getPixel(col,row) == sf::Color::White);
//         }
//     }
//     //app.Destroy();
// }

// /**
//  * !\brief Test that draw commands can be added to the command stack and executed
//  *
//  */
// TEST_CASE("Testing Draw add and execute command"){
//     App app;
//     //app.Init(&initialization);
//     app.initializeBoard();
//     int e_r = sf::Color::Red.r,e_g = sf::Color::Red.g,e_b = sf::Color::Red.b;
//     Command* cmd = new Draw(100,100,0,0,
//             app.GetImage(),sf::Color::Red,app.getBackgroundColor());
//     app.AddCommand(cmd);
//     app.ExecuteCommand();
//     sf::Color actual_color = app.GetImage().getPixel(100,100);
//     int a_r = actual_color.r, a_g = actual_color.g , a_b = actual_color.b;
//     REQUIRE(e_r == a_r);
//     REQUIRE(e_g == a_g);
//     REQUIRE(e_b == a_b);
// }
// /*!\brief We allowed clients to use a Clear_Canvas command which is paired up with
//  * ClearAllCommands to clear the canvas to another color and remove
//  * all client's command lists that are connected to the server.
//  */
// TEST_CASE("Clearing the canvas"){
//     App app;
//     app.initializeBoard();
//     int e_r = sf::Color::Blue.r,e_g = sf::Color::Blue.g,e_b = sf::Color::Blue.b;
//     Command* cmd = new Draw(100,100,0,0,
//                             app.GetImage(),sf::Color::Red,app.getBackgroundColor());
//     app.AddCommand(cmd);
//     cmd = new Clear_Canvas(app.GetImage(),sf::Color::Blue);
//     app.AddCommand(cmd);
//     app.ExecuteCommand();
//     app.ClearAllCommands();
//     sf::Color actual_color = app.GetImage().getPixel(0,0);
//     int a_r = actual_color.r, a_g = actual_color.g , a_b = actual_color.b;
//     REQUIRE(e_r == a_r);
//     REQUIRE(e_g == a_g);
//     REQUIRE(e_b == a_b);
// }

// /**
//  *!\brief Networking Test Case 1: Can multiple clients join a server and send strings to
//  *			          each other.
//  */
// TEST_CASE("Clients attempting to join a local server") {
//     UDPNetworkServer* server = new UDPNetworkServer("server", sf::IpAddress::getLocalAddress(), 50000);

    
//     //the server is run on a different thread so it and the client can be run simultaneously
//     std::thread th1(startServer, server);

//     //Lambda function for sending message and checking if it was received
//     auto testConnection = [](UDPNetworkClient* client) {
// 	//client threads need to wait 1 second to make sure the server starts first
// 	sleep(1);
//     	client->joinServer(sf::IpAddress::getLocalAddress(), 50000);
//     	client->sendString("1A");
//     	bool received = false;
//     	std::string serverString = "k";
//     	//Waits for the server to send data
//         while(!received) { 
// 	    serverString = client->receiveData();
// 	    if (!serverString.empty() && serverString.at(0) != 't') {
// 	        received = true;
// 	    }
//     	}
// 	    //Need to strip null characters so compare will work
// 	    serverString.erase(std::remove(serverString.begin(), serverString.end(), '\0'), serverString.end());
// 	    if (client->getUsername().compare("testClient")==0) {
// 	        REQUIRE(serverString.compare("1A (from testClient2)") == 0);
// 	    } else if (client->getUsername().compare("testClient2")==0) {
// 	        REQUIRE(serverString.compare("1A (from testClient)") == 0);
// 	    }
//     };

    
//     std::thread th2(testConnection, client);
//     std::thread th3(testConnection, client2);

//     th1.join();
//     th2.join();
//     th3.join();
// }

// /**
//  * !/brief Networking 2: Have a client send a draw, undo and redo to the server
//  *              and have the server send those commands to a differnent
//  *              client
//  */
// TEST_CASE("Client attempting to draw undo and redo to a server and another client") {
//     UDPNetworkServer* server = new UDPNetworkServer("server", sf::IpAddress::getLocalAddress(), 49999);
//     //the server is run on a different thread so it and the client can be run simultaneously
//     std::thread th1(startServer, server);
//     App* app = new App();

//     //Lambda function to have a client execute commands
//     auto testDraw = [](App* app) {
//         //client threads need to wait 1 second to make sure the server starts first
//         sleep(1);
//         app->Init(&initialization);
//         app->initializeBoard();
//         client->joinServer(sf::IpAddress::getLocalAddress(), 49999);
//         client->sendString("testClient is joining");
//         Command* cmd = new Draw(80,80,0,0,
//                 app->GetImage(),sf::Color::Red,app->getBackgroundColor(), client);
//         app->AddCommand(cmd);
//         app->ExecuteCommand();
//         Command* cmd2 = new Draw(120,120,0,0,
//                 app->GetImage(),sf::Color::Red,app->getBackgroundColor(), client);
//         app->AddCommand(cmd2);
//         app->ExecuteCommand();
//         app->UndoCommand();
//         app->RedoCommand();
//     };

//     //Lambda function for a client to listen to commands
//     auto testListen = []() {
//         //client threads need to wait 1 second to make sure the server starts first
//         sleep(1);
//         client2->joinServer(sf::IpAddress::getLocalAddress(), 49999);
//         client2->sendString("testClient2 is joining");
//         int received = 0;
//         std::string commandList[4];
//     	std::string serverString = "k";
//     	//Waits for the server to send data
//         while(received < 4) {	
//             serverString = client2->receiveData();
//             if (!serverString.empty() && serverString.at(0) != 't') {
//                 commandList[received] = serverString;
//                 received++;
//             }
//     	}
//         //Need to remove null characters so compare works
//         for (int i = 0; i < 4; i++) {
//             commandList[i].erase(std::remove(commandList[i].begin(), commandList[i].end(), '\0'), commandList[i].end());
//         }
//         REQUIRE(commandList[0].compare("DRAW,EXECUTE,80,80,80,80,255,0,0,255,255,255 (from testClient)") == 0);
//         REQUIRE(commandList[1].compare("DRAW,EXECUTE,120,120,120,120,255,0,0,255,255,255 (from testClient)") == 0);
//         REQUIRE(commandList[2].compare("DRAW,UNDO,120,120,120,120,255,0,0,255,255,255 (from testClient)") == 0);
//         REQUIRE(commandList[3].compare("DRAW,EXECUTE,120,120,120,120,255,0,0,255,255,255 (from testClient)") == 0);
//     };

//     std::thread th2(testDraw, app);
//     std::thread th3(testListen);

//     th1.join();
//     th2.join();
//     th3.join();
// }


// /**
//  * !/brief Networking 3: If another client undoes your command, it should undo on your screen.
//  *		 This test ensures that this functionality works.
//  */
// TEST_CASE("Testing if a client can undo another clients draw") {
//     UDPNetworkServer* server = new UDPNetworkServer("server", sf::IpAddress::getLocalAddress(), 49998);
//     //the server is run on a different thread so it and the client can be run simultaneously
//     std::thread th1(startServer, server);
//     App* app = new App();

//     //Lambda function to have a client execute commands
//     auto testDraw = [](App* app) {
//         //client threads need to wait 1 second to make sure the server starts first
//         sleep(1);
//         app->Init(&initialization);
//         app->initializeBoard();
//         client->joinServer(sf::IpAddress::getLocalAddress(), 49998);
//         client->sendString("testClient is joining");
//         Command* cmd = new Draw(80,80,0,0,
//                 app->GetImage(),sf::Color::Red,app->getBackgroundColor(), client);
//         app->AddCommand(cmd);
//         app->ExecuteCommand();
//     	bool received = false;
//     	std::string serverString = "k";
// 	    while(!received) {
//             serverString = client->receiveData();
//             if (!serverString.empty() && serverString.at(0) != 't') {
//                 received = true;
//                 app->executeCommandFromString(serverString);
// 	        }
//     	}
// 	    int e_r = 255,e_g = 255,e_b = 255;
// 	    sf::Color actual_color = app->GetImage().getPixel(80,80);
//         int a_r = actual_color.r, a_g = actual_color.g , a_b = actual_color.b;
//         REQUIRE(e_r == a_r);
//         REQUIRE(e_g == a_g);
//         REQUIRE(e_b == a_b);
//     };

//     //Lambda function for a client to listen to commands
//     auto testListen = []() {
//         //client threads need to wait 1 second to make sure the server starts first
//         sleep(1);
//         client2->joinServer(sf::IpAddress::getLocalAddress(), 49998);
//         client2->sendString("testClient2 is joining");
//     	bool received = false;
//     	std::string serverString = "k";
//     	//Waits for the server to send data
//         while(!received) {
//             serverString = client2->receiveData();
//             if (!serverString.empty()) {
//                 received = true;
//                 client2->sendString("DRAW,UNDO,80,80,80,80,255,0,0,255,255,255");
//             }
//     	}
//     };
//     std::thread th2(testDraw, app);
//     std::thread th3(testListen);

//     th1.join();
//     th2.join();
//     th3.join();
// }

// /**
//  * !/brief Tests if two clients can send chats to the server and receive each others message.
//  *
//  */
// TEST_CASE("Testing chat functionality") {
//     UDPNetworkServer* server = new UDPNetworkServer("server", sf::IpAddress::getLocalAddress(), 49997);
//     UDPNetworkClient* client3 = new UDPNetworkClient("testClient3", 50003);
//     UDPNetworkClient* client4 = new UDPNetworkClient("testClient4", 50004);

//     //the server is run on a different thread so it and the client can be run simultaneously
//     std::thread th1(startServer, server);

//     //Lambda function for sending chat and checking if it was received
//     auto testConnection = [](UDPNetworkClient* client) {
//         //client threads need to wait 1 second to make sure the server starts first
//         sleep(1);
//     	client->joinServer(sf::IpAddress::getLocalAddress(), 49997);
//     	client->sendString(client->getUsername() + "is joining");
//         Command* c = new Chat("sent from " + client->getUsername(), client);
//         c->execute();
//     	bool received = false;
//     	std::string serverString = "k";
//     	//Waits for the server to send data
//         while(!received) { 
//             serverString = client->receiveData();
//             if (!serverString.empty() && serverString.at(0) != 't') {
//                 received = true;
//             }
//     	}
//         //Need to strip null characters so compare will work
//         serverString.erase(std::remove(serverString.begin(), serverString.end(), '\0'), serverString.end());
//         //Check if the client received the other client's chat
//         if (client->getUsername().compare("testClient3")==0) {
//             REQUIRE(serverString.compare("CHAT,EXECUTE,sent from testClient4 (from testClient4)") == 0);
//         }
//         else if (client->getUsername().compare("testClient4")==0) {
//             REQUIRE(serverString.compare("CHAT,EXECUTE,sent from testClient3 (from testClient3)") == 0);
//         }
//     };
    
//     std::thread th2(testConnection, client3);
//     std::thread th3(testConnection, client4);

//     th1.join();
//     th2.join();
//     th3.join();
// }
