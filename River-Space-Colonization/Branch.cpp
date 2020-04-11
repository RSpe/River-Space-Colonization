#include "Branch.h"

Branch::Branch(glm::vec2 pos, glm::vec2 parent_pos, glm::vec2 dir)
{
	position = pos;
	parent_position = parent_pos;
	direction = dir;
}

glm::vec2 Branch::get_position() const
{
	return this->position;
}

glm::vec2 Branch::get_parent() const
{
	return this->parent_position;
}

glm::vec2 Branch::get_direction() const
{
	return this->direction;
}