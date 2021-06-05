#include "pathfinding.hpp"

Pathfinding::Pathfinding()
    : Pathfinding(WINDOW_WIDTH, WINDOW_HEIGHT, X_NODES, Y_NODES)
{
    
}

Pathfinding::Pathfinding(int width, int height, int x_nodes, int y_nodes)
{
	this->window.create(sf::VideoMode(width, height), "Pathfinding");
}

Pathfinding::~Pathfinding()
{

}

void Pathfinding::loop() {
	while(this->window.isOpen()) {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                this->window.close();
            }
        }
    }
}

int main(int argc, char *argv[])
{
    Pathfinding pathfinding;
    pathfinding.loop();
}
