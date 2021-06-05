#include "pathfinding.hpp"

Pathfinding::Pathfinding()
    : Pathfinding(WINDOW_WIDTH, WINDOW_HEIGHT, X_NODES, Y_NODES)
{
    
}

Pathfinding::Pathfinding(int width, int height, int x_nodes, int y_nodes)
    : x_nodes(x_nodes),
      y_nodes(y_nodes), 
      width(width), 
      height(height),
      nodes_width(width / x_nodes),
      nodes_height(height / y_nodes)
{
	this->window.create(sf::VideoMode(width, height), "Pathfinding");


}

Pathfinding::~Pathfinding()
{

}

void Pathfinding::loop() {

    draw_nodes();

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

void Pathfinding::create_nodes() {

    nodes = new Node[x_nodes * y_nodes];

    for(int x = 0; x < x_nodes; x++) {
        for(int y = 0; y < y_nodes; y++) {
            nodes[x * x_nodes + y].parent = nullptr;
            nodes[x * x_nodes + y].x = x;
            nodes[x * x_nodes + y].y = y;
            nodes[x * x_nodes + y].is_obstacle = false;
            nodes[x * x_nodes + y].is_visited = false;
            nodes[x * x_nodes + y].goal_score = __INT_MAX__;
        }
    }
}

void Pathfinding::draw_nodes() {
	for(int x = 0; x < x_nodes; x++) {
        for(int y = 0; y < y_nodes; y++) {
            Node* node = &nodes[x * x_nodes + y];

            sf::RectangleShape shape(sf::Vector2f(nodes_width, nodes_height));
            shape.setFillColor(sf::Color::White);
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1.f);
            shape.setPosition(sf::Vector2f(x * nodes_width, y * nodes_height));

            this->window.draw(shape);
        }
    }

    this->window.display();
}

int main(int argc, char *argv[])
{
    Pathfinding pathfinding;
    pathfinding.loop();
}
