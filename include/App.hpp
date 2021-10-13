/** 
 *  @file   App.hpp 
 *  @brief  App class interface
 *  @author Mike and Andres 
 *  @date   2020-09-02 
 ***********************************************/
#ifndef APP_HPP
#define APP_HPP

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
// Include standard library C++ libraries.
#include <list>
#include <queue>
#include <stack>
#include <string>
#include "Command.hpp"
#include "UDPNetworkClient.hpp"
// Project header files
// #include ...
class Graphics_Manager;

/*!\brief This class represents a paint application
 *
 * It tracks commands and canvas. It also contains a UDP
 * client object.
 */
class App {
   private:
    // Member variables
    //List to store commands
    std::list<Command*> m_commands;
    //Pointer to track command
    std::list<Command*>::iterator current;
    // Main image
    sf::Image* m_image;
    // Create a sprite that we overaly
    // on top of the texture.
    sf::Sprite* m_sprite;
    // Texture sent to the GPU for rendering
    sf::Texture* m_texture;
    sf::Color m_brush_color;
    sf::Color m_background_color;

    UDPNetworkClient* m_client;
    // Member functions
    // Store the address of our funcion pointer
    // for each of the callback functions.
    UDPNetworkClient* (*m_initFunc)();
    void (*m_updateFunc)(App& app,Graphics_Manager& manager, int& selected_color);
    void (*m_drawFunc)(App& app);
    // Keeps track of the previous mouse and current mouse positions
    // 'pmouse' is where the mouse previously was.
    // 'mouse' records where the mouse currently is.
    unsigned int pmouseX, pmouseY, mouseX, mouseY;

   public:
    // Default constructor which is hidden in the Singleton
    App();
    //GUI color selected
    enum gui_colors{BLACK,WHITE,RED,GREEN,BLUE,YELLOW,MAGENTA,CYAN};
    // Member Variables
    sf::RenderWindow* m_window;
    // Member functions
    void AddCommand(Command* c);
    void ExecuteCommand();
    void UndoCommand();
    void RedoCommand();
    void ClearAllCommands();
    void initializeBoard();

    sf::Image& GetImage();
    sf::Texture& GetTexture();
    sf::RenderWindow& GetWindow();

    void setMouseX(unsigned int x);
    void setMouseY(unsigned int y);
    void setPMouseX(unsigned int x);
    void setPMouseY(unsigned int y);
    unsigned int getPMouseX() const;
    unsigned int getPMouseY() const;
    unsigned int getMouseX() const;
    unsigned int getMouseY() const;
    UDPNetworkClient& getClient();

    void setBrushColor(sf::Color color);
    sf::Color getBrushColor() const;
    void setBackgroundColor(sf::Color color);
    sf::Color getBackgroundColor() const;

    void Init(UDPNetworkClient* (*initFunction)());
    void UpdateCallback(void (*updateFunction)(App& app,
            Graphics_Manager& manager, int& selected_color));
    void DrawCallback(void (*drawFunction)(App& app));
    void Loop();

    //Parses a string for values to create and execute a command.
    void executeCommandFromString(const std::string& input);
    ~App();
};

#endif
