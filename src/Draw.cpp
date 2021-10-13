/** 
 *  @file   Draw.cpp 
 *  @brief  Draw implementation, all drawing actions are commands. 
 *  @author Mike and Ryan and Andres 
 *  @date   2020-04-18 
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
// #include ...
#include <string>
#include <sstream>
// Project header files
#include "Draw.hpp"

/*!\brief Constructor for Draw command
 *      that takes in current pixel, previous pixel,
 *      current image, brush color, and background color.
 *
 * @param mouseX is the pixel's x coordinate
 * @param mouseY is the pixel's y coordinate
 * @param pmouseX is the pixel's previous x coordinate
 * @param pmouseY is the pixel's previous y coordinate
 * @param m_image is the current image
 * @param color is the brush color
 * @param background is the background color
 */
Draw::Draw(unsigned int mouseX, unsigned int mouseY, unsigned int pmouseX,
           unsigned int pmouseY, sf::Image& m_image, sf::Color color,
           sf::Color background)
        : m_mouseX(mouseX), m_mouseY(mouseY), m_pmouseX(pmouseX), m_pmouseY(pmouseY),
          m_image(m_image), m_color(color), m_background(background) {
        m_client = nullptr;
}

/*!\brief Constructor for Draw command
 *      that takes in current pixel, previous pixel,
 *      current image, brush color, background color,
 *      and references a client object to send information to the server
 * @param mouseX is the pixel's x coordinate
 * @param mouseY is the pixel's y coordinate
 * @param pmouseX is the pixel's previous x coordinate
 * @param pmouseY is the pixel's previous y coordinate
 * @param m_image is the current image
 * @param color is the brush color
 * @param background is the background color
 * @param client
 */
Draw::Draw(unsigned int mouseX, unsigned int mouseY, unsigned int pmouseX,
        unsigned int pmouseY, sf::Image& m_image, sf::Color color,
        sf::Color background, UDPNetworkClient* client)
    : m_mouseX(mouseX), m_mouseY(mouseY), m_pmouseX(pmouseX), m_pmouseY(pmouseY),
    m_image(m_image), m_color(color), m_background(background), m_client(client) {}

/*! \brief Set the current pixel and the
*       color to black. If the there exist
*       a client object, then send the command
*       information to the server.
*/
void Draw::execute() {
    m_pmouseX = m_mouseX;
    m_pmouseY = m_mouseY;
    m_image.setPixel(m_mouseX, m_mouseY, m_color);
    if(m_client != nullptr){
        sf::Packet packet;
        packet << "DRAW" << m_mouseX << m_mouseY << m_pmouseX << m_pmouseY;
        std::stringstream stringStream;
        stringStream << "DRAW,EXECUTE," << m_mouseX << "," << m_mouseY << "," << m_pmouseX << "," << m_pmouseY << ",";
        stringStream << (int) m_color.r << "," << (int) m_color.g << "," << (int) m_color.b << ",";
        stringStream << (int) m_background.r << "," << (int) m_background.g << "," << (int) m_background.b;
        m_client->sendString(stringStream.str());
    }
}

/*! \brief Set the current pixel to the 
*       the previous pixel position. If the there exist
*       a client object, then send the command
*       information to the server.
*/
void Draw::undo() {
    m_image.setPixel(m_pmouseX, m_pmouseY, m_background);
    if(m_client != nullptr){
	    std::stringstream stringStream;
	    stringStream << "DRAW,UNDO," << m_mouseX << "," << m_mouseY << "," << m_pmouseX << "," << m_pmouseY << ",";
	    stringStream << (int) m_color.r << "," << (int) m_color.g << "," << (int) m_color.b << ",";
        stringStream << (int) m_background.r << "," << (int) m_background.g << "," << (int) m_background.b;
        m_client->sendString(stringStream.str());
    }
}
