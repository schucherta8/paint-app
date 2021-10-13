/**
 *  @file   Graphics_Manager.hpp
 *  @brief  Manages the GUI for the application
 *  @author Andres
 *  @date   2020-17-04
 ***********************************************/

#ifndef GRAPHICS_MANAGER_HPP
#define GRAPHICS_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../lib/nuklear.h"
#include "../lib/nuklear_sfml_gl2.h"

#include <App.hpp>
#include <Clear_Canvas.hpp>
#include <Chat.hpp>

/*!\brief This class represents a Graphic Manager.
 *
 * It handles the GUI initialization, events,
 * layout, and rendering.
 */
class Graphics_Manager {
    sf::RenderWindow* m_gui_window;
    struct nk_context* m_cxt;
    struct nk_colorf m_bg{};
    char m_buffer[256] = {0};
public:
    Graphics_Manager();
    void initialization();
    void eventHandler(sf::Event& event);
    void drawLayout(App& app, int& selected_color);
    void render();
    sf::RenderWindow& getGuiWindow();
    ~Graphics_Manager();
};

#endif