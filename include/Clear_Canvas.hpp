/**
 *  @file   Clear_Canvas.hpp
 *  @brief  Clearing the canvas action interface.
 *  @author Mike and Andres
 *  @date   2020-09-02
 ***********************************************/
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Command.hpp"
#include "UDPNetworkClient.hpp"

/*!\brief This class represents a clear canvas command.
 *
 * This class clears the canvas to last brush color executed.
 */
class Clear_Canvas : public Command {

    sf::Color m_color;
    sf::Image& m_image;
    UDPNetworkClient* m_client;

public:
    Clear_Canvas(sf::Image& image, sf::Color color);
    Clear_Canvas(sf::Image& image, sf::Color color, UDPNetworkClient* client);
    void execute() override;
    void undo() override;
};
#endif //BACKGROUND_H
