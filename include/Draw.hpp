/** 
 *  @file   Draw.hpp 
 *  @brief  Drawing actions interface. 
 *  @author Mike and Andres
 *  @date   2020-09-02 
 ***********************************************/
#ifndef DRAW_H
#define DRAW_H

// Include our Third-Party SFML header
// #include ...
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
// Include standard library C++ libraries.
#include <string>
// Project header files
#include "Command.hpp"
#include "UDPNetworkClient.hpp"

/*!\brief This class represents a Draw command.
 *
 * It draws a pixel on the canvas.
 */
class Draw : public Command {
    unsigned int m_mouseX, m_mouseY;
    unsigned int m_pmouseX, m_pmouseY;
    sf::Image& m_image;
    sf::Color m_color, m_background;
    UDPNetworkClient* m_client;
   public:
    Draw(unsigned int mouseX, unsigned int mouseY, unsigned int pmouseX,
            unsigned int pmouseY,sf::Image& image, sf::Color color, sf::Color background);
    Draw(unsigned int mouseX, unsigned int mouseY, unsigned int pmouseX,
         unsigned int pmouseY,sf::Image& image,sf::Color color,
         sf::Color background, UDPNetworkClient* client);
    void execute() override;
    void undo() override;
};

#endif
