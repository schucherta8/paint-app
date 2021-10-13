/** 
 *  @file   Graphics_Manager.cpp 
 *  @brief  Class for Nuklear GUI elements
 *  @author Mike and Ryan and Andres 
 *  @date   2020-04-18 
 ***********************************************/

// Project header files
#include "Graphics_Manager.hpp"

/*!\brief Constructor for the Graphic Manager.
 */
Graphics_Manager::Graphics_Manager(){
    m_gui_window = nullptr;
    m_cxt = nullptr;
}

/*!\brief Initialize the graphics manager
 *  for an application. Must be run first
 *  in order to use other methods.
 */
void Graphics_Manager::initialization(){
    // Setup the context
    sf::ContextSettings settings(24, 8, 4, 2, 2);

    // Create a GUI window to draw to
    m_gui_window = new sf::RenderWindow(
            sf::VideoMode(600,400), "GUI Window",sf::Style::Default,settings);
    m_gui_window->setVerticalSyncEnabled(true);
    m_gui_window->setActive(true);
    glViewport(0, 0, m_gui_window->getSize().x, m_gui_window->getSize().y);
    m_cxt = nk_sfml_init(m_gui_window);

    struct nk_font_atlas *atlas;
    nk_sfml_font_stash_begin(&atlas);
    nk_sfml_font_stash_end();

    m_bg.r = 0.10f, m_bg.g = 0.18f, m_bg.b = 0.24f, m_bg.a = 1.0f;
}
/*!\brief Handles events for the Graphics Manager.
 *
 * @param event is an SFML event
 */
void Graphics_Manager::eventHandler(sf::Event& event){
    nk_input_begin(m_cxt);
    while(m_gui_window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            nk_sfml_shutdown();
            m_gui_window->close();
            exit(EXIT_SUCCESS);
        } else if(event.type == sf::Event::KeyReleased){
            // Check if the escape key is pressed.
            if(event.key.code == sf::Keyboard::Escape){
                nk_sfml_shutdown();
                m_gui_window->close();
                exit(EXIT_SUCCESS);
            }
        }
        nk_sfml_handle_event(&event);
    }
    nk_input_end(m_cxt);
}
/*!\brief Draws the GUI layout to a window.
 * Allows the user radio buttons to change colors,
 * use buttons to clear canvas, undo, redo, and
 * to send messages.
 *
 * @param app is a reference to the application.
 * @param selected_color used a flag to determine
 * which color is selected and shown active on GUI
 */
void Graphics_Manager::drawLayout(App& app, int& selected_color){
    if (nk_begin(m_cxt, "GUI", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {

        nk_layout_row_dynamic(m_cxt, 30, 4);
        if (nk_option_label(m_cxt, "black", selected_color == app.BLACK)){
            selected_color = app.BLACK;
            app.setBrushColor(sf::Color::Black);
        }
        if (nk_option_label(m_cxt, "white", selected_color == app.WHITE)){
            selected_color = app.WHITE;
            app.setBrushColor(sf::Color::White);
        }
        if (nk_option_label(m_cxt, "red", selected_color == app.RED)){
            selected_color = app.RED;
            app.setBrushColor(sf::Color::Red);
        }
        if (nk_option_label(m_cxt, "green", selected_color == app.GREEN)){
            selected_color = app.GREEN;
            app.setBrushColor(sf::Color::Green);
        }
        if(nk_option_label(m_cxt,"blue", selected_color == app.BLUE)){
            selected_color = app.BLUE;
            app.setBrushColor(sf::Color::Blue);
        }
        if(nk_option_label(m_cxt,"yellow", selected_color == app.YELLOW)){
            selected_color = app.YELLOW;
            app.setBrushColor(sf::Color::Yellow);
        }
        if(nk_option_label(m_cxt,"magenta", selected_color == app.MAGENTA)){
            selected_color = app.MAGENTA;
            app.setBrushColor(sf::Color::Magenta);
        }
        if(nk_option_label(m_cxt,"cyan", selected_color == app.CYAN)){
            selected_color = app.CYAN;
            app.setBrushColor(sf::Color::Cyan);
        }
        if (nk_button_label(m_cxt, "Clear Screen")){
            app.setBackgroundColor(app.getBrushColor());
            Command* c = new Clear_Canvas(app.GetImage(), app.getBrushColor(),&app.getClient());
            app.AddCommand(c);
            app.ExecuteCommand();
            app.ClearAllCommands();
        }
        if (nk_button_label(m_cxt, "Undo")) {
            app.UndoCommand();
        }
        if (nk_button_label(m_cxt, "Redo")) {
            app.RedoCommand();
        }

        nk_layout_row_dynamic(m_cxt, 20, 1);
        
        nk_layout_row_dynamic(m_cxt, 25, 1);
        //Learned from github.com/vurtun/nuklear/issues/683
        nk_edit_string_zero_terminated (m_cxt, NK_EDIT_FIELD, m_buffer, sizeof(m_buffer) -1, nk_filter_default);
        if (nk_button_label(m_cxt, "Send")) {
            Command* c = new Chat(m_buffer, &app.getClient());
            c->execute();
            memset(m_buffer, 0, 256);
            delete c;
        }
	nk_layout_row_dynamic(m_cxt, 20, 1);
	if (nk_button_label(m_cxt, "Clear text")) {
	    memset(m_buffer, 0, 256);
	}
    }
    nk_end(m_cxt);
}
/*!\brief Render and display GUI
 *
 */
void Graphics_Manager::render(){
    m_gui_window->setActive(true);
    m_gui_window->clear();
    glClearColor(m_bg.r, m_bg.g, m_bg.b, m_bg.a);
    glClear(GL_COLOR_BUFFER_BIT);
    nk_sfml_render(NK_ANTI_ALIASING_ON);
    m_gui_window->display();
}
/**
 * Get the GUI render window.
 *
 * @return the GUI render window.
 */
sf::RenderWindow& Graphics_Manager::getGuiWindow(){
    return *m_gui_window;
}

/**
 * Deconstructor for Graphics Manager
 */
Graphics_Manager::~Graphics_Manager()= default;
