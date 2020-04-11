#include "Branch.h"

Branch::Branch(std::shared_ptr<Branch> par, glm::vec2 pos, glm::vec2 dir)
{
	position = pos;
	parent = par;
	direction = dir;
}

glm::vec2 Branch::get_position() const
{
	return this->position;
}

std::shared_ptr<Branch> Branch::get_parent() const
{
	return this->parent;
}

glm::vec2 Branch::get_direction() const
{
	return this->direction;
}