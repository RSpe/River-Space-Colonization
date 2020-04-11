#include "Leaf.h"

Leaf::Leaf(glm::vec2 pos)
{
	position = pos;
}

glm::vec2 Leaf::get_position() const
{
	return this->position;
}
