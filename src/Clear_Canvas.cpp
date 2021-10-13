/**
 *  @file   Clear_Canvas.cpp
 *  @brief  Clear the canvas to the most recent color.
 *  @author Andres
 *  @date   2020-04-18
 ***********************************************/
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

#include <Clear_Canvas.hpp>

Clear_Canvas::Clear_Canvas(sf::Image& image, sf::Color color)
: m_image(image),m_color(color),m_client(nullptr) {}

Clear_Canvas::Clear_Canvas(sf::Image& image, sf::Color color, UDPNetworkClient* client)
: m_image(image), m_color(color), m_client(client){}

/*!\brief Clear the canvas to the
 *  most recent brush color
 */
void Clear_Canvas::execute() {
    m_image.create(600,400,m_color);
    if(m_client != nullptr){
        std::string color = std::to_string(m_color.r) + "," + std::to_string(m_color.g) + ","
                + std::to_string(m_color.b);
        m_client->sendString("CLEAR_CANVAS,EXECUTE," + color);
    }
}

/*!\brief Does nothing. Can't be undo.
 *
 */
void Clear_Canvas::undo() {
}
