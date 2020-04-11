#include "Leaf.h"

Leaf::Leaf(glm::vec2 pos)
{
	position = pos;
	reached = false;
}

glm::vec2 Leaf::get_position() const
{
	return this->position;
}

void Leaf::set_reached()
{
	this->reached = true;
}

bool Leaf::get_reached() const
{
	return this->reached;
}