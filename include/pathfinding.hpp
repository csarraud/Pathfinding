#ifndef PATHFINDING_H
#define PATHFINDING_H
#pragma once

#include <SFML/Graphics.hpp>

#define X_NODES 20
#define Y_NODES 20
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define NODE_WIDTH (WINDOW_WIDTH / X_NODES)
#define NODE_HEIGHT (WINDOW_HEIGHT / Y_NODES)

class Pathfinding
{
	private:
		sf::RenderWindow window;

	public:
		Pathfinding();
		Pathfinding(int width, int height, int x_nodes, int y_nodes);
		~Pathfinding();

		void loop();
};
#endif
