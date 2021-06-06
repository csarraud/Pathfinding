#ifndef PATHFINDING_H
#define PATHFINDING_H
#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "node.hpp"

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
		int x_nodes, y_nodes;
		int width, height;
		int nodes_width, nodes_height;

		Node* nodes;
		std::list<Node*> tested_nodes;

		Node* start_node;
		Node* end_node;

	public:
		Pathfinding();
		Pathfinding(int width, int height, int x_nodes, int y_nodes);
		~Pathfinding();

		void loop();
		void create_nodes();
		void draw_nodes();
		sf::Color get_node_color(Node* node);
		void solve();
		int calculate_goal_score(Node& node);
};
#endif
