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

    this->start_node = nullptr;
    this->end_node = nullptr;

    create_nodes();
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
            else if(event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                
                change_node_state(x, y);
                draw_nodes();
            }
            else if(event.type == sf::Event::KeyPressed) {
                if(this->start_node != nullptr && this->end_node != nullptr) {
                    solve();
                }
            }
        }
    }
}

void Pathfinding::change_node_state(int x_window, int y_window) {
	for(int x = 0; x < x_nodes; x++) {
        for(int y = 0; y < y_nodes; y++) {
            
            if(x_window > x * nodes_width && x_window < (x + 1) * nodes_width
                && y_window > y * nodes_height && y_window < (y + 1) * nodes_height) {
                    this->nodes[x * x_nodes + y].is_obstacle = true;
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

    this->start_node = &nodes[5];
    this->end_node = &nodes[378];
}

void Pathfinding::draw_nodes() {
	for(int x = 0; x < x_nodes; x++) {
        for(int y = 0; y < y_nodes; y++) {
            Node* node = &nodes[x * x_nodes + y];

            sf::RectangleShape shape(sf::Vector2f(nodes_width, nodes_height));
            shape.setFillColor(get_node_color(node));
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1.f);
            shape.setPosition(sf::Vector2f(x * nodes_width, y * nodes_height));

            this->window.draw(shape);
        }
    }

    this->window.display();
}

sf::Color Pathfinding::get_node_color(Node* node) {
	if(node->is_obstacle) {
        return sf::Color(200, 200, 200);
    }
    else if(node == this->start_node) {
        return sf::Color::Green;
    }
    else if(node == this->end_node) {
        return sf::Color::Red;
    }
    else if(node->is_visited) {
        return sf::Color::Yellow;
    }

    return sf::Color::White;
}

void Pathfinding::solve() {
	Node* current_node = this->start_node;
    calculate_goal_score(current_node);
    this->tested_nodes.push_back(current_node);
    
    while(current_node != this->end_node) {

        current_node = get_best_node();

        if(current_node == nullptr) {
            break;
        }

        for(Node* node : get_neighbors(current_node)) {
            
            calculate_goal_score(node);

            /*
             * If the node isn't already in tested_nodes list
             */
            if(std::find(this->tested_nodes.begin(), this->tested_nodes.end(), node) == this->tested_nodes.end()) {
                this->tested_nodes.push_back(node);
            }
        }

        current_node->is_visited = true;
        this->tested_nodes.pop_front();

        draw_nodes();
    }

    std::cout<<"Finished !"<<std::endl;
    this->start_node = nullptr;
    this->end_node = nullptr;
}

int Pathfinding::calculate_goal_score(Node* node) {
	int score = std::sqrt(
        (node->x - this->end_node->x) * (node->x - this->end_node->x) * 100
        + (node->y - this->end_node->y) * (node->y - this->end_node->y) * 100
    );

    node->goal_score = score;
    
    return score;
}

Node* Pathfinding::get_best_node() {
	
    this->tested_nodes.sort([](const Node* n1, const Node* n2) {
        return n1->goal_score < n2->goal_score;
    });

    while(!this->tested_nodes.empty() && this->tested_nodes.front()->is_visited) {
        this->tested_nodes.pop_front();
    }

    if(this->tested_nodes.empty()) {
        return nullptr;
    }

    return this->tested_nodes.front();
}

std::list<Node*> Pathfinding::get_neighbors(Node* node) {
	std::list<Node*> neighbors;

    for(int x = -1; x <= 1; x++) {
        for(int y = 0; y <= 1; y++) {
            int index = (node->x + x) * x_nodes + (node->y + y);

            if(index < 0 && index > x_nodes * y_nodes) {
                continue;
            }

            Node* neighbor = &this->nodes[index];

            if(!neighbor->is_obstacle) {
                neighbors.push_back(neighbor);
            }
        }
    }

    return neighbors;
}

int main(int argc, char *argv[])
{
    Pathfinding pathfinding;
    pathfinding.loop();
}
