/** 
 *  @file   App.cpp 
 *  @brief  Main class for program
 *  @author Mike and Ryan and Andres 
 *  @date   2020-04-18 
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../lib/nuklear.h"
#include "../lib/nuklear_sfml_gl2.h"
// Include standard library C++ libraries.
#include <cassert>
#include <string>
#include <CommandParser.hpp>
#include <Graphics_Manager.hpp>
// Project header files
#include "Clear_Canvas.hpp"

/*!\brief Constructor for the paint application
 *
 * It is composed of mouse and canvas variables,
 * brush and background color, function callbacks,
 * and a client.
 *
 */
App::App(){
    // Mouse variables
    mouseX = 0, mouseY = 0, pmouseX = 0, pmouseY = 0;
    //Canvas variables
    m_window = nullptr;
    m_image = new sf::Image;
    m_sprite = new sf::Sprite;
    m_texture = new sf::Texture;
    //Function pointers
    m_initFunc = nullptr, m_updateFunc = nullptr, m_drawFunc = nullptr;
    //Canvas Colors
    m_brush_color = sf::Color::Black;
    m_background_color = sf::Color::White;
    //Client
    m_client = nullptr;

    
}
/*! \brief 	When we draw, we would prefer to add
*		a command to a data structure.
*		
*/
void App::AddCommand(Command* c) {
    int counter = 0;
    auto it = current;
    ++it;
    //While current is not at the most recent command
    //delete all commands after the previous current command
    //to the end of the list.
    while (it != m_commands.end()) {
        Command* pcmd = *it;
        delete pcmd;
        ++it;
        ++counter;
    }
    m_commands.resize(m_commands.size() - counter);

    //Get current element
    m_commands.push_back(c);
    current = m_commands.end();
    --current;
}
/*! \brief Undo current command and then move
*       to the previous command.
* 
*/
void App::UndoCommand() {
    if (current != --m_commands.rend().base()) {
        Command* cmd = *current;
        cmd->undo();
        --current;
    }
}

/*! \brief Move to the next command
*       and then execute it.
*  
*/
void App::RedoCommand() {
    if (current != --m_commands.end()) {
        ++current;
        Command* cmd = *current;
        cmd->execute();
    }
}
/*! \brief 	Execute the current command.
*
*/
void App::ExecuteCommand() {
    Command* cmd = *current;
    cmd->execute();
}
/*!\brief Clear all previous commands.
 *
 */
void App::ClearAllCommands(){
    auto it = m_commands.begin();
    while (it != m_commands.end()) {
        Command* pcmd = *it;
        delete pcmd;
        ++it;
    }
    m_commands.clear();
    current = m_commands.end();
    --current;
}
/*!\brief Set the current mouse x-axis value
 *
 * @param x an unsigned integer x-axis value
 */
void App::setMouseX(unsigned int x) {mouseX = x;}
/*!\brief Set the current mouse y-axis value
 *
 * @param y an unsigned integer y-axis value
 */
void App::setMouseY(unsigned int y) {mouseY = y;}
/*!\brief Set the previous mouse x-axis value
 *
 * @param x an unsigned integer x-axis
 */
void App::setPMouseX(unsigned int x){pmouseX = x;}
/*!\brief Set the previous mouse y-axis value
 *
 * @param x an unsigned integer y-axis
 */
void App::setPMouseY(unsigned int y) {pmouseY = y;}
/*!\brief Get the current mouse x-axis value
 *
 * @return current mouse x-axis value
 */
unsigned int App::getMouseX() const {return mouseX;}
/*!\brief Get the current mouse y-axis value
 *
 * @return current mouse y-axis value
 */
unsigned int App::getMouseY() const {return mouseY;}
/*!\brief Get the previous mouse x-axis value
 *
 * @return previous mouse x-axis value
 */
unsigned int App::getPMouseX() const {return pmouseX;}
/*!\brief Get the previous mouse y-axis value
 *
 * @return previous mouse y-axis value
 */
unsigned int App::getPMouseY() const {return pmouseY;}

/*!\brief Get the reference to a client object
 *
 * @return a reference to a client object
 */
UDPNetworkClient& App::getClient() {return *m_client;}

/*!\brief Set the current brush color
 *
 * @param color is the current brush color
 */
void App::setBrushColor(sf::Color color) {
    m_brush_color = color;
}
/*!\brief Get the current brush color
 *
 * @return the color of the brush
 */
sf::Color App::getBrushColor() const {
    return m_brush_color;
}
/*!\brief Set the background color
 *
 * @param color is a background color
 */
void App::setBackgroundColor(sf::Color color) {
    m_background_color = color;
}
/*!\brief Get the background color
 *
 * @return the background color
 */
sf::Color App::getBackgroundColor() const {
    return m_background_color;
}
/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*		
*/
sf::Image& App::GetImage() {
    return *m_image;
}

/*! \brief 	Return a reference to our m_Texture so that
*		we do not have to publicly expose it.
*		
*/
sf::Texture& App::GetTexture() {
    return *m_texture;
}

/*! \brief 	Return a reference to our m_window so that we
*		do not have to publicly expose it.
*		
*/
sf::RenderWindow& App::GetWindow() {
    return *m_window;
}

/*! \brief 	Initializes the App and sets up the main
*		rendering window(i.e. our canvas.). It
*       also initializes the server or client.
*/
void App::Init(UDPNetworkClient* (*initFunction)()) {
    // Set our initialization function to perform any user
    // initialization
    m_initFunc = initFunction;
}

/*!\brief Initialize the canvas.
 *
 */
void App::initializeBoard() {
    m_window = new sf::RenderWindow(sf::VideoMode(600, 400), "Mini-Paint alpha 0.0.2", sf::Style::Close);
    m_window->setVerticalSyncEnabled(true);
    // Create an image which stores the pixels we will update
    m_image->create(600, 400, m_background_color);
    assert(m_image != nullptr && "m_image != nullptr");
    // Create a texture which lives in the GPU and will render our image
    m_texture->loadFromImage(*m_image);
    assert(m_texture != nullptr && "m_texture != nullptr");
    // Create a sprite which is the entity that can be textured
    m_sprite->setTexture(*m_texture);
    assert(m_sprite != nullptr && "m_sprite != nullptr");
    current = m_commands.end();

}

/*! \brief 	Set a callback function which will be called
		each iteration of the main loop before drawing.
*		
*/
void App::UpdateCallback(void (*updateFunction)(App& app, Graphics_Manager& manager, int& selected_color)) {
    m_updateFunc = updateFunction;
}

/*! \brief 	Set a callback function which will be called
		each iteration of the main loop after update.
*		
*/
void App::DrawCallback(void (*drawFunction)(App& app)) {
    m_drawFunc = drawFunction;
}

/*! \brief 	The main loop function which handles initialization
		and will be executed until the main window is closed.
		Within the loop function the update and draw callback
		functions will be called.
*		
*/
void App::Loop() {
    // Call the init function
    m_client = m_initFunc();
    initializeBoard();
    Graphics_Manager manager;
    manager.initialization();
    int selected_color = BLACK;
    // Start the main rendering loop
    while (m_window->isOpen() && manager.getGuiWindow().isOpen()) {
	//Receive data from server
        std::string tempString = m_client->receiveData();
        //Check if we received a string of data
        if(!tempString.empty() && tempString.at(0) != 'H'){
            executeCommandFromString(tempString);
        }
        // Clear the window
        m_window->clear();
        // Updates specified by the user
        m_updateFunc(*this, manager, selected_color);
        // Additional drawing specified by user
        m_drawFunc(*this);
        // Draw to the canvas
        m_window->draw(*m_sprite);
        // Display the canvas
        m_window->display();
    }
}

/*!\brief Execute a command from a parsed string.
 *
 * @param input is a string that contains command type,
 * action, and values.
 */
void App::executeCommandFromString(const std::string& input){
    CommandParser parser(*m_image);
    parser.parseString(input);
    Command* cmd = parser.getCommand();
    //Depending on the command type and action type we execute or undo
    if(parser.getCommandType() == "DRAW"){
        if(parser.getActionType() == "EXECUTE"){
            cmd->execute();
        } else{
            cmd->undo();
        }
        delete cmd;
    } else if(parser.getCommandType() == "CLEAR_CANVAS") {
        if(parser.getActionType() == "EXECUTE"){
            cmd->execute();
            ClearAllCommands();
            sf::Color background = m_image->getPixel(0,0);
            setBackgroundColor(background);
        }
        delete cmd;
    } else if (parser.getCommandType() == "CHAT"){
        if(parser.getActionType() == "EXECUTE"){cmd->execute();}
    }
}
/*!\brief Deconstructor for app.
 *
 * Free any allocated member to canvas values and command values in the list.
 *
 */
App::~App() {
    delete m_image;
    delete m_sprite;
    delete m_texture;

    //Delete any command objects left in the list.
    auto iter = m_commands.begin();
    while (iter != m_commands.end()) {
        Command* cmd = *iter;
        delete cmd;
        ++iter;
    }
    m_commands.clear();
    delete m_window;
    delete m_client;
}