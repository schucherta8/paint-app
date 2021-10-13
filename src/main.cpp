/** 
 *  @file   main.cpp 
 *  @brief  Entry point into the program.
 *  @author Mike and Ryan and Andres 
 *  @date   2020-04-18
 ***********************************************/

// g++ -std=c++17 *.cpp -o App -lsfml-graphics -lsfml-window -lsfml-system
//
// Note:	If your compiler does not support -std=c++17,
//		then try -std=c++14 then -std=c++11.
//
// HOW TO RUN
//
// ./App

// Include our Third-Party SFML header
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>
#include "../lib/nuklear.h"
#include "../lib/nuklear_sfml_gl2.h"
// Include standard library C++ libraries.
#include <iostream>
#include <list>
#include <Graphics_Manager.hpp>
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"
#include "Clear_Canvas.hpp"
#include "UDPNetworkClient.hpp"
#include "UDPNetworkServer.hpp"

/*! \brief 	Callback function to prompt the user to input server or client information.
 * 		After the information, begins the server or client.
 *		
 */

UDPNetworkClient* initialization() {
    UDPNetworkClient *client = nullptr;
    std::cout << "Starting the App" << std::endl;
    std::string role;
    std::string serverPort = "50000";
    std::string serverIpString;
    sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
    // Set the role
    std::cout << "Enter (s) for Server, Enter (c) for client: " << std::endl;
    std::cin >> role;

    // The std::cin function records the '\n' character,
    // so I instead just look at the first character of
    // the user input.
    // A 'trim' function may be more ideal.
    if(role[0] == 's'){
	    std::cout << "Enter the port number. Servers cannot share the same port and ip ('d' for 50000): ";
	    //std::string serverPort;
	    //std::string serverIp;
	    //sf::IpAddress sendIp;
	    std::cin >> serverPort;
	    if (serverPort == "d") {
		serverPort = "50000";
	    }
	    std::cout << "Enter the IP address ('l' for local address): ";
	    std::cin >> serverIpString;
	    if (serverIpString == "l") {
		serverIp = sf::IpAddress::getLocalAddress();
	    }
	    else {
		serverIp = serverIpString;
	    }
	    UDPNetworkServer server("Server Name",serverIp,std::stoi(serverPort));
	    // Create a server 
	    // Run the server on local network for now
	    server.start(false, 1);
    }else if(role[0] == 'c'){
	// Create a client and have them join
        std::string uname;
	    std::string ip;
        unsigned short port;
        std::cout << "Enter your username:";
        std::cin >> uname;
        std::cout << "Which port will you try? (e.g. 50001-50010): ";
        std::cin >> port;
        std::cout << "Enter IP address ('l' for local address): ";
        std::cin >> ip;
        sf::IpAddress sendIp(ip);
        std::cout << "Enter the server port ('d' for port 50000): ";
        std::cin >> serverPort;
	if (serverPort == "d") {
	    serverPort = "50000";
	}
	std::cout << "Enter the server IP address ('l' for local address): ";
	std::cin >> serverIpString;
	if (serverIpString == "l") {
	    serverIp = sf::IpAddress::getLocalAddress();
	}
	else {
	    serverIp = serverIpString;
	}
	client = new UDPNetworkClient(uname, port);
	if (ip == "l") {
	    client->joinServer(serverIp,std::stoi(serverPort));
	} else {
	    client->joinServer(sendIp, 50000);
	}
	client->setUsername(uname);
	client->sendString("Hello, "+uname+" is joining!");
	return client;
    }
}


/*!
 * \brief Set the key_pressed actions based on the type of key
 *
 * @param app is our application
 * @param key is the key type
 */
void set_key_pressed_actions(App& app, sf::Keyboard::Key& key, int& selected_color){
    
    switch(key){
        case sf::Keyboard::Escape:
            app.GetWindow().close();
            exit(EXIT_SUCCESS);
        case sf::Keyboard::Z:
            app.UndoCommand();
            break;
        case sf::Keyboard::Y:
            app.RedoCommand();
            break;
        case sf::Keyboard::Num1:
            selected_color = app.BLACK;
            app.setBrushColor(sf::Color::Black);
            break;
        case sf::Keyboard::Num2:
            selected_color = app.WHITE;
            app.setBrushColor(sf::Color::White);
            break;
        case sf::Keyboard::Num3:
            selected_color = app.RED;
            app.setBrushColor(sf::Color::Red);
            break;
        case sf::Keyboard::Num4:
            selected_color = app.GREEN;
            app.setBrushColor(sf::Color::Green);
            break;
        case sf::Keyboard::Num5:
            selected_color = app.BLUE;
            app.setBrushColor(sf::Color::Blue);
            break;
        case sf::Keyboard::Num6:
            selected_color = app.YELLOW;
            app.setBrushColor(sf::Color::Yellow);
            break;
        case sf::Keyboard::Num7:
            selected_color = app.MAGENTA;
            app.setBrushColor(sf::Color::Magenta);
            break;
        case sf::Keyboard::Num8:
            selected_color = app.CYAN;
            app.setBrushColor(sf::Color::Cyan);
            break;
        case sf::Keyboard::Space:
        {
            app.setBackgroundColor(app.getBrushColor());
            Command* c = new Clear_Canvas(app.GetImage(), app.getBrushColor(),&app.getClient());
            app.AddCommand(c);
            app.ExecuteCommand();
            app.ClearAllCommands();
            break;
        }
        default:
            break;
    }
}
/*! \brief 	The update function for the App callback
*		
*/
void update(App& app,Graphics_Manager& manager, int& selected_color) {
    // Update our canvas
    sf::Event event{};
    manager.eventHandler(event);
    while (app.GetWindow().pollEvent(event)) {
        if(event.type == sf::Event::Closed){
            app.GetWindow().close();
            exit(EXIT_SUCCESS);
        }
        else if (event.type == sf::Event::KeyPressed) {
            // Capture any keys that are pressed
            set_key_pressed_actions(app,event.key.code, selected_color);
        }
    }
    manager.drawLayout(app,selected_color);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i coordinates = sf::Mouse::getPosition(app.GetWindow());
        //Check if the mouse coordinates are out of bounds of the window
        if(coordinates.x > 0 && coordinates.y > 0
            && coordinates.x < app.GetWindow().getSize().x
            && coordinates.y < app.GetWindow().getSize().y){
            app.setMouseX(coordinates.x);
            app.setMouseY(coordinates.y);
            //Do not allow any repeating pixels in a row
            if (!(app.getMouseX() == app.getPMouseX() && app.getMouseY() == app.getPMouseY())) {
                Command* c = new Draw(app.getMouseX(), app.getMouseY(), app.getPMouseX(),
                        app.getPMouseY(), app.GetImage(),app.getBrushColor(),
                        app.getBackgroundColor(), &app.getClient());
                app.AddCommand(c);
                app.ExecuteCommand();
                // Where was the mouse previously before going to the next frame
                app.setPMouseX(app.getMouseX());
                app.setPMouseY(app.getMouseY());
            }
        }
    }
    manager.render();
}

/*! \brief 	The draw call 
*		
*/
void draw(App& app) {
    app.GetTexture().loadFromImage(app.GetImage());
}


/*! \brief 	The entry point into our program.
*		
*/
int main() {

    App app;
    // Call any setup function
    // Passing a function pointer into the 'init' function.
    // of our application.
    app.Init(&initialization);
    // Setup your keyboard
    app.UpdateCallback(&update);
    // Setup the Draw Function
    app.DrawCallback(&draw);
    // Call the main loop function
    app.Loop();
    

    return 0;
}
