#ifndef NODE_H
#define NODE_H
#pragma once

#include <stdbool.h>

class Node  
{
	private:

	public:
		Node();
		~Node();

		Node* parent;
		int x, y;
		bool is_obstacle, is_visited;
		int goal_score;
};
#endif